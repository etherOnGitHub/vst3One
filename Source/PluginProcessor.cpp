#include "PluginProcessor.h"
#include "PluginEditor.h"

LightbenderAudioProcessor::LightbenderAudioProcessor() 
{
    // defaults
}

// -- DSP
void LightbenderAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	juce::ignoreUnused(sampleRate, samplesPerBlock);
	// init fft
	fftSize = fftSizes[selectedIndex];
	fftOrder = static_cast<int>(std::log2(fftSize)); // Calculate FFT order based on selected size
	fft = std::make_unique< juce::dsp::FFT >(fftOrder); // Unique pointer to JUCE FFT object
	fftBuffer.allocate(2 * fftSize, true); // Allocate buffer for FFT (real + imaginary parts)
}

void LightbenderAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ignoreUnused(midiMessages);
	const int numChannels = buffer.getNumChannels();
	const int numSamples = buffer.getNumSamples();

	jassert(numSamples == fftSize); // Ensure the number of samples matches the FFT size

	for (int channel = 0; channel < numChannels; ++channel)
	{
		float* channelData = buffer.getWritePointer(channel);

		for (int i = 0; i < fftSize; ++i) // Prepare FFT input
			fftBuffer[i] = channelData[i] * inputGain; // Apply input gain
		for (int i = 0; i < fftSize; ++i) // Zero imaginary parts
			fftBuffer[i + fftSize] = 0.0f; // Imaginary part initialized to zero
		fft->performRealOnlyForwardTransform(fftBuffer.getData()); // Perform real FFT
		//=====================================================

		// Frequency domain processing will be done here

		//=====================================================
		fft->performRealOnlyInverseTransform(fftBuffer.getData()); // Perform inverse FFT
		const float normalisationFactor = 1.0f / static_cast<float>(fftSize); // Normalization factor
		for (int i = 0; i < fftSize; ++i) // Process FFT output
		{
			float outSample = fftBuffer[i] * normalisationFactor; // Normalize FFT output
			outSample = juce::jlimit(-1.0f, 1.0f, outSample); // Limit output sample to [-1.0, 1.0]
			channelData[i] = outSample; // Write back to buffer
		}
	}
}

juce::AudioProcessorEditor* LightbenderAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LightbenderAudioProcessor();
}


