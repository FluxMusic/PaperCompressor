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

class RatioDisplay : public juce::Component
{
public:
    RatioDisplay(PaperCompressorAudioProcessor& p);
    ~RatioDisplay();
    
private:
    PaperCompressorAudioProcessor& audioProcessor;
    
    void paint(juce::Graphics& g) override;
};
