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

#include "usbd_midi_if.h"
#include "midi/imidi_source.h"
#include "synthesis/synthesizers/synthesizer.h"
#include "synthesis/sound_sources/isound_source.h"
#include "embedded_sound_source.h"
#include "midi/synthesizer_midi_sink.h"
#include "synth.h"
#include "synthesis/buffer.h"
#include <queue>

using namespace BOSSCorp::Midi;
IMidiSource midiSource;

volatile bool writeFirstHalf = false;
volatile bool writeSecondHalf = false;

std::queue<MidiEvent> midiEventQueue;

void MIDI_Message_Received(uint8_t status, uint8_t data1, uint8_t data2)
{
	//midiEventQueue.push(MidiEvent(static_cast<Status>(status), data1, data2));
	midiSource.send(MidiEvent(static_cast<Status>(status), data1, data2));
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	writeFirstHalf = true;
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	writeSecondHalf = true;
}




void entrypoint()
{
	synth s(10);
	s.init();
	SynthesizerMidiSink synthSink(Channel::Channel1, s);
	midiSource.subscribe(synthSink);

	constexpr int dataSize   = 128;
	constexpr int samplerate = 15980;
	constexpr int bufferSize = dataSize / 2;
	int16_t* data = new int16_t[dataSize];

	BOSSCorp::Synthesis::Buffer buffera(bufferSize, samplerate, data);
	BOSSCorp::Synthesis::Buffer bufferb(bufferSize, samplerate, data + dataSize);

	for(int i = 0; i < dataSize; i++)
	{
		data[i] = 0;
	}

	HAL_I2S_Transmit_DMA(&hi2s2, reinterpret_cast<uint16_t*>(data), dataSize);

	while(true)
	{
		while(!midiEventQueue.empty())
		{
			MidiEvent event = midiEventQueue.front();
			midiSource.send(event);
			midiEventQueue.pop();
		}

		if(writeFirstHalf)
		{
			writeFirstHalf = false;
			s.process(buffera);
		}

		if(writeSecondHalf)
		{
			writeSecondHalf = false;
			s.process(bufferb);
		}
	}
}

