#pragma once
#include "MIDI.h"


class Audio
{
public:
	bool Init();
	void Cleanup();
private:
	MIDI midi;
	SDL_AudioSpec spec;
	SDL_AudioStream* stream;
};