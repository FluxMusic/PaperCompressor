/*
  ==============================================================================

    PaperLookAndFeel.cpp
    Created: 5 May 2024 5:42:04pm
    Author:  Alex Huber

  ==============================================================================
*/

#include "PaperLookAndFeel.h"
#include "../Components/PaperKnob.h"
#include "../Components/PeakResetButton.h"
#include "../Components/PaperBypass.h"

void PaperLookAndFeel::drawRotarySlider(juce::Graphics& g, 
                                        int x,
                                        int y,
                                        int width,
                                        int height,
                                        float sliderPosProportional,
                                        float rotaryStartAngle,
                                        float rotaryEndAngle,
                                        juce::Slider& slider)
{
    const auto originalBounds = juce::Rectangle<int>(x, y, width, height);
    
    if (dynamic_cast<PaperKnob*>(&slider))
    {
        auto size = juce::jmin(originalBounds.getWidth(), originalBounds.getHeight());
        
        auto bounds = juce::Rectangle<int>(size, size);
        
        bounds.setCentre(originalBounds.getCentre());
        
        if (const auto svg = juce::XmlDocument::parse(BinaryData::Knob_svg))
        {
            const auto drawable = juce::Drawable::createFromSVG(*svg);
            drawable->setTransformToFit(bounds.toFloat(), juce::RectanglePlacement::centred);
            
            const float angle = juce::jmap(sliderPosProportional, 0.f, 1.f, rotaryStartAngle, rotaryEndAngle);
            
            drawable->draw(g, 1.f, juce::AffineTransform::rotation(angle, bounds.getCentreX(), bounds.getCentreY()));
        }
    }
}

void PaperLookAndFeel::drawLinearSlider(juce::Graphics& g,
                                        int x,
                                        int y,
                                        int width,
                                        int height,
                                        float sliderPos,
                                        float minSliderPos,
                                        float maxSliderPos,
                                        juce::Slider::SliderStyle,
                                        juce::Slider& slider)
{
    const auto bounds = juce::Rectangle<int>(x, y, width, height);
    
    const auto size = juce::jmin(width, height) / 2.2;
    
    auto knobBounds = juce::Rectangle<int>(size, size * 1.5);
    knobBounds.setX(bounds.getCentreX() - size / 2);
    knobBounds.setY(sliderPos - (size * 1.5) / 2);
    
    if (const auto slider = juce::XmlDocument::parse(BinaryData::OutputGainSlider1_svg))
    {
        const auto drawable = juce::Drawable::createFromSVG(*slider);
        drawable->setTransformToFit(bounds.toFloat(), juce::RectanglePlacement::stretchToFit);
        drawable->draw(g, 1.f);
    }
    
    if (const auto sliderKnob = juce::XmlDocument::parse(BinaryData::OutputGainSliderKnob_svg))
    {
        const auto drawable = juce::Drawable::createFromSVG(*sliderKnob);
        g.setColour(juce::Colours::floralwhite.withBrightness(0.95));
        g.fillRect(knobBounds);
        drawable->setTransformToFit(knobBounds.toFloat(), juce::RectanglePlacement::stretchToFit);
        drawable->draw(g, 1.f);
    }
}
void PaperLookAndFeel::drawButtonBackground(juce::Graphics& g,
                                            juce::Button& button,
                                            const juce::Colour &backgroundColour,
                                            bool shouldDrawButtonAsHighlighted,
                                            bool shouldDrawButtonAsDown)
{
    if (dynamic_cast<PeakResetButton*>(&button))
        g.fillAll(backgroundColour);
    
    if (auto toggleButton = dynamic_cast<PaperBypass*>(&button))
    {
        auto bounds = button.getLocalBounds().toFloat();
        bounds = bounds.reduced(bounds.getHeight() / 13);
        
        g.setColour(juce::Colours::black);
        
        g.drawRoundedRectangle(bounds, bounds.getHeight() / 15, bounds.getHeight() / 18);
        
        toggleButton->getToggleState() ? g.setColour(juce::Colours::grey) : g.setColour(juce::Colours::floralwhite);
        
        g.fillRect(bounds);
        
        auto insideBounds = bounds.reduced(bounds.getHeight() / 13);
        
        g.setColour(juce::Colours::black);
        
        g.drawRoundedRectangle(insideBounds, bounds.getHeight() / 20, bounds.getHeight() / 18);
        
        toggleButton->getToggleState() ? g.setColour(juce::Colours::black.withAlpha(0.8f)) : g.setColour(juce::Colours::floralwhite);
        
        g.fillRect(insideBounds);
    }
}
