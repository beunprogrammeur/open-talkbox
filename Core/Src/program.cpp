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

#include "waveform_generator.h"


auto wfGenerator = TalkBox::WaveformGenerator<1604, 44100>();

void entrypoint()
{
	// the lowest key on the piano (A0) has a period of 1603.7 samples
	// TODO: increase the sample time to compensate for pitch-bend effect pedals
	wfGenerator.SetWaveform(TalkBox::Waveform::Square);

	float frequency = TalkBox::Tone::GetFrequency(TalkBox::Note::F, 4);
	wfGenerator.GenerateWaveForm(frequency, 1);
	auto& buffer = wfGenerator.AquireActiveBuffer();

	HAL_I2S_Transmit_DMA(&hi2s2, reinterpret_cast<uint16_t*>(buffer.Data().data()), buffer.Size());

	while(true)
	{

	}
}
