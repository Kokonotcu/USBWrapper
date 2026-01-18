#pragma once
#include <rtmidi/RtMidi.h> // Cross-platform MIDI lib
#include "Synthesizer.h"

class MIDI
{
public:
	void Init();
	RtMidiIn* GetRtMidi();
	static void midiCallback(double deltatime, std::vector<unsigned char>* message, void* userData);
	void Shutdown();

private:
	RtMidiIn* midiIn = nullptr;
};