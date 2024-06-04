/*
  ==============================================================================

    PaperOutputGainSlider.h
    Created: 30 May 2024 9:47:56pm
    Author:  Alex Huber

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../LookAndFeel/PaperLookAndFeel.h"

class PaperOutputGainSlider : public juce::Slider
{
public:
    PaperOutputGainSlider(juce::RangedAudioParameter& rap);
    ~PaperOutputGainSlider();
    
    void paint(juce::Graphics& g) override;
    
private:
    PaperLookAndFeel lookAndFeel;
    
    juce::RangedAudioParameter* param;
    
    juce::Label textBox;
};
