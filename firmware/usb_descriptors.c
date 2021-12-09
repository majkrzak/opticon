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
    .bTerminalID = 2,
    .wTerminalType = TT_STREAMING,
    .bAssocTerminal = 0,
    .bSourceID = 1,
    .iTerminal = 1,
};

interface_descriptor_t video_streaming_interface_descriptor = {
    .bLength = sizeof video_streaming_interface_descriptor,
    .bDescriptorType = INTERFACE_DESCRIPTOR,
    .bInterfaceNumber = 1,
    .bAlternateSetting = 0,
    .bNumEndpoints = 0, // TODO temporarly
    .bInterfaceClass = CC_VIDEO,
    .bInterfaceSubClass = SC_VIDEOSTREAMING,
    .bInterfaceProtocol = PC_PROTOCOL_15,
    .iInterface = 1,
};

// 3.9.2.1 Input Header Descriptor
video_streaming_interface_descriptor_header_t
    video_streaming_interface_descriptor_header = {
        .bLength = sizeof video_streaming_interface_descriptor_header,
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = VS_INPUT_HEADER,
        .bNumFormats = 1,
        .wTotalLength = 0, // TODO calculate properly!
        .bEndpointAddress =
            {
                .direction = IN,
                .number = 1,
            },
        .bmInfo =
            {
                .dynamic_format_change = OFF,
            },
        .bTerminalLink = 2,
        .bStillCaptureMethod = 0,
        .bTriggerSupport = 0,
        .bTriggerUsage = 0,
        .bControlSize = 0,
};

uncompressed_video_format_descriptor_t uncompressed_video_format_descriptor = {
    .bLength = sizeof uncompressed_video_format_descriptor,
    .bDescriptorType = CS_INTERFACE,
    .bDescriptorSubtype = VS_FORMAT_UNCOMPRESSED,
    .bFormatIndex = 1,
    .bNumFrameDescriptors = 1,
    .guidFormat = {},
    .bBitsPerPixel = 8,      // TODO
    .bDefaultFrameIndex = 0, // TODO dunno
    .bAspectRatioX = 1,
    .bAspectRatioY = 1,
    .bmInterlaceFlags = 0, // TODO ensure
    .bCopyProtect = 0,
};

uncompressed_video_frame_descriptor_t uncompressed_video_frame_descriptor = {
    .bLength = sizeof uncompressed_video_frame_descriptor,
    .bDescriptorType = CS_INTERFACE,
    .bDescriptorSubtype = VS_FRAME_UNCOMPRESSED,
    .bFrameIndex = 1,
    .bmCapabilities =
        {
            .still_image_supported = OFF,
            .fixed_frame_rate = ON,
        },
    .wWidth = 16,
    .wHeight = 16,
    .dwMinBitRate = 512ul * 512ul, // TODO calculate
    .dwMaxBitRate = 512ul * 512ul,
    .dwMaxVideoFrameBufferSize = 16 * 16 * 3,
    .dwDefaultFrameInterval = 1000000,
    .bFrameIntervalType = 0,
    .dwMinFrameInterval = 1000000,
    .dwMaxFrameInterval = 1000000,
    .dwFrameIntervalStep = 0,
};

endpoint_descriptor_t video_streaming_endpoint_descriptor = {
    .bLength = sizeof video_streaming_endpoint_descriptor,
    .bDescriptorType = ENDPOINT_DESCRIPTOR,
    .bEndpointAddress =
        {
            .direction = IN,
            .number = 1,
        },
    .bmAttributes =
        {
            .transfer_type = BULK,
        },
    .wMaxPacketSize = 64, // TODO fixme
    .bInterval = 100,
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
