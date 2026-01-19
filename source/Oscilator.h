#pragma once
#include <vector>
#include <mutex>
#include <SDL3/SDL.h>
#include "Wave.h"

namespace Oscilator
{
    void Init();

    void NoteOn(int note, int velocity);

    void NoteOff(int note);

	void SetWaveform(std::unique_ptr<Wave> wave);

    // Helper for visualization
    struct VoiceState
    {
        bool active;
        int note;
    };

    std::vector<VoiceState> GetActiveVoices();

    // SDL Audio Callback (The Sound Engine)
    void AudioCallback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount);

};
