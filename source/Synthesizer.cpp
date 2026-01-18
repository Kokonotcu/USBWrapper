#include "Synthesizer.h"

void Synthesizer::Init() 
{
    for (auto& v : voices)
        v.active = false;
}

void Synthesizer::NoteOn(int note)
{
    std::lock_guard<std::mutex> lock(mut);
    voices[note].active = true;
    voices[note].note = note;
    voices[note].phase = 0.0f;
}

void Synthesizer::NoteOff(int note)
{
    std::lock_guard<std::mutex> lock(mut);
    voices[note].active = false;
}

std::vector<Synthesizer::VoiceState> Synthesizer::GetActiveVoices()
{
    std::lock_guard<std::mutex> lock(mut);
    std::vector<VoiceState> states;
    for (const auto& v : voices)
        states.push_back({ v.active, v.note });
    return states;
}

void Synthesizer::AudioCallback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount)
{
    Synthesizer* synth = (Synthesizer*)userdata;
    int sampleCount = additional_amount / sizeof(float);
    std::vector<float> buffer(sampleCount);

    {
        std::lock_guard<std::mutex> lock(synth->mut);
        for (int i = 0; i < sampleCount; ++i)
        {
            float sample = 0.0f;
            for (auto& voice : synth->voices)
            {
                if (voice.active)
                {
                    // Standard Sine Wave Formula
                    float freq = 440.0f * std::pow(2.0f, (voice.note - 69) / 12.0f);
                    sample += 0.2f * std::sin(voice.phase);
                    voice.phase += 2.0f * 3.14159f * freq / 48000.0f;
                    if (voice.phase > 2.0f * 3.14159f)
                        voice.phase -= 2.0f * 3.14159f;
                }
            }
            buffer[i] = sample;
        }
    }
    SDL_PutAudioStreamData(stream, buffer.data(), buffer.size() * sizeof(float));
}
