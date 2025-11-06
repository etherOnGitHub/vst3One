#include "PluginProcessor.h"
#include "PluginEditor.h"

LightbenderAudioProcessor::LightbenderAudioProcessor() {}

juce::AudioProcessorEditor* LightbenderAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LightbenderAudioProcessor();
}
