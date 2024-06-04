/*
  ==============================================================================

    LevelMeter.cpp
    Created: 21 May 2024 5:51:40pm
    Author:  Alex Huber

  ==============================================================================
*/

#include "LevelMeter.h"

SingleMeter::SingleMeter()
{
}

void SingleMeter::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();
    g.setColour(juce::Colours::grey.withAlpha(0.6f));
    g.fillRoundedRectangle(bounds, 5.f);
    
    g.setGradientFill(juce::ColourGradient{juce::Colours::black.withAlpha(0.3f), bounds.getWidth() / 2, bounds.getBottom(), juce::Colours::black.withAlpha(0.8f), bounds.getWidth() / 2, bounds.getY(), false});
    auto fill = juce::jmap(level, -60.f, 0.f, bounds.getY(), bounds.getBottom());
    g.fillRoundedRectangle(bounds.removeFromBottom(fill), 5.f);
}

LevelMeter::LevelMeter(bool gainScaleLeft)
: gainScaleLeft(gainScaleLeft)
{
    addAndMakeVisible(meterL);
    addAndMakeVisible(meterR);
    
    addAndMakeVisible(peakDB);
    peakDB.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::black);
    peakDB.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::black);
    peakDB.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::floralwhite);
    peakDB.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::floralwhite);
    
    peakDB.onClick = [this]()
    {
        oldLevel = -100.f;
        peakDB.setButtonText("-Inf");
    };
    
    addAndMakeVisible(rmsDB);
    rmsDB.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    rmsDB.setJustificationType(juce::Justification::centred);
}

void LevelMeter::paint(juce::Graphics& g)
{
    meterL.repaint();
    meterR.repaint();
    
    const auto fullBounds = getLocalBounds();
    auto bounds = fullBounds;
    auto levelBounds = bounds.removeFromBottom(bounds.getHeight() / 18);
    auto scaleBounds = bounds;
    
    scaleBounds.removeFromTop(scaleBounds.getHeight() / 15);
    
    auto displayBounds = scaleBounds;
    
    if (gainScaleLeft)
    {
        scaleBounds.removeFromRight(scaleBounds.getWidth() / 2);
        displayBounds = scaleBounds.removeFromLeft(scaleBounds.getWidth() / 1.5);
        peakDB.setJustification(false);
    }
    else
    {
        scaleBounds.removeFromLeft(scaleBounds.getWidth() / 2);
        displayBounds = scaleBounds.removeFromRight(scaleBounds.getWidth() / 1.5);
        peakDB.setJustification(true);
    }
    
    auto left = scaleBounds.getX();
    auto right = left + scaleBounds.getWidth();
    auto top = scaleBounds.getY();
    auto bottom = scaleBounds.getBottom();
    
    const auto fontHeight = displayBounds.getWidth() / 2;
    
    juce::Array<float> rmsDisplay
    {
        -100.f, -60.f, -40.f, -30.f, -20.f, -12.f, -6.f, -3.f, 0.f
    };
    
    g.setColour(juce::Colours::grey.withAlpha(0.8f));
    
    g.setFont(fontHeight);
    
    for (auto rms : rmsDisplay)
    {
        auto lineY = juce::jmap(rms, 0.f, -100.f, static_cast<float>(top), static_cast<float>(bottom));
        if (gainScaleLeft)
        {
            g.drawHorizontalLine(lineY, left + (right - left) / 5, right - (right - left) / 5);
            
            auto text = juce::String::formatted("%.0f", rms);
            
            juce::Rectangle<int> r(displayBounds.getWidth(), fontHeight);
            r.setCentre(displayBounds.getCentreX(), lineY);
            r.setX(displayBounds.getX());
            
            g.drawFittedText(text, r, juce::Justification::right, 1);
        }
        else
        {
            g.drawHorizontalLine(lineY, left + (right - left) / 5, right - (right - left) / 5);
            
            auto text = juce::String::formatted("%.0f", rms);
            
            juce::Rectangle<int> r(displayBounds.getWidth(), fontHeight);
            r.setCentre(displayBounds.getCentreX(), lineY);
            r.setX(displayBounds.getX());
            
            g.drawFittedText(text, r, juce::Justification::left, 1);
        }
    }
    
    juce::String text = juce::String::formatted("%.1f", oldLevel);
    
    auto newLevel = getPeakLevel();
    
    auto font = juce::Font(levelBounds.getHeight() / 1.6);
    
    rmsDB.setFont(font);
    
    rmsDB.setText(juce::String::formatted("%.1f", newLevel), juce::dontSendNotification);
    
    if (newLevel == -100.f)
    {
        rmsDB.setText("-Inf", juce::dontSendNotification);
    }
    
    if (newLevel > oldLevel)
    {
        peakDB.setButtonText(juce::String::formatted("%.1f", newLevel));
        oldLevel = newLevel;
    }
}

void LevelMeter::resized()
{
    const auto fullBounds = getLocalBounds();
    auto bounds = fullBounds;
    
    if (gainScaleLeft)
    {
        bounds.removeFromLeft(bounds.getWidth() / 2);
    }
    else
    {
        bounds.removeFromRight(bounds.getRight() / 2);
    }
    
    auto levelBounds = bounds.removeFromBottom(bounds.getHeight() / 18);
    auto peakBounds = bounds.removeFromTop(bounds.getHeight() / 15);
    
    auto halfBounds = bounds.getWidth() / 2.2;
    
    auto leftMeterBounds = bounds.removeFromLeft(halfBounds);
    auto rightMeterBounds = bounds.removeFromRight(halfBounds);
    
    meterL.setBounds(leftMeterBounds);
    meterR.setBounds(rightMeterBounds);
    
    peakDB.setBounds(peakBounds);
    rmsDB.setBounds(levelBounds);
}

void LevelMeter::setLevels(float leftChannelValue, float rightChannelValue)
{
    meterL.setLevel(leftChannelValue);
    meterR.setLevel(rightChannelValue);
}

float LevelMeter::getPeakLevel()
{
    return juce::jmax(meterL.getLevel(), meterR.getLevel());
}
