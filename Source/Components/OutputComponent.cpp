/*
  ==============================================================================

    OutputComponent.cpp
    Created: 21 May 2024 7:16:48pm
    Author:  Alex Huber

  ==============================================================================
*/

#include "OutputComponent.h"

OutputComponent::OutputComponent(PaperEQAudioProcessor& p)
: audioProcessor(p),
inputMeter(false),
outputMeter(true),
outputGain(*audioProcessor.getAPVTS().getParameter("OutputGain")),
outputGainAttachment(audioProcessor.getAPVTS(), "OutputGain", outputGain)
{
    addAndMakeVisible(inputMeter);
    addAndMakeVisible(outputMeter);
    
    addAndMakeVisible(outputGain);
    outputGain.setSliderSnapsToMousePosition(false);
    
    startTimerHz(60);
    
    inputMeter.repaint();
    outputMeter.repaint();
}

void OutputComponent::timerCallback()
{
    const auto leftChannelInputValue = audioProcessor.getRMSInputLevel(0);
    const auto rightChannelInputValue = audioProcessor.getRMSInputLevel(1);
    inputMeter.setLevels(leftChannelInputValue, rightChannelInputValue);
    
    const auto leftChannelOutputValue = audioProcessor.getRMSOutputLevel(0);
    const auto rightChannelOutputValue = audioProcessor.getRMSOutputLevel(1);
    outputMeter.setLevels(leftChannelOutputValue, rightChannelOutputValue);
}

void OutputComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::floralwhite.withBrightness(0.95));
    auto bounds = getLocalBounds();
    auto descBounds = bounds.removeFromBottom(bounds.getHeight() / 8);
    
    auto inputBounds = descBounds.removeFromLeft(descBounds.getWidth() / 3);
    auto outputBounds = descBounds.removeFromRight(descBounds.getWidth() / 2);
    
    auto space = descBounds.getWidth() / 3;
    
    inputBounds.removeFromRight(space);
    outputBounds.removeFromLeft(space);
    
    g.setColour(juce::Colours::black);
    g.setFont(descBounds.getHeight() / 2.4);
    g.drawFittedText("IN", inputBounds, juce::Justification::centred, 1);
    g.drawFittedText("OUT", outputBounds, juce::Justification::centred, 1);
    g.drawFittedText("GAIN", descBounds, juce::Justification::centred, 1);
}

void OutputComponent::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromBottom(bounds.getHeight() / 8);
    auto inputMeterBounds = bounds.removeFromLeft(bounds.getWidth() / 3);
    auto outputMeterBounds = bounds.removeFromRight(bounds.getWidth() / 2);
    
    inputMeter.setBounds(inputMeterBounds);
    outputMeter.setBounds(outputMeterBounds);
    
    auto space = bounds.getWidth() / 20;
    bounds.removeFromLeft(space);
    bounds.removeFromRight(space);
    outputGain.setBounds(bounds);
}
