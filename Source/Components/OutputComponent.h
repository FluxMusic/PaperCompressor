/*
  ==============================================================================

    OutputComponent.h
    Created: 21 May 2024 7:16:48pm
    Author:  Alex Huber

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "LevelMeter.h"
#include "PaperOutputGainSlider.h"

class OutputComponent : public juce::Component, public juce::Timer
{
public:
    OutputComponent(PaperEQAudioProcessor& p);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
    void timerCallback() override;
    
private:
    PaperEQAudioProcessor& audioProcessor;
    
    LevelMeter inputMeter, outputMeter;
    
    PaperOutputGainSlider outputGain;
    juce::AudioProcessorValueTreeState::SliderAttachment outputGainAttachment;
};
