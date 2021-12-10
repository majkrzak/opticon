#include "usb_descriptors.h"
#include "usb_types.h"

#include <stdint.h>

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

configuration_descriptor_bundle_t configuration_descriptor_bundle = {
    .configuration_descriptor =
        {
            .bLength =
                sizeof configuration_descriptor_bundle.configuration_descriptor,
            .bDescriptorType = CONFIGURATION_DESCRIPTOR,
            .wTotalLength = sizeof configuration_descriptor_bundle,
            .bNumInterfaces = 2,
            .bConfigurationValue = 1,
            .iConfiguration = 1,
            .bmAttributes = 0,
            .bMaxPower = 250,
        },
    .interface_association_descriptor =
        {
            .bLength = sizeof configuration_descriptor_bundle
                           .interface_association_descriptor,
            .bDescriptorType = INTERFACE_ASSOCIATION_DESCRIPTOR,
            .bFirstInterface = 0,
            .bInterfaceCount = 2,
            .bFunctionClass = CC_VIDEO,
            .bFunctionSubClass = SC_VIDEO_INTERFACE_COLLECTION,
            .bFunctionProtocol = PC_PROTOCOL_UNDEFINED,
            .iFunction = 1,
        },
    .video_control_interface_descriptor =
        {
            .bLength = sizeof configuration_descriptor_bundle
                           .video_control_interface_descriptor,
            .bDescriptorType = INTERFACE_DESCRIPTOR,
            .bInterfaceNumber = 0,
            .bAlternateSetting = 0,
            .bNumEndpoints = 0,
            .bInterfaceClass = CC_VIDEO,
            .bInterfaceSubClass = SC_VIDEOCONTROL,
            .bInterfaceProtocol = PC_PROTOCOL_15,
            .iInterface = 1,
        },
    .video_control_interface_descriptor_bundle =
        {
            .video_control_interface_descriptor_header =
                {
                    .bLength = sizeof configuration_descriptor_bundle
                                   .video_control_interface_descriptor_bundle
                                   .video_control_interface_descriptor_header,
                    .bDescriptorType = CS_INTERFACE,
                    .bDescriptorSubType = VC_HEADER,
                    .bcdUVC = 0x150,
                    .wTotalLength =
                        sizeof configuration_descriptor_bundle
                            .video_control_interface_descriptor_bundle,
                    .dwClockFrequency = F_CPU,
                    .bInCollection = 1,
                    .baInterfaceNr = {1},
                },
            .camera_terminal_descriptor =
                {
                    .bLength = sizeof configuration_descriptor_bundle
                                   .video_control_interface_descriptor_bundle
                                   .camera_terminal_descriptor,
                    .bDescriptorType = CS_INTERFACE,
                    .bDescriptorSubType = VC_INPUT_TERMINAL,
                    .bTerminalID = 1,
                    .wTerminalType = ITT_CAMERA,
                    .bAssocTerminal = 2,
                    .iTerminal = 1,
                    .wObjectiveFocalLengthMin = 0,
                    .wObjectiveFocalLengthMax = 0,
                    .wOcularFocalLength = 0,
                    .bControlSize =
                        sizeof configuration_descriptor_bundle
                            .video_control_interface_descriptor_bundle
                            .camera_terminal_descriptor.bmControls,
                    .bmControls =
                        {
                            0,
                            0,
                            0,
                        },
                },
            .streaming_terminal_descriptor =
                {
                    .bLength = sizeof configuration_descriptor_bundle
                                   .video_control_interface_descriptor_bundle
                                   .streaming_terminal_descriptor,
                    .bDescriptorType = CS_INTERFACE,
                    .bDescriptorSubType = VC_OUTPUT_TERMINAL,
                    .bTerminalID = 2,
                    .wTerminalType = TT_STREAMING,
                    .bAssocTerminal = 1,
                    .bSourceID = 1,
                    .iTerminal = 1,
                },
        },
    .video_streaming_interface_descriptor =
        {
            .bLength = sizeof configuration_descriptor_bundle
                           .video_streaming_interface_descriptor,
            .bDescriptorType = INTERFACE_DESCRIPTOR,
            .bInterfaceNumber = 1,
            .bAlternateSetting = 0,
            .bNumEndpoints = 1,
            .bInterfaceClass = CC_VIDEO,
            .bInterfaceSubClass = SC_VIDEOSTREAMING,
            .bInterfaceProtocol = PC_PROTOCOL_15,
            .iInterface = 1,
        },
    .video_streaming_interface_descriptor_bundle =
        {
            .video_streaming_interface_descriptor_header =
                {
                    .bLength = sizeof configuration_descriptor_bundle
                                   .video_streaming_interface_descriptor_bundle
                                   .video_streaming_interface_descriptor_header,
                    .bDescriptorType = CS_INTERFACE,
                    .bDescriptorSubtype = VS_INPUT_HEADER,
                    .bNumFormats = 1,
                    .wTotalLength =
                        sizeof configuration_descriptor_bundle
                            .video_streaming_interface_descriptor_bundle,
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
                },
            .uncompressed_video_format_descriptor =
                {
                    .bLength = sizeof configuration_descriptor_bundle
                                   .video_streaming_interface_descriptor_bundle
                                   .uncompressed_video_format_descriptor,
                    .bDescriptorType = CS_INTERFACE,
                    .bDescriptorSubtype = VS_FORMAT_UNCOMPRESSED,
                    .bFormatIndex = 1,
                    .bNumFrameDescriptors = 1,
                    .guidFormat =
                        {
                            0x59,
                            0x55,
                            0x59,
                            0x32,
                            0x00,
                            0x00,
                            0x10,
                            0x00,
                            0x80,
                            0x00,
                            0x00,
                            0xAA,
                            0x00,
                            0x38,
                            0x9B,
                            0x71,
                        },
                    .bBitsPerPixel = 8,      // TODO
                    .bDefaultFrameIndex = 0, // TODO dunno
                    .bAspectRatioX = 1,
                    .bAspectRatioY = 1,
                    .bmInterlaceFlags = 0, // TODO ensure
                    .bCopyProtect = 0,
                },
            .uncompressed_video_frame_descriptor =
                {
                    .bLength = sizeof configuration_descriptor_bundle
                                   .video_streaming_interface_descriptor_bundle
                                   .uncompressed_video_frame_descriptor,
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
                },
            .video_streaming_endpoint_descriptor =
                {
                    .bLength = sizeof configuration_descriptor_bundle
                                   .video_streaming_interface_descriptor_bundle
                                   .video_streaming_endpoint_descriptor,
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
                },
        },
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

video_probe_controls_t video_probe_controls = {
    .bmHint =
        {
            .fixed_dwFrameInterval = ON,
            .fixed_wKeyFrameRate = ON,
            .fixed_wPFrameRate = ON,
            .fixed_wCompQuality = ON,
            .fixed_wCompWindowSize = ON,
        },
    .bFormatIndex = 1,
    .bFrameIndex = 1,
    .dwFrameInterval = 1000000,
    .wKeyFrameRate = 0,
    .wPFrameRate = 0,
    .wCompQuality = 0,
    .wCompWindowSize = 0,
    .wDelay = 0,
    .dwMaxVideoFrameSize = 0,
    .dwMaxPayloadTransferSize = 0,
    .dwClockFrequency = 0,
    .bmFramingInfo = 0,
    .bPreferedVersion = 0,
    .bMinVersion = 0,
    .bMaxVersion = 0,
    .bUsage = 0,
    .bBitDepthLuma = 0,
    .bmSettings = 0,
    .bMaxNumberOfRefFramesPlus1 = 0,
    .bmRateControlModes = 0,
    .bmLayoutPerStream = {},
};
