#include "device_array.h"

int main(void) 
{
	DeviceArray usbDev;
	libusb_context** context = nullptr;
    bool midiFound = false;
	bool mouseFound = false;
	bool keyboardFound = false;
    
    if (libusb_init_context(context, &usbDev.GetOptions(), 0) != 0)
    {
        fprintf(stderr, "libusb_init failed\n");
        return 1;
    }
	usbDev.SetContext(context);

    libusb_device** tempDevices;
    ssize_t count = libusb_get_device_list(NULL, &tempDevices);
	usbDev.SetDevices(tempDevices);

    if (count < 0) 
    {
        fprintf(stderr, "get_device_list failed\n");
        libusb_exit(NULL);
        return 1;
    }

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
    libusb_exit(NULL);
    return 0;
}