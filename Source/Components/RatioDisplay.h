/*
  ==============================================================================

    RatioDisplay.h
    Created: 4 Jun 2024 10:10:53pm
    Author:  Alex Huber

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

class RatioLine : public juce::Component
{
public:
    RatioLine();
    ~RatioLine();
    
    void setThreshold(float thresholdIn) { threshold = thresholdIn; }
    void setRatio(float ratioIn) { ratio = ratioIn; }
    
private:
    void paint(juce::Graphics& g) override;
    
private:
    float threshold { 0.f };
    float ratio { 1.f };
};

class RatioDisplay : public juce::Component, public juce::Timer
{
public:
    RatioDisplay(PaperCompressorAudioProcessor& p);
    ~RatioDisplay();
    
private:
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
    void timerCallback() override;
    
private:
    RatioLine ratioLine;
    
    PaperCompressorAudioProcessor& audioProcessor;
    
    std::atomic<float> thresholdCache { 0.f };
    std::atomic<float> ratioCache { 1.f };
};
