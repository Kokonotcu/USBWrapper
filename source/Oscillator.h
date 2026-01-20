#pragma once
#include <SDL3/SDL_audio.h>
#include "Wave.h"
#include <vector>
#include <memory>
#include <mutex>

class Oscillator
{
public:
	Oscillator() = default;

    void Init();

    void Oscilate(std::vector<float>& buffer);

    void NoteOn(int note, int velocity);

    void NoteOff(int note);

	void SetWaveform(std::unique_ptr<Wave> wave);

public:
    // Helper for visualization
    struct VoiceState
    {
        bool active;
        int note;
    };

    std::vector<VoiceState> GetActiveVoices();

public:
    static constexpr int sampleRate = 44100;

private:
    struct Voice
    {
        bool active;
        int note;
        float phase;
        float amplitude;
    };

private:
    float CalculateFrequency(int note);

private:
    std::unique_ptr<Wave> currentWave;
    Voice voices[128] = {0};
    std::mutex mut;

};
