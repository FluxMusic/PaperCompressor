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
    auto bounds = getLocalBounds();
    
    juce::String valueString = "";
    
    if (param->getParameterID().equalsIgnoreCase("LowCutFreq")
        || param->getParameterID().equalsIgnoreCase("LowShelfFreq")
        || param->getParameterID().equalsIgnoreCase("PeakFreq")
        || param->getParameterID().equalsIgnoreCase("HighShelfFreq")
        || param->getParameterID().equalsIgnoreCase("HighCutFreq"))
    {
        valueString = static_cast<juce::String>(getValue());
        valueString.append(" Hz", 3);
    }
    else if (param->getParameterID().equalsIgnoreCase("LowShelfGain")
             || param->getParameterID().equalsIgnoreCase("PeakGain")
             || param->getParameterID().equalsIgnoreCase("HighShelfGain"))
    {
        auto range = getRange();
        valueString = juce::String::formatted("%.1f", juce::jmap(getValue(), range.getStart(), range.getEnd(), -18.0, 18.0));
        valueString.append(" dB", 3);
    }
    else if (param->getParameterID().equalsIgnoreCase("LowShelfQ")
             || param->getParameterID().equalsIgnoreCase("PeakQ")
             || param->getParameterID().equalsIgnoreCase("HighShelfQ"))
    {
        auto range = getRange();
        valueString = juce::String::formatted("%.1f", juce::jmap(getValue(), range.getStart(), range.getEnd(), 0.1, 10.0));
    }
    else
    {
        if (auto choiceParam = dynamic_cast<juce::AudioParameterChoice*>(param))
            valueString = choiceParam->getCurrentChoiceName();
    }
    
    const auto valueBounds = bounds.removeFromBottom(bounds.getHeight() / 5);
    
//    const auto labelBounds = bounds.removeFromTop(bounds.getHeight() / 4);
    
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
    g.setColour(juce::Colours::black);
    g.setFont(valueBounds.getHeight() / 1.3);
//    g.drawFittedText(sliderName, labelBounds, juce::Justification::centred, 1);
//    
    g.drawFittedText(static_cast<juce::String>(valueString), valueBounds, juce::Justification::centred, 1);
}
