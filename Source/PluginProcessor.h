#pragma once
#include <JuceHeader.h>

class LightbenderAudioProcessor : public juce::AudioProcessor
{
public:
    LightbenderAudioProcessor();
    ~LightbenderAudioProcessor() override = default;
    //==============================================================================
    // AudioProcessor overrides
    //==============================================================================
    void prepareToPlay(double, int) override {}
    void releaseResources() override {}
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override {}
    const juce::String getName() const override { return "Lightbender"; }
    bool hasEditor() const override { return true; }
    juce::AudioProcessorEditor* createEditor() override;
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override {}
    void setStateInformation(const void*, int) override {}

private:
    std::array<int, 7> fftSizes{ 64, 128, 256, 512, 1024, 2048, 4096 }; // Supported FFT sizes in a set array
	int selectedIndex = 5; // Index to select the FFT size from the fftSizes array (2048 by default)
    int fftSize = fftSizes[selectedIndex];
	int fftOrder = static_cast<int>(std::log2(fftSize)); // Calculate FFT order based on selected size
	fft = std::make_unique< juce::dsp::FFT >(fftOrder); // Unique pointer to JUCE FFT object
	juce::HeapBlock<float> fftBuffer; // Buffer to hold audio data for FFT

	float inputGain = 1.0f; // Gain applied to input signal before processing
	float outputGain = 1.0f; // Gain applied to output signal after processing

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LightbenderAudioProcessor)
};
