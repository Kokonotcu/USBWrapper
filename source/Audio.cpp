#include "Audio.h"

bool Audio::Init()
{
    spec = { SDL_AUDIO_F32, 2, 48000 };
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, Synthesizer::AudioCallback, &synth);
    SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(stream));

    midi.Init();
    synth.Init();

    try
    {
        // Auto-connect to the first available device
        unsigned int portCount = midi.GetRtMidi()->getPortCount();
        if (portCount > 0)
        {
            midi.GetRtMidi()->openPort(0); // Open first device
            midi.GetRtMidi()->setCallback(&MIDI::midiCallback, &synth);
            midi.GetRtMidi()->ignoreTypes(false, false, false); // Don't ignore SysEx/Timing
            std::cout << "Connected to MIDI Device: " << midi.GetRtMidi()->getPortName(0) << "\n";
        }
        else
        {
            std::cout << "No MIDI devices found. (You can still use the visualizer)\n";
        }

        return true;
    }
    catch (RtMidiError& error)
    {
        error.printMessage();
    }
}

void Audio::Cleanup()
{
    midi.Shutdown();
}

Synthesizer& Audio::GetSynthesizer()
{
	return synth;
}
