#include "Audio.h"

bool Audio::Init()
{
    spec = { SDL_AUDIO_F32, 2, Oscillator::sampleRate };
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, Synthesizer::AudioCallback, nullptr);
    SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(stream));

    midi.Init();
    Synthesizer::Init();

    try
    {
        unsigned int portCount = midi.GetRtMidi()->getPortCount();

        // 1. List all devices to the console so you can see them
        std::cout << "Available MIDI Ports:\n";
        int bestPort = -1;

        for (unsigned int i = 0; i < portCount; i++) {
            std::string name = midi.GetRtMidi()->getPortName(i);
            std::cout << "  [" << i << "] " << name << "\n";

            if (name.find("MIDI"))
            {
                bestPort = i;
            }
        }

        // 2. Open the best guess (or default to 0)
        if (portCount > 0)
        {
            int targetPort = (bestPort != -1) ? bestPort : 0;

            midi.GetRtMidi()->openPort(bestPort);
            midi.GetRtMidi()->setCallback(&MIDI::midiCallback, nullptr);
            midi.GetRtMidi()->ignoreTypes(false, false, false);

            std::cout << "Connected to MIDI Device: " << midi.GetRtMidi()->getPortName(targetPort) << "\n";
        }
        else
        {
            std::cout << "No MIDI devices found.\n";
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
