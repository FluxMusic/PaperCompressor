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
#include "PaperKnob.h"

class OutputComponent : public juce::Component, public juce::Timer
{
public:
    OutputComponent(PaperCompressorAudioProcessor& p);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
    void timerCallback() override;
    
private:
    PaperCompressorAudioProcessor& audioProcessor;
    
    LevelMeter inputMeter, outputMeter;
    
    PaperOutputGainSlider threshold;
    PaperKnob inputGain, outputGain;
    juce::AudioProcessorValueTreeState::SliderAttachment thresholdAttachment, inputGainAttachment, outputGainAttachment;
};
