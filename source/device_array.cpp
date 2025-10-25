#include "device_array.h"

void DeviceArray::print_strings(libusb_device* dev, const libusb_device_descriptor& dd)
{
	libusb_device_handle* h = NULL;
	int open_rc = libusb_open(dev, &h);

#ifdef DEBUG

	if (open_rc != 0)
	{
		printf("  (open failed: %d)\n", open_rc);
		printf("  iMan/iProd/iSer: %u/%u/%u\n", dd.iManufacturer, dd.iProduct, dd.iSerialNumber);
		printf("  (open failed: %s)\n", libusb_error_name(open_rc));
		return;
	}

	unsigned char buf[256];

	if (dd.iManufacturer) 
	{
		int n = libusb_get_string_descriptor_ascii(h, dd.iManufacturer, buf, sizeof(buf));
		if (n > 0) printf("  Manufacturer: %s\n", buf);
	}
	if (dd.iProduct) 
	{
		int n = libusb_get_string_descriptor_ascii(h, dd.iProduct, buf, sizeof(buf));
		if (n > 0) printf("  Product     : %s\n", buf);
	}
	if (dd.iSerialNumber) 
	{
		int n = libusb_get_string_descriptor_ascii(h, dd.iSerialNumber, buf, sizeof(buf));
		if (n > 0) printf("  Serial      : %s\n", buf);
	}

#endif // DEBUG

	libusb_close(h);
}
