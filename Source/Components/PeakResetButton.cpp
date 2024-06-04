/*
  ==============================================================================

    PeakResetButton.cpp
    Created: 1 Jun 2024 4:26:41pm
    Author:  Alex Huber

  ==============================================================================
*/

#include "PeakResetButton.h"

PeakResetButton::PeakResetButton(juce::String buttonText)
: text(buttonText)
{
    setLookAndFeel(&lnf);
}

PeakResetButton::~PeakResetButton()
{
    setLookAndFeel(nullptr);
}

void PeakResetButton::paint(juce::Graphics& g)
{
    getLookAndFeel().drawButtonBackground(g, *this, juce::Colours::floralwhite.withBrightness(0.95), false, false);
    
    const auto bounds = getLocalBounds();
    
    g.setFont(bounds.getHeight() / 1.7);
    g.setColour(juce::Colours::black);
    
    if (auto textNum = text.getFloatValue())
    {
        if (textNum >= 0.f)
            g.setColour(juce::Colours::red);
    }
    
    if (justifyLeft)
        g.drawFittedText(text, bounds, juce::Justification::left, 1);
    else
        g.drawFittedText(text, bounds, juce::Justification::right, 1);
}
