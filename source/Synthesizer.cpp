#include "Synthesizer.h"

#define MASTER_VOLUME 0.2f

namespace Synthesizer
{
    namespace
    {
        struct Voice
        {
            bool active;
            int note;
            float phase;
            float amplitude;
        };


		std::unique_ptr<Wave> currentWave; // Current waveform (not used in this simple example)
        Voice voices[128] = { 0 }; // Polyphony for all 128 MIDI notes
        std::mutex mut;
    }

    void Init()
    {
		currentWave = std::make_unique<SineWave>(); 
        for (auto& v : voices)
            v.active = false;
    }
    void NoteOn(int note, int velocity)
    {
        std::lock_guard<std::mutex> lock(mut);
        voices[note].active = true;
        voices[note].note = note;
        voices[note].phase = 0.0f;

        // We divide by 127.0f to normalize it.
        voices[note].amplitude = (float)velocity / 127.0f;
    }
    void NoteOff(int note)
    {
        std::lock_guard<std::mutex> lock(mut);
        voices[note].active = false;
    }

    void SetWaveform(std::unique_ptr<Wave> wave)
    {
		currentWave.reset();
		currentWave = std::move(wave);
    }

    std::vector<Synthesizer::VoiceState> GetActiveVoices()
    {
        std::lock_guard<std::mutex> lock(mut);
        std::vector<VoiceState> states;
        for (const auto& v : voices)
            states.push_back({ v.active, v.note });
        return states;
    }

    void AudioCallback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount)
    {
        int sampleCount = additional_amount / sizeof(float);
        std::vector<float> buffer(sampleCount);

        std::lock_guard<std::mutex> lock(mut);

		SetWaveform(std::make_unique<NoiseWave>());
        for (int i = 0; i < sampleCount; ++i)
        {
            float sample = 0.0f;
            for (auto& voice : voices)
            {
                if (voice.active)
                {
                    // Standard Sine Wave Formula
                    float freq = 440.0f * std::pow(2.0f, (voice.note - 69) / 12.0f);
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
}