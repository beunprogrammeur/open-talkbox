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


auto* wfGenerator = new TalkBox::WaveformGenerator<1604, 44100>();

void entrypoint()
{
	// the lowest key on the piano (A0) has a period of 1603.7 samples
	// TODO: increase the sample time to compensate for pitch-bend effect pedals
	wfGenerator->SetWaveform(TalkBox::Waveform::SawTooth);
	//wfGenerator->GenerateWaveForm(2000, 1);




	//HAL_SPI_Transmit_DMA(&hspi2, reinterpret_cast<uint8_t*>(buffer.Data().data()), buffer.Size());
	uint32_t time = 0;
	uint32_t freq = 0;
	while(true)
	{
		auto tick = HAL_GetTick();
		if(tick > time + 100)
		{
			time = tick;

			freq += 100;
			if(freq > 4000) freq = 100;

			wfGenerator->GenerateWaveForm(freq, 1);
			auto& buffer = wfGenerator->AquireActiveBuffer();

			HAL_I2S_DMAStop(&hi2s2);
			HAL_I2S_Transmit_DMA(&hi2s2, reinterpret_cast<uint16_t*>(buffer.Data().data()), buffer.Size());
		}
	}
}
