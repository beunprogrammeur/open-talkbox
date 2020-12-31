/*
 * note.h
 *
 *  Created on: Dec 21, 2020
 *      Author: vincent
 */

#ifndef INC_TONE_H_
#define INC_TONE_H_

#include <stdint.h>
#include "note.h"
namespace TalkBox
{


class Tone
{
private:
public:
	static float GetFrequency(Note note, int octave);
	static float GetFrequency(int midiPitch);
};

} // namespace TalkBox


#endif /* INC_TONE_H_ */
