#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class LightbenderAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    LightbenderAudioProcessorEditor(LightbenderAudioProcessor&);
    ~LightbenderAudioProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override {}

private:
    LightbenderAudioProcessor& processorRef;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LightbenderAudioProcessorEditor)
};
