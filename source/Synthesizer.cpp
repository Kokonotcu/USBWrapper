#include "Synthesizer.h"

namespace Synthesizer
{
	namespace 
	{
		std::vector<std::unique_ptr<Oscilator>> oscilators;
	}

	void Init()
	{
		oscilators.push_back(std::make_unique<Oscilator>());
		oscilators[0]->Init();
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

	std::vector<Oscilator::VoiceState> GetActiveVoices()
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
		for(auto& osc : oscilators)
		{
			osc->Oscilate(userdata, stream, additional_amount, total_amount);
		}
	}
}