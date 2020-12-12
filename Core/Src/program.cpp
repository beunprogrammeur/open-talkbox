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

#include "waveform_generator.h"


auto wfGenerator = TalkBox::WaveformGenerator<1604, 44100>();

void entrypoint()
{
	// the lowest key on the piano (A0) has a period of 1603.7 samples
	// TODO: increase the sample time to compensate for pitch-bend effect pedals
	wfGenerator.SetWaveform(TalkBox::Waveform::SawTooth);
	wfGenerator.GenerateWaveForm(4186, 0.25);

	while(true)
	{
		auto& buffer = wfGenerator.AquireActiveBuffer();
		HAL_I2S_Transmit(&hi2s1, reinterpret_cast<uint16_t*>(buffer.Data().data()), buffer.Size(), 10);
	}
}
