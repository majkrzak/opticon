#include "usb_descriptors.h"
#include "usb_types.h"

#include <stdint.h>

device_descriptor_t device_descriptor = {
    .bLength = sizeof(device_descriptor_t),
    .bDescriptorType = DEVICE_DESCRIPTOR,
    .bcdUSB = 0x0200,
    .bDeviceClass = CC_VIDEO,
    .bDeviceSubClass = SC_VIDEOSTREAMING,
    .bDeviceProtocol = PC_PROTOCOL_15,
    .bMaxPacketSize = 32,
    .idVendor = 0x6431,  // sha256(majkrzak)[0:1]
    .idProduct = 0xdeb2, // sha256(optikos)[0:1]
    .bcdDevice = 0x0000,
    .iManufacturer = 1,
    .iProduct = 1,
    .iSerialNumber = 1,
    .bNumConfigurations = 1,
};

configuration_descriptor_t configuration_descriptor = {
    .bLength = sizeof(configuration_descriptor_t),
    .bDescriptorType = CONFIGURATION_DESCRIPTOR,
    .wTotalLength = sizeof(configuration_descriptor_t),
    .bNumInterfaces = 0,
    .bConfigurationValue = 1,
    .iConfiguration = 1,
    .bmAttributes = 0,
    .bMaxPower = 250,
};

string_descriptor_t string_descriptor_zero = {
    .bLength = 2 + 2 * 1,
    .bDescriptorType = STRING_DESCRIPTOR,
    .bString =
        {
            0x040,
        },
};

string_descriptor_t string_descriptor_one = {
    .bLength = 2 + 2 * 8,
    .bDescriptorType = STRING_DESCRIPTOR,
    .bString =
        {
            'm',
            'a',
            'j',
            'k',
            'r',
            'z',
            'a',
            'k',
        },
};
