/*
 * embedded_sound_source.h
 *
 *  Created on: 13 Feb 2021
 *      Author: vincent
 */

#ifndef INC_EMBEDDED_SOUND_SOURCE_H_
#define INC_EMBEDDED_SOUND_SOURCE_H_

#include "synthesis/sound_sources/isound_source.h"
#include "synthesis/oscillators/pwm_oscillator.h"
#include "synthesis/oscillators/sawtooth_oscillator.h"
#include "synthesis/oscillators/configurations/configurations.h"
#include "synthesis/envelopes/adsr_envelope.h"
namespace BOSSCorp::TalkBox::SoundSources
{

class EmbeddedSoundSource : public BOSSCorp::Synthesis::SoundSources::ISoundSource
{
private:
	BOSSCorp::Synthesis::Envelopes::ADSREnvelope _adsrEnvelope;
	BOSSCorp::Synthesis::Oscillators::PWMOscillator _pwmOscillator;
	BOSSCorp::Synthesis::Oscillators::SawToothOscillator _sawtoothOscillator;
	BOSSCorp::Synthesis::Oscillators::IOscillator& osc1;
	BOSSCorp::Synthesis::Oscillators::IOscillator& osc2;
public:
	EmbeddedSoundSource(BOSSCorp::Synthesis::Envelopes::ADSRConfiguration& adsrConfig, const BOSSCorp::Synthesis::Oscillators::Configurations::PWMConfiguration& pwmConfig, const BOSSCorp::Synthesis::Oscillators::Configurations::SawtoothConfiguration& sawtoothConfig);
	virtual float next();
	virtual void reset();
	virtual void configure(Midi::Note note, int8_t octave, float amplitude);
	virtual void release() { _adsrEnvelope.release(); }
};

} // end BOSSCorp::TalkBox::SoundSources



#endif /* INC_EMBEDDED_SOUND_SOURCE_H_ */
