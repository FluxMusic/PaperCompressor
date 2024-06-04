/*
  ==============================================================================

    PeakResetButton.h
    Created: 1 Jun 2024 4:26:41pm
    Author:  Alex Huber

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../LookAndFeel/PaperLookAndFeel.h"

class PeakResetButton : public juce::TextButton
{
public:
    PeakResetButton(juce::String buttonText);
    ~PeakResetButton();
    
    void setButtonText(juce::String newButtonText) { text = newButtonText; }
    
    void setJustification(bool newJustifyLeft) { justifyLeft = newJustifyLeft; }
    
private:
    PaperLookAndFeel lnf;
    
    juce::String text;
    
    bool justifyLeft { false };
    
    void paint(juce::Graphics& g) override;
};
