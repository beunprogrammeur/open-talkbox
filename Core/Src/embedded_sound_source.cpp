/*
 * embedded_sound_source.cpp
 *
 *  Created on: 13 Feb 2021
 *      Author: vincent
 */

#include "embedded_sound_source.h"
#include "midi/converter.h"
namespace BOSSCorp::TalkBox::SoundSources
{

EmbeddedSoundSource::EmbeddedSoundSource(BOSSCorp::Synthesis::Envelopes::ADSRConfiguration& adsrConfig, const BOSSCorp::Synthesis::Oscillators::Configurations::PWMConfiguration& pwmConfig, const BOSSCorp::Synthesis::Oscillators::Configurations::SawtoothConfiguration& sawtoothConfig)
	: _adsrEnvelope(adsrConfig), _pwmOscillator(pwmConfig), _sawtoothOscillator(sawtoothConfig), osc1(_pwmOscillator), osc2(_sawtoothOscillator), ISoundSource(_adsrEnvelope)
{
}

float EmbeddedSoundSource::next()
{
	using namespace BOSSCorp::Synthesis::Oscillators;
	float sample = 0.0f;

	float dt = deltaTime();

	sample += osc1.next(dt);
	sample += osc2.next(dt);
	sample *= _envelope.next(dt);

	return sample;
}

void EmbeddedSoundSource::reset()
{
	ISoundSource::reset();
	_pwmOscillator.reset();
	_sawtoothOscillator.reset();
}

void EmbeddedSoundSource::configure(Midi::Note note, int8_t octave, float amplitude)
{
	ISoundSource::configure(note, octave, amplitude);

	_pwmOscillator.configure(note, octave, amplitude);
	_sawtoothOscillator.configure(note, octave, amplitude);
}

} // end BOSSCorp::TalkBox::SoundSources



