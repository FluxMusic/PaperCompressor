/*
  ==============================================================================

    PaperKnob.h
    Created: 5 May 2024 5:41:45pm
    Author:  Alex Huber

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../LookAndFeel/PaperLookAndFeel.h"

class PaperKnob : public juce::Slider
{
public:
    PaperKnob(juce::RangedAudioParameter& rap, juce::String label);
    
    ~PaperKnob();
    
    void paint (juce::Graphics&) override;
    
private:
    PaperLookAndFeel lnf;
    
    juce::RangedAudioParameter* param;
    
    juce::String sliderName;
};
