/*
  ==============================================================================

    PaperOutputGainSlider.cpp
    Created: 30 May 2024 9:47:56pm
    Author:  Alex Huber

  ==============================================================================
*/

#include "PaperOutputGainSlider.h"

PaperOutputGainSlider::PaperOutputGainSlider(juce::RangedAudioParameter& rap)
: param(&rap)
{
    addAndMakeVisible(textBox);
    setLookAndFeel(&lookAndFeel);
    setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
}

PaperOutputGainSlider::~PaperOutputGainSlider()
{
    setLookAndFeel(nullptr);
}

void PaperOutputGainSlider::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toDouble();
    
    auto labelBounds = bounds.removeFromBottom(bounds.getHeight() / 18);
    bounds.removeFromTop(bounds.getHeight() / 15);
    
    textBox.setBounds(labelBounds.toNearestInt());
    textBox.setJustificationType(juce::Justification::centred);
    
    auto labelText = juce::String::formatted("%.1f", getValue());
    labelText << " dB";
    
    textBox.setText(labelText, juce::dontSendNotification);
    
    auto font = juce::Font(labelBounds.getHeight() / 1.6);
    
    textBox.setFont(font);
    textBox.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::floralwhite.withBrightness(0.95));
    textBox.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    
    const auto range = getRange();
    
    const auto minSliderPos = bounds.getHeight() - bounds.getHeight() / 50;
    const auto maxSliderPos = bounds.getY() + bounds.getHeight() / 15;
    
    setMouseDragSensitivity(minSliderPos - maxSliderPos);
    
    getLookAndFeel().drawLinearSlider(g,
                                      bounds.getX(),
                                      bounds.getY(),
                                      bounds.getWidth(),
                                      bounds.getHeight(),
                                      juce::jmap(static_cast<double>(getValue()), range.getStart(), range.getEnd(), minSliderPos, maxSliderPos),
                                      minSliderPos,
                                      maxSliderPos,
                                      juce::Slider::SliderStyle::LinearBarVertical,
                                      *this);
}
