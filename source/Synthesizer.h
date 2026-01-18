#pragma once
#include <vector>
#include <cmath>
#include <mutex>
#include <SDL3/SDL.h>


class Synthesizer
{
public:
    void Init();

    void NoteOn(int note);

    void NoteOff(int note);

    // Helper for visualization
    struct VoiceState
    {
        bool active;
        int note;
    };

    std::vector<VoiceState> GetActiveVoices();

    // SDL Audio Callback (The Sound Engine)
    static void AudioCallback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount);

private:
    struct Voice
    {
        bool active;
        int note;
        float phase;
    };

    Voice voices[128] = {0}; // Polyphony for all 128 MIDI notes
    std::mutex mut;
};