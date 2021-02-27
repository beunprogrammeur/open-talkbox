/*
 * synth.h
 *
 *  Created on: 13 Feb 2021
 *      Author: vincent
 */

#ifndef INC_SYNTH_H_
#define INC_SYNTH_H_

#include "synthesis/synthesizers/synthesizer.h"
#include "synthesis/sound_sources/isound_source.h"
#include "embedded_sound_source.h"

class synth : public BOSSCorp::Synthesis::Synthesizers::Synthesizer
{
protected:
	virtual BOSSCorp::Synthesis::SoundSources::ISoundSource* getNewSoundSource()
	{
		return new BOSSCorp::TalkBox::SoundSources::EmbeddedSoundSource(_adsrConfig, _pwmConfig, _sawtoothConfig);
	}

public:
	explicit synth(int polyhony) : Synthesizer(polyhony) {}
};



#endif /* INC_SYNTH_H_ */
