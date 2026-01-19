#include "Oscilator.h"

#define MASTER_VOLUME 0.2f

void Oscilator::Init()
{

    currentWave = std::make_unique<SineWave>();
    for (auto& v : voices)
        v.active = false;
    
}

void Oscilator::Oscilate(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount)
{
    int sampleCount = additional_amount / sizeof(float);
    std::vector<float> buffer(sampleCount);

    std::lock_guard<std::mutex> lock(mut);

    for (int i = 0; i < sampleCount; ++i)
    {
        float sample = 0.0f;
        for (auto& voice : voices)
        {
            if (voice.active)
            {
                float freq = CalculateFrequency(voice.note);
                sample += voice.amplitude * currentWave->Calculate(voice.phase) * MASTER_VOLUME;
                voice.phase += 2.0f * 3.14159f * freq / 48000.0f;
                if (voice.phase > 2.0f * 3.14159f)
                    voice.phase -= 2.0f * 3.14159f;
            }
        }
        buffer[i] = sample;
    }

    SDL_PutAudioStreamData(stream, buffer.data(), buffer.size() * sizeof(float));
}

void Oscilator::NoteOn(int note, int velocity)
{
    std::lock_guard<std::mutex> lock(mut);
    voices[note].active = true;
    voices[note].note = note;
    voices[note].phase = 0.0f;

    // We divide by 127.0f to normalize it.
    voices[note].amplitude = (float)velocity / 127.0f;
}

void Oscilator::NoteOff(int note)
{
    std::lock_guard<std::mutex> lock(mut);
    voices[note].active = false;
}

void Oscilator::SetWaveform(std::unique_ptr<Wave> wave)
{
    currentWave.reset();
	currentWave = std::move(wave);
}

std::vector<Oscilator::VoiceState> Oscilator::GetActiveVoices()
{
    std::lock_guard<std::mutex> lock(mut);
    std::vector<VoiceState> states;
    for (const auto& v : voices)
        states.push_back({ v.active, v.note });
    return states;
}

float Oscilator::CalculateFrequency(int note)
{
    return 440.0f * std::pow(2.0f, (note - 69) / 12.0f);
}

    
