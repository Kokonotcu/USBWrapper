#pragma once
#include "MIDI.h"


class Audio
{
public:
	bool Init();
	void Cleanup();
	Synthesizer& GetSynthesizer();
private:
	Synthesizer synth;
	MIDI midi;
	SDL_AudioSpec spec;
	SDL_AudioStream* stream;
};