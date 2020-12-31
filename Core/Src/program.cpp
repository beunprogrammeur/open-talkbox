/*
 * program.cpp
 *
 *  Created on: Dec 9, 2020
 *      Author: vincent
 */

#include "program.h"
#include "gpio.h"
#include "main.h"
#include "i2s.h"
#include "tone.h"
#include "note.h"

#include "usbd_midi_if.h"
#include "waveform_generator.h"


auto wfGenerator = TalkBox::WaveformGenerator<2400, 44100>();

void UpdatePlayFrequency(float frequency, float amplitude)
{
	wfGenerator.GenerateWaveForm(frequency,  amplitude);
	auto& buffer = wfGenerator.AquireActiveBuffer();

	HAL_I2S_DMAStop(&hi2s2);
	HAL_I2S_Transmit_DMA(&hi2s2, reinterpret_cast<uint16_t*>(buffer.Data().data()), buffer.Size());
}

void MIDI_CC_Received(uint8_t channel, uint8_t code, uint8_t value)
{

}

void MIDI_Note_On_Received(uint8_t channel, uint8_t key, uint8_t velocity)
{
	if(channel != 0) return;

	float frequency = TalkBox::Tone::GetFrequency(key);
	UpdatePlayFrequency(frequency, 1.0 / 127 * velocity);
}

void MIDI_Note_Off_received(uint8_t channel, uint8_t key)
{
	HAL_I2S_DMAStop(&hi2s2);
}


void entrypoint()
{
	wfGenerator.SetWaveform(TalkBox::Waveform::SawTooth);

	float frequency = TalkBox::Tone::GetFrequency(TalkBox::Note::A, 4);
	float frequency2 = TalkBox::Tone::GetFrequency(103);
	wfGenerator.GenerateWaveForm(frequency, 1);
	auto& buffer = wfGenerator.AquireActiveBuffer();

	HAL_I2S_Transmit_DMA(&hi2s2, reinterpret_cast<uint16_t*>(buffer.Data().data()), buffer.Size());

	while(true)
	{

	}
}
