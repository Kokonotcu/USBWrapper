#pragma once
#include "Oscillator.h"

namespace Synthesizer
{
	void Init();

	void ProcessNoteOn(int note, int velocity);
	void ProcessNoteOff(int note);
	std::vector<Oscillator::VoiceState> GetActiveVoices();

	Oscillator* GetOscillator(int index);

	// SDL Audio Callback (The Sound Engine)
	void AudioCallback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount);
};