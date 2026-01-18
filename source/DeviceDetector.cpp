#include "DeviceDetector.h"

bool DeviceDetector::Initialize()
{
    if (libusb_init_context(context, &usbDev.GetOptions(), 0) != 0)
    {
        fprintf(stderr, "libusb_init failed\n");
        return false;
    }
    usbDev.SetContext(context);

    libusb_device** tempDevices;
    ssize_t count = libusb_get_device_list(NULL, &tempDevices);
    usbDev.SetDevices(tempDevices);

    if (count < 0)
    {
        fprintf(stderr, "get_device_list failed\n");
        libusb_exit(NULL);
        return false;
    }

    std::unique_ptr<MidiDevice> midiDevice;

    printf("USB devices found: %zd\n", count);
    for (ssize_t i = 0; i < count; ++i)
    {
        libusb_device_descriptor d;
        if (libusb_get_device_descriptor(usbDev.GetDevice(i), &d) == 0)
        {
            printf("%04x:%04x \n", d.idVendor, d.idProduct);
            DeviceArray::print_strings(usbDev.GetDevice(i), d);

            if (HasMidiInterface(usbDev.GetDevice(i))) {
                midiFound = true;
                printf("  -> MIDI interface detected!\n");

                libusb_ref_device(usbDev.GetDevice(i));

                midiDevice = std::make_unique<MidiDevice>(usbDev.GetDevice(i));
            }
            if (HasMouseInterface(usbDev.GetDevice(i)))
            {
                mouseFound = true;
                printf("  -> Mouse interface detected!\n");
            }
            if (HasKeyboardInterface(usbDev.GetDevice(i)))
            {
                keyboardFound = true;
                printf("  -> Keyboard interface detected!\n");
            }

        }
    }

    if (!midiFound)
        printf("No MIDI device found.\n");

    libusb_free_device_list(usbDev.GetDevices(), 1);
	return true;
}

bool DeviceDetector::Shutdown()
{
	libusb_exit(NULL);
	return true;
}
