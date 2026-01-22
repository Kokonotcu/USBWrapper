#include "Oscillator.h"

#define MASTER_VOLUME 0.12f

void Oscillator::Init()
{

    currentWave = std::make_unique<SineWave>();
    for (auto& v : voices)
        v.active = false;
    
}

void Oscillator::Oscilate(std::vector<float>& buffer)
{
    std::lock_guard<std::mutex> lock(mut);

    for (int i = 0; i < buffer.size(); ++i)
    {
        float sample = 0.0f;
        for (auto& voice : voices)
        {
            if (voice.active)
            {
                float freq = CalculateFrequency(voice.note);
                sample += voice.amplitude * currentWave->Calculate(voice.phase) * MASTER_VOLUME;
                voice.phase += 2.0f * M_PI * freq / sampleRate;
                if (voice.phase > 2.0f * M_PI)
                    voice.phase -= 2.0f * M_PI;
            }
        }
        buffer[i] += sample;
    }   
}

void Oscillator::NoteOn(int note, int velocity)
{
    std::lock_guard<std::mutex> lock(mut);
    voices[note].active = true;
    voices[note].note = note;
    voices[note].phase = 0.0f;

    // We divide by 127.0f to normalize it.
    voices[note].amplitude = (float)velocity / 127.0f;
}

void Oscillator::NoteOff(int note)
{
    std::lock_guard<std::mutex> lock(mut);
    voices[note].active = false;
}

void Oscillator::SetWaveform(std::unique_ptr<Wave> wave)
{
    currentWave.reset();
	currentWave = std::move(wave);
}

std::vector<Oscillator::VoiceState> Oscillator::GetActiveVoices()
{
    std::lock_guard<std::mutex> lock(mut);
    std::vector<VoiceState> states;
    for (const auto& v : voices)
        states.push_back({ v.active, v.note });
    return states;
}

float Oscillator::CalculateFrequency(int note)
{
    return 440.0f * std::pow(2.0f, (note - 69) / 12.0f);
}

    
