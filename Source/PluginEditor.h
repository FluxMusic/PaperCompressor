/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/OutputComponent.h"
#include "Components/PaperKnob.h"

//==============================================================================
/**
*/
class PaperCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PaperCompressorAudioProcessorEditor (PaperCompressorAudioProcessor&);
    ~PaperCompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PaperCompressorAudioProcessor& audioProcessor;
    
    PaperKnob attackSlider, ratioSlider, releaseSlider;
    
    juce::AudioProcessorValueTreeState::SliderAttachment attackSliderAttachment, ratioSliderAttachment, releaseSliderAttachment;

    OutputComponent outputComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PaperCompressorAudioProcessorEditor)
};
