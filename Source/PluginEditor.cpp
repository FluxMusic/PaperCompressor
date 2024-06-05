/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PaperCompressorAudioProcessorEditor::PaperCompressorAudioProcessorEditor (PaperCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
attackSlider(*audioProcessor.getAPVTS().getParameter("Attack"), "Attack"),
ratioSlider(*audioProcessor.getAPVTS().getParameter("Ratio"), "Ratio"),
releaseSlider(*audioProcessor.getAPVTS().getParameter("Release"), "Release"),
attackSliderAttachment(audioProcessor.getAPVTS(), "Attack", attackSlider),
ratioSliderAttachment(audioProcessor.getAPVTS(), "Ratio", ratioSlider),
releaseSliderAttachment(audioProcessor.getAPVTS(), "Release", releaseSlider),
ratioDisplay(p),
outputComponent(p)
{
    addAndMakeVisible(outputComponent);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(ratioSlider);
    addAndMakeVisible(releaseSlider);
    
    addAndMakeVisible(ratioDisplay);
    
    setSize (450, 330);
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(1.36f);
    setResizeLimits(450, 330, 900, 660);
}

PaperCompressorAudioProcessorEditor::~PaperCompressorAudioProcessorEditor()
{
}

//==============================================================================
void PaperCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::floralwhite);
    
    auto bounds = getLocalBounds().toFloat();
    bounds = bounds.reduced(bounds.getWidth() / 60);
    
    auto outputBounds = bounds.removeFromRight(bounds.getWidth() * 0.38);
    
    g.setColour(juce::Colours::floralwhite.withBrightness(0.95));
    g.fillRect(outputBounds);
    
    auto titleBounds = outputBounds.removeFromTop(outputBounds.getHeight() / 10);
    
    g.setColour(juce::Colours::black);
    g.setFont(titleBounds.getHeight() / 1.3);
    g.drawFittedText("PaperComp", titleBounds.toNearestInt(), juce::Justification::centred, 1);
    
    auto sliderBounds = bounds.removeFromBottom(bounds.getHeight() / 3);
    auto releaseBounds = sliderBounds.removeFromRight(sliderBounds.getWidth() / 3);
    auto ratioBounds = sliderBounds.removeFromRight(sliderBounds.getWidth() / 2);
    
    g.setColour(juce::Colours::red);
    g.fillRect(sliderBounds);
    g.setColour(juce::Colours::orange);
    g.fillRect(ratioBounds);
    g.setColour(juce::Colours::yellowgreen);
    g.fillRect(releaseBounds);
    
    bounds = getLocalBounds().toFloat();
    bounds = bounds.reduced(bounds.getWidth() / 60);
    
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(bounds, 5.f, bounds.getHeight() / 130);
}

void PaperCompressorAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds = bounds.reduced(bounds.getWidth() / 60);
    const auto space = bounds.getHeight() / 50;
    
    auto outputBounds = bounds.removeFromRight(bounds.getWidth() * 0.38);
    outputBounds.removeFromTop(outputBounds.getHeight() / 10);
    outputBounds.removeFromRight(bounds.getHeight() / 130);
    outputBounds.removeFromBottom(bounds.getHeight() / 130);
    outputBounds.removeFromRight(space);
    outputBounds.removeFromLeft(space);
    outputComponent.setBounds(outputBounds);
    
    auto sliderBounds = bounds.removeFromBottom(bounds.getHeight() / 3);
    auto releaseBounds = sliderBounds.removeFromRight(sliderBounds.getWidth() / 3);
    auto ratioBounds = sliderBounds.removeFromRight(sliderBounds.getWidth() / 2);
    
    attackSlider.setBounds(sliderBounds);
    ratioSlider.setBounds(ratioBounds);
    releaseSlider.setBounds(releaseBounds);
    
    ratioDisplay.setBounds(bounds);
}
