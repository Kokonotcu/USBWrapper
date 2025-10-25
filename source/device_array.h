#include <iostream>
#include <vector>
#include "device.h"

class DeviceArray
{
public:
	static void print_strings(libusb_device* dev, const struct libusb_device_descriptor& dd);
public:
	libusb_context** GetContext()
	{
		return context;
	}
	void SetContext(libusb_context** ctx)
	{
		context = ctx;
	}
	libusb_init_option& GetOptions()
	{
		return options;
	}
	void SetDevices(libusb_device** dev)
	{
		devices = dev;
	}
	libusb_device* GetDevice(int index)
	{
		return devices[index];
	}
	libusb_device** GetDevices()
	{
		return devices;
	}

private:
	libusb_context** context = nullptr; 
	libusb_init_option options;
	libusb_device** devices;
};