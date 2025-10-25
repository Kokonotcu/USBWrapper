#include "device.h"

bool HasMidiInterface(libusb_device* dev) 
{
    struct libusb_config_descriptor* cfg = nullptr;
    if (libusb_get_active_config_descriptor(dev, &cfg) != 0)
        return false;

    bool found = false;
    for (int i = 0; i < cfg->bNumInterfaces && !found; ++i) 
    {
        const libusb_interface* itf = &cfg->interface[i];
        for (int a = 0; a < itf->num_altsetting; ++a) 
        {
            const libusb_interface_descriptor* id = &itf->altsetting[a];
            if (id->bInterfaceClass == 0x01 && id->bInterfaceSubClass == 0x03) 
            {
                found = true;
                break;
            }
        }
    }
    libusb_free_config_descriptor(cfg);
    return found;
}

bool HasMouseInterface(libusb_device* dev)
{
    struct libusb_config_descriptor* cfg = nullptr;
    if (libusb_get_active_config_descriptor(dev, &cfg) != 0)
        return false;

    bool found = false;
    for (int i = 0; i < cfg->bNumInterfaces && !found; ++i)
    {
        const libusb_interface* itf = &cfg->interface[i];
        for (int a = 0; a < itf->num_altsetting; ++a)
        {
            const libusb_interface_descriptor* id = &itf->altsetting[a];
            if (id->bInterfaceClass == 0x03 &&  // HID
                id->bInterfaceSubClass == 0x01 &&  // Boot Interface
                id->bInterfaceProtocol == 0x02)
            {
                found = true;
                break;
            }
        }
    }
    libusb_free_config_descriptor(cfg);
    return found;
}

bool HasKeyboardInterface(libusb_device* dev)
{
    struct libusb_config_descriptor* cfg = nullptr;
    if (libusb_get_active_config_descriptor(dev, &cfg) != 0)
        return false;

    bool found = false;
    for (int i = 0; i < cfg->bNumInterfaces && !found; ++i)
    {
        const libusb_interface* itf = &cfg->interface[i];
        for (int a = 0; a < itf->num_altsetting; ++a)
        {
            const libusb_interface_descriptor* id = &itf->altsetting[a];
            if (id->bInterfaceClass == 0x03 &&  // HID
                id->bInterfaceSubClass == 0x01 &&  // Boot Interface
                id->bInterfaceProtocol == 0x01)
            {
                found = true;
                break;
            }
        }
    }
    libusb_free_config_descriptor(cfg);
    return found;
}