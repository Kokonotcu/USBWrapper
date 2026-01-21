#include "MIDI.h"
#include "Graphics.h"

void MIDI::midiCallback(double deltatime, std::vector<unsigned char>* message, void* userData)
{
    // MIDI Packet: [Status, Note, Velocity]
    if (message->size() >= 3)
    {
        int status = (int)message->at(0);
        int note = (int)message->at(1);
        int velocity = (int)message->at(2);

        // Note On (0x90)
        if ((status & 0xF0) == 0x90 && velocity > 0)
        {
            Synthesizer::ProcessNoteOn(note, velocity);
        }
        // Note Off (0x80)
        else if ((status & 0xF0) == 0x80 || ((status & 0xF0) == 0x90 && velocity == 0))
        {
            Synthesizer::ProcessNoteOff(note);
        }
    }
}

void MIDI::Init()
{
    midiIn = new RtMidiIn();
}

RtMidiIn* MIDI::GetRtMidi()
{
    return midiIn;
}

void MIDI::Shutdown()
{
    if (midiIn)
        delete midiIn;
}
