#pragma once
#include <libusb.h>

bool HasMidiInterface(libusb_device* dev);
bool HasMouseInterface(libusb_device* dev);
bool HasKeyboardInterface(libusb_device* dev);

class Device
{
public:

protected:
	libusb_device* device = nullptr; 
};

class MidiDevice : public Device
{
public:
	MidiDevice(libusb_device* dev)
	{
		device = dev;
	}
private:
};

class MouseDevice : public Device
{
public:
	MouseDevice(libusb_device* dev)
	{
		device = dev;
	}
private:
};