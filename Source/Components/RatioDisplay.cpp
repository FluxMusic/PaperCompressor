/*
  ==============================================================================

    RatioDisplay.cpp
    Created: 4 Jun 2024 10:10:53pm
    Author:  Alex Huber

  ==============================================================================
*/

#include "RatioDisplay.h"

RatioDisplay::RatioDisplay(PaperCompressorAudioProcessor& p)
: audioProcessor(p)
{
}

RatioDisplay::~RatioDisplay()
{
}

void RatioDisplay::paint(juce::Graphics& g)
{
    const auto fullBounds = getLocalBounds();
    const auto size = juce::jmin(fullBounds.getHeight(), fullBounds.getWidth());
    auto bounds = juce::Rectangle<float>(size, size);
    bounds.setCentre(fullBounds.getCentre().toFloat());
    g.setColour(juce::Colours::black.withAlpha(0.9f));
    g.fillRect(bounds.reduced(size / 75));
    bounds = bounds.reduced(size / 50);
    g.setColour(juce::Colours::floralwhite);
    g.fillRect(bounds);
    const auto thumbSize = bounds.getHeight() / 30;
    auto thresholdThumb = juce::Rectangle<float>(thumbSize, thumbSize);
    auto ratioThumb = thresholdThumb;
    
    juce::Array<float> lines
    {
        -10.f, -20.f, -30.f, -40.f, -50.f
    };
    
    g.setColour(juce::Colours::grey.withAlpha(0.5f));
    
    for (auto line : lines)
    {
        auto lineX = juce::jmap(line, -60.f, 0.f, bounds.getX(), bounds.getRight());
        auto lineY = juce::jmap(line, -60.f, 0.f, bounds.getBottom(), bounds.getY());
        g.drawVerticalLine(lineX, bounds.getY(), bounds.getBottom());
        g.drawHorizontalLine(lineY, bounds.getX(), bounds.getRight());
    }
    
    auto threshold = audioProcessor.getAPVTS().getRawParameterValue("Threshold")->load();
    auto ratio = audioProcessor.getAPVTS().getRawParameterValue("Ratio")->load();
    
    auto thresholdX = juce::jmap(threshold, -60.f, 0.f, bounds.getX(), bounds.getRight());
    auto thresholdY = juce::jmap(threshold, -60.f, 0.f, bounds.getBottom(), bounds.getY());
    
    auto thresholdPoint = juce::Point<float>(thresholdX, thresholdY);
    
    juce::Path ratioPath;
    
    ratioPath.startNewSubPath(bounds.getX(), bounds.getBottom());
    
    ratioPath.lineTo(thresholdPoint);
    
    auto ratioBounds = juce::Rectangle<float>(thresholdPoint, bounds.getTopRight());
    ratioBounds.removeFromBottom(ratioBounds.getHeight() / ratio);
    
    ratioPath.lineTo(ratioBounds.getBottomRight());
    
    thresholdThumb.setCentre(thresholdPoint);
    ratioThumb.setCentre(ratioBounds.getBottomRight());
    
    g.setColour(juce::Colours::black);
    g.strokePath(ratioPath, juce::PathStrokeType(2.f));
    ratioPath.lineTo(bounds.getBottomRight());
    ratioPath.closeSubPath();
    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.fillPath(ratioPath);
    
    g.setColour(juce::Colours::black);
    g.fillEllipse(thresholdThumb);
    g.fillEllipse(ratioThumb);
    g.setColour(juce::Colours::floralwhite);
    g.fillEllipse(thresholdThumb.reduced(ratioThumb.getWidth() / 5));
    g.fillEllipse(ratioThumb.reduced(ratioThumb.getWidth() / 5));
}
