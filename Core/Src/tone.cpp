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
	constexpr float baseNote = 55; // note A0; (assuming A3 = 440Hz)
	return baseNote *  std::pow(2.0, (12.0 * octave + static_cast<float>(note)) / 12.0);
}

} // namespace TalkBox
