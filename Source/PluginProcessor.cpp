/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PaperCompressorAudioProcessor::PaperCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
apvts(*this, nullptr, "Parameters", createParameterLayout())
#endif
{
}

PaperCompressorAudioProcessor::~PaperCompressorAudioProcessor()
{
}

//==============================================================================
const juce::String PaperCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PaperCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PaperCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PaperCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PaperCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PaperCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PaperCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PaperCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PaperCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void PaperCompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PaperCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PaperCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PaperCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PaperCompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool PaperCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PaperCompressorAudioProcessor::createEditor()
{
    //    return new PaperCompressorAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void PaperCompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PaperCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PaperCompressorAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout PaperCompressorAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    auto gainRange = juce::NormalisableRange<float>(-60.f, 12.f, 0.1f, 1.f);
    auto thresholdRange = juce::NormalisableRange<float>(-60.f, 0.f, 0.1f, 1.f);
    auto attackRange = juce::NormalisableRange<float>(1.f, 200.f, 1.f, 1.f);
    auto releaseRange = juce::NormalisableRange<float>(10.f, 2000.f, 1.f, 1.f);
    
    auto choices = std::vector<float>{1, 1.5, 2, 3, 4, 5, 6, 7, 8, 10, 20, 50, 100};
    juce::StringArray choiceStrings;
    for (auto choice : choices)
    {
        choiceStrings.add(juce::String(choice, 1));
    }

    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("InputGain", 1), "Input Gain", gainRange, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Threshold", 2), "Threshold", thresholdRange, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Attack", 3), "Attack", attackRange, 10.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Release", 4), "Release", releaseRange, 200.f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID("Ratio", 5), "Ratio", choiceStrings, 2));
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("OutputGain", 6), "Output Gain", gainRange, 0));

    return layout;
}
