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
outputComponent(p)
{
    addAndMakeVisible(outputComponent);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(ratioSlider);
    addAndMakeVisible(releaseSlider);
    
    setSize (500, 330);
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(1.52f);
    setResizeLimits(500, 330, 1000, 660);
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
    
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(bounds, 5.f, bounds.getHeight() / 130);
    
    auto outputBounds = bounds.removeFromRight(bounds.getWidth() * 0.38);
    
    g.setColour(juce::Colours::purple);
    g.fillRect(outputBounds);
    
    auto sliderBounds = bounds.removeFromBottom(bounds.getHeight() / 3);
    auto releaseBounds = sliderBounds.removeFromRight(sliderBounds.getWidth() / 3);
    auto ratioBounds = sliderBounds.removeFromRight(sliderBounds.getWidth() / 2);
    
    g.setColour(juce::Colours::red);
    g.fillRect(sliderBounds);
    g.setColour(juce::Colours::orange);
    g.fillRect(ratioBounds);
    g.setColour(juce::Colours::yellowgreen);
    g.fillRect(releaseBounds);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PaperCompressorAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds = bounds.reduced(bounds.getWidth() / 60);
    
    auto outputBounds = bounds.removeFromRight(bounds.getWidth() * 0.38);
    outputComponent.setBounds(outputBounds);
    
    auto sliderBounds = bounds.removeFromBottom(bounds.getHeight() / 3);
    auto releaseBounds = sliderBounds.removeFromRight(sliderBounds.getWidth() / 3);
    auto ratioBounds = sliderBounds.removeFromRight(sliderBounds.getWidth() / 2);
    
    attackSlider.setBounds(sliderBounds);
    ratioSlider.setBounds(ratioBounds);
    releaseSlider.setBounds(releaseBounds);
}
