#include "PluginEditor.h"

LightbenderAudioProcessorEditor::LightbenderAudioProcessorEditor(LightbenderAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    setSize(400, 300);
}

void LightbenderAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawFittedText("Lightbender", getLocalBounds(), juce::Justification::centred, 1);
}
