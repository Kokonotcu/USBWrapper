#pragma once
#include "device_array.h"

class DeviceDetector
{
public:
	bool Initialize();
	bool Shutdown();

private:
	DeviceArray usbDev;
	libusb_context** context = nullptr;

	bool midiFound = false;
	bool mouseFound = false;
	bool keyboardFound = false;
};