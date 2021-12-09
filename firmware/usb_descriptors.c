#include "usb_descriptors.h"
#include "usb_types.h"

#include <stdint.h>

// 3.2 Device Descriptor
device_descriptor_t device_descriptor = {
    .bLength = sizeof(device_descriptor_t),
    .bDescriptorType = DEVICE_DESCRIPTOR,
    .bcdUSB = 0x0200,
    .bDeviceClass = CC_MISCELLANEOUS,
    .bDeviceSubClass = SC_COMMON_CLASS,
    .bDeviceProtocol = PC_INTERFACE_ASSOCIATION_DESCRIPTOR,
    .bMaxPacketSize = 32,
    .idVendor = 0x6431,  // sha256(majkrzak)[0:1]
    .idProduct = 0xdeb2, // sha256(optikos)[0:1]
    .bcdDevice = 0x0000,
    .iManufacturer = 1,
    .iProduct = 1,
    .iSerialNumber = 1,
    .bNumConfigurations = 1,
};

// 3.4 Configuration Descriptor
configuration_descriptor_t configuration_descriptor = {
    .bLength = sizeof configuration_descriptor,
    .bDescriptorType = CONFIGURATION_DESCRIPTOR,
    .wTotalLength = sizeof configuration_descriptor, // TODO calculate properly!
    .bNumInterfaces = 0,
    .bConfigurationValue = 1,
    .iConfiguration = 1,
    .bmAttributes = 0,
    .bMaxPower = 250,
};

// 3.6 Interface Association Descriptor
interface_association_descriptor_t interface_association_descriptor = {
    .bLength = sizeof interface_association_descriptor,
    .bDescriptorType = INTERFACE_ASSOCIATION_DESCRIPTOR,
    .bFirstInterface = 0,
    .bInterfaceCount = 2,
    .bFunctionClass = CC_VIDEO,
    .bFunctionSubClass = SC_VIDEO_INTERFACE_COLLECTION,
    .bFunctionProtocol = PC_PROTOCOL_UNDEFINED,
    .iFunction = 1,
};

// 3.7.1 Standard VC Interface Descriptor
interface_descriptor_t video_control_interface_descriptor = {
    .bLength = sizeof video_control_interface_descriptor,
    .bDescriptorType = INTERFACE_DESCRIPTOR,
    .bInterfaceNumber = 0,
    .bAlternateSetting = 0,
    .bNumEndpoints = 0,
    .bInterfaceClass = CC_VIDEO,
    .bInterfaceSubClass = SC_VIDEOCONTROL,
    .bInterfaceProtocol = PC_PROTOCOL_15,
    .iInterface = 1,
};

// 3.7.2 Class-Specific VC Interface Descriptor
video_control_interface_descriptor_header_t
    video_control_interface_descriptor_header = {
        .bLength = sizeof video_control_interface_descriptor_header,
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubType = VC_HEADER,
        .bcdUVC = 0x150,
        .wTotalLength = 0, // TODO calculate properly!
        .dwClockFrequency = F_CPU,
        .bInCollection = 1,
        .baInterfaceNr = {1},
};

// 3.7.2.3 Camera Terminal Descriptor
camera_terminal_descriptor_t camera_terminal_descriptor = {
    .bLength = sizeof camera_terminal_descriptor,
    .bDescriptorType = CS_INTERFACE,
    .bDescriptorSubType = VC_OUTPUT_TERMINAL,
    .bTerminalID = 1,
    .wTerminalType = ITT_CAMERA,
    .bAssocTerminal = 2,
    .iTerminal = 1,
    .wObjectiveFocalLengthMin = 0,
    .wObjectiveFocalLengthMax = 0,
    .wOcularFocalLength = 0,
    .bControlSize = sizeof camera_terminal_descriptor.bControlSize,
    .bmControls =
        {
            0,
            0,
            0,
        },
};

streaming_terminal_descriptor_t streaming_terminal_descriptor = {
    .bLength = sizeof streaming_terminal_descriptor,
    .bDescriptorType = CS_INTERFACE,
    .bDescriptorSubType = VC_OUTPUT_TERMINAL,
    .bTerminalID = 3,
    .wTerminalType = TT_STREAMING,
    .bAssocTerminal = 0,
    .bSourceID = 1,
    .iTerminal = 1,
};

string_descriptor_t string_descriptor_zero = {
    .bLength = 2 + 2 * 1,
    .bDescriptorType = STRING_DESCRIPTOR,
    .bString =
        {
            0x0409,
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
