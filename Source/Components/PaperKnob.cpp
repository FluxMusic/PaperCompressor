/*
  ==============================================================================

    PaperKnob.cpp
    Created: 5 May 2024 5:41:45pm
    Author:  Alex Huber

  ==============================================================================
*/

#include "PaperKnob.h"

PaperKnob::PaperKnob(juce::RangedAudioParameter& rap, juce::String label)
: juce::Slider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox),
param(&rap),
sliderName(label)
{
    setLookAndFeel(&lnf);
}

PaperKnob::~PaperKnob()
{
    setLookAndFeel(nullptr);
    
//    param = nullptr;
}

void PaperKnob::paint(juce::Graphics& g)
{
    auto fullBounds = getLocalBounds();
    auto size = juce::jmin(fullBounds.getWidth(), fullBounds.getHeight());
    auto bounds = juce::Rectangle<int>(size, size);
    bounds.setCentre(fullBounds.getCentre());
    
    juce::String valueString = "";
    
    if (param->getParameterID().equalsIgnoreCase("InputGain")
        || param->getParameterID().equalsIgnoreCase("OutputGain"))
    {
        valueString = juce::String::formatted("%.1f", getValue());
        valueString.append(" dB", 3);
    }
    else if (param->getParameterID().equalsIgnoreCase("Ratio"))
    {
        valueString = juce::String::formatted("%.1f", getValue());
        valueString.append(":1", 2);
    }
    else
    {
        valueString = static_cast<juce::String>(getValue());
        valueString.append(" ms", 3);
    }
    
    juce::Rectangle<int> labelBounds;
    
    const auto valueBounds = bounds.removeFromBottom(bounds.getHeight() / 5);
    
    if (param->getParameterID().equalsIgnoreCase("InputGain")
        || param->getParameterID().equalsIgnoreCase("OutputGain"))
    {
    }
    else
        labelBounds = bounds.removeFromTop(bounds.getHeight() / 4);
    
    const auto startAngle = juce::degreesToRadians(180.f + 30.f);
    const auto endAngle = juce::degreesToRadians(180.f - 30.f) + juce::MathConstants<float>::twoPi;
    
    const auto range = getRange();
    
    if (param->getParameterID().equalsIgnoreCase("LowCutFreq")
        || param->getParameterID().equalsIgnoreCase("LowShelfFreq")
        || param->getParameterID().equalsIgnoreCase("PeakFreq")
        || param->getParameterID().equalsIgnoreCase("HighShelfFreq")
        || param->getParameterID().equalsIgnoreCase("HighCutFreq"))
    {
        getLookAndFeel().drawRotarySlider(g,
                                          bounds.getX(),
                                          bounds.getY(),
                                          bounds.getWidth(),
                                          bounds.getHeight(),
                                          juce::mapFromLog10(getValue(), range.getStart(), range.getEnd()),
                                          startAngle,
                                          endAngle,
                                          *this);
    }
    
    else
    {
        getLookAndFeel().drawRotarySlider(g,
                                          bounds.getX(),
                                          bounds.getY(),
                                          bounds.getWidth(),
                                          bounds.getHeight(),
                                          juce::jmap(getValue(), range.getStart(), range.getEnd(), 0.0, 1.0),
                                          startAngle,
                                          endAngle,
                                          *this);
    }
    if (!param->getParameterID().equalsIgnoreCase("InputGain")
        || !param->getParameterID().equalsIgnoreCase("OutputGain"))
    {
        g.setColour(juce::Colours::black);
        g.setFont(labelBounds.getHeight() / 1.3);
        g.drawFittedText(sliderName, labelBounds, juce::Justification::centred, 1);
    }
    g.setFont(valueBounds.getHeight() / 1.3);
    g.drawFittedText(static_cast<juce::String>(valueString), valueBounds, juce::Justification::centred, 1);
}
