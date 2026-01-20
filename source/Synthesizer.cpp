#include "Synthesizer.h"

namespace Synthesizer
{
	namespace 
	{
		std::vector<std::unique_ptr<Oscillator>> oscilators;
	}

	void Init()
	{
		oscilators.push_back(std::make_unique<Oscillator>());
		oscilators[0]->Init();
		oscilators[0]->SetWaveform(std::make_unique<SineWave>());

		oscilators.push_back(std::make_unique<Oscillator>());
		oscilators[1]->Init();
		oscilators[1]->SetWaveform(std::make_unique<NoiseWave>());
	}

	void ProcessNoteOn(int note, int velocity)
	{
		for (auto& osc : oscilators)
		{
			osc->NoteOn(note, velocity);
		}
	}

	void ProcessNoteOff(int note)
	{
		for (auto& osc : oscilators)
		{
			osc->NoteOff(note);
		}
	}

	std::vector<Oscillator::VoiceState> GetActiveVoices()
	{
		// For simplicity, we return the voices from the first oscilator
		if (!oscilators.empty())
		{
			return oscilators[0]->GetActiveVoices();
		}
		return {};
	}

	void AudioCallback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount)
	{
		int sampleCount = additional_amount / sizeof(float);
		std::vector<float> buffer(sampleCount);

		for(auto& osc : oscilators)
		{
			osc->Oscilate(buffer);
		}

		SDL_PutAudioStreamData(stream, buffer.data(), buffer.size() * sizeof(float));
	}
}