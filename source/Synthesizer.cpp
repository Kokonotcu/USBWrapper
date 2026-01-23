#include "Synthesizer.h"

namespace Synthesizer
{
	namespace 
	{
		std::vector<std::unique_ptr<Oscillator>> oscilators;
		bool activeNotes[127] = {false};
	}

	void Init()
	{
		oscilators.push_back(std::make_unique<Oscillator>());
		oscilators[0]->Init();
		oscilators[0]->SetWaveform(std::make_unique<SineWave>());
	}

	void ProcessNoteOn(int note, int velocity)
	{
		if (activeNotes[note])
			return;
		for (auto& osc : oscilators)
		{
			osc->NoteOn(note, velocity);
			activeNotes[note] = true;
		}
	}

	void ProcessNoteOff(int note)
	{
		if (!activeNotes[note])
			return;
		for (auto& osc : oscilators)
		{
			osc->NoteOff(note);
			activeNotes[note] = false;
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

	Oscillator* GetOscillator(int index)
	{
		if (index >= 0 && index < oscilators.size())
		{
			return oscilators[index].get();
		}
		return nullptr;
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