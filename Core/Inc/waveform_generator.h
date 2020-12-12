/*
 * waveform_generator.h
 *
 *  Created on: Dec 12, 2020
 *      Author: vincent
 */

#ifndef INC_WAVEFORM_GENERATOR_H_
#define INC_WAVEFORM_GENERATOR_H_

#include <stdint.h>
#include "buffer.h"
#include <limits>
#include <algorithm>

namespace TalkBox
{

enum class Waveform : uint8_t
{
	Square,
	SawTooth,
	Sine
};

struct WaveformData
{
public:
	float sampleTime;
	float waveTime;
	float amplitude;
	int samplesPerWave;
};

template <int bufferSize, int sampleRate> class WaveformGenerator
{
public:
	typedef TalkBox::Buffer<int16_t, bufferSize> WaveBuffer;
private:
	Waveform _waveform;
	WaveBuffer  _bufferA, _bufferB;
	WaveBuffer& _activeBuffer;

public:
	WaveformGenerator();

	void SetWaveform(Waveform waveform);
	void GenerateWaveForm(float frequency, float amplitude);
	WaveBuffer& AquireActiveBuffer() const;
private:
	void FillBuffer(WaveBuffer& buffer, int waveLength);
	WaveBuffer& AquireInactiveBuffer();
	void SetActiveBuffer(WaveBuffer& buffer);

	void GenerateSquareWave(  WaveBuffer& buffer, const WaveformData& data);
	void GenerateSineWave(    WaveBuffer& buffer, const WaveformData& data);
	void GenerateSawToothWave(WaveBuffer& buffer, const WaveformData& data);
};

template< int bufferSize, int sampleRate>
WaveformGenerator<bufferSize, sampleRate>::WaveformGenerator()
	: _waveform(Waveform::Square)
	, _bufferA()
	, _bufferB()
	, _activeBuffer(_bufferA){ }

template< int bufferSize, int sampleRate>
void WaveformGenerator<bufferSize, sampleRate>::SetWaveform(Waveform waveform)
{
	_waveform = waveform;
}

template< int bufferSize, int sampleRate>
void WaveformGenerator<bufferSize,sampleRate>::GenerateWaveForm(float frequency, float amplitude)
{
	auto data       = TalkBox::WaveformData();
	data.amplitude  = amplitude;
	data.sampleTime = 1.0 / sampleRate;
	data.waveTime   = 1.0 / frequency;
	data.samplesPerWave = data.waveTime / data.sampleTime;

	auto& buffer = AquireInactiveBuffer();

	switch(_waveform)
	{
	case Waveform::Square:
		GenerateSquareWave(buffer, data);
		break;
	case Waveform::SawTooth:
		GenerateSawToothWave(buffer, data);
		break;
	case Waveform::Sine:
		GenerateSineWave(buffer, data);
		break;
	}

	FillBuffer(buffer, data.samplesPerWave);
	SetActiveBuffer(buffer);
}

template< int bufferSize, int sampleRate>
typename WaveformGenerator<bufferSize, sampleRate>::WaveBuffer& WaveformGenerator<bufferSize, sampleRate>::AquireInactiveBuffer()
{
	return (&_activeBuffer == &_bufferA) ?_bufferB : _bufferA;
}
template< int bufferSize, int sampleRate>
typename WaveformGenerator<bufferSize, sampleRate>::WaveBuffer& WaveformGenerator<bufferSize, sampleRate>::AquireActiveBuffer() const
{
	return _activeBuffer;
}

template< int bufferSize, int sampleRate>
void WaveformGenerator<bufferSize, sampleRate>::SetActiveBuffer(WaveBuffer& buffer)
{
	_activeBuffer = buffer;
}

template< int bufferSize, int sampleRate>
void WaveformGenerator<bufferSize, sampleRate>::FillBuffer(WaveBuffer& buffer, int waveLength)
{
	auto& data = buffer.Data();
	int count  = data.size() / waveLength;

	// the original data is at position 0, repeat copy that data
	for(int i = 1; i < count; i++)
	{
		std::copy(data.begin(), data.begin() + waveLength, data.begin() + (i * waveLength));
	}

	buffer.Size(count * waveLength);
}

template< int bufferSize, int sampleRate>
void WaveformGenerator<bufferSize, sampleRate>::GenerateSquareWave(WaveBuffer& buffer, const WaveformData& data)
{
	const int halfWave      = data.samplesPerWave / 2;
	const int stepAmplitude = data.amplitude * std::numeric_limits<int16_t>::max();
	const int low  = -stepAmplitude;
	const int high = +stepAmplitude;

	auto& array = buffer.Data();
	// waveform generation
	for(int i = 0; i < halfWave; i++)
	{
		array[i] = low;
	}

	for(int i = halfWave; i < data.samplesPerWave; i++)
	{
		array[i] = high;
	}
}

template< int bufferSize, int sampleRate>
void WaveformGenerator<bufferSize, sampleRate>::GenerateSineWave(WaveBuffer& buffer, const WaveformData& data)
{
	// TODO: generate Sine using CMSIS DSP Library.
}

template< int bufferSize, int sampleRate>
void WaveformGenerator<bufferSize, sampleRate>::GenerateSawToothWave(WaveBuffer& buffer, const WaveformData& data)
{
	const int stepAmplitude = data.amplitude * std::numeric_limits<int16_t>::max();
	const int low  = -stepAmplitude;
	const int high = +stepAmplitude;
	const int step = high*2 / data.samplesPerWave;

	auto& array = buffer.Data();
	for(int i = 0; i < data.samplesPerWave; i++)
	{
		array[i] = low + (step * i);
	}
}



} // namespace TalkBox




#endif /* INC_WAVEFORM_GENERATOR_H_ */
