/*
 * tone.cpp
 *
 *  Created on: Dec 21, 2020
 *      Author: vincent
 */

#include "tone.h"
#include <cmath>

namespace TalkBox
{

float Tone::GetFrequency(Note note, int octave)
{
	constexpr float baseNote = 27.5; // note A0; (assuming A3 = 440Hz)
	return baseNote *  std::pow(2.0, (12.0 * octave + static_cast<float>(note)) / 12.0);
}

float Tone::GetFrequency(int midiPitch)
{
	midiPitch -= 21; // A0 = pitch 21;

	auto note = static_cast<Note>(midiPitch % 12);
	auto octave = midiPitch / 12;

	return GetFrequency(note, octave);
}

} // namespace TalkBox
