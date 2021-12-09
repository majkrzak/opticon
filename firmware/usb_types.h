#pragma once

#include <stdint.h>

#define USB_STRUCT                                                             \
  __attribute__((packed, scalar_storage_order("little-endian")))

typedef enum {
  OFF = 0,
  ON = 1,
} on_off_t;

typedef struct USB_STRUCT {
  uint8_t number : 4;
  uint8_t _ : 3;
  enum {
    OUT = 0,
    IN = 1,
  } direction : 1;
} endpoint_address_t;

typedef struct {
  struct {
    enum {
      DEVICE = 0,
      INTERFACE = 1,
      ENDPOINT = 2,
      OTHER = 3,
    } recipient : 5;
    enum {
      STANDARD = 0,
      CLASS = 1,
      VENDOR = 2,
    } type : 2;
    enum type {
      HOST_TO_DEVICE = 0,
      DEVICE_TO_HOST = 1,
    } direction : 1;
  } bmRequestType;
  enum {
    GET_STATUS = 0,
    CLEAR_FEATURE = 1,
    SET_FEATURE = 3,
    SET_ADDRESS = 5,
    GET_DESCRIPTOR = 6,
    SET_DESCRIPTOR = 7,
    GET_CONFIGURATION = 8,
    SET_CONFIGURATION = 9,
    GET_INTERFACE = 10,
    SET_INTERFACE = 11,
    SYNCH_FRAME = 12,
    SET_SEL = 48,
    SET_ISOCH_DELAY = 49,
  } bRequest : 8;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} USB_STRUCT setup_request_t;

typedef union {
  setup_request_t t;
  uint8_t b[sizeof(setup_request_t)];
} setup_request;

enum {
  DEVICE_DESCRIPTOR = 0x01,
  CONFIGURATION_DESCRIPTOR = 0x02,
  STRING_DESCRIPTOR = 0x03,
  INTERFACE_DESCRIPTOR = 0x04,
  ENDPOINT_DESCRIPTOR = 0x05,
  DEVICE_QUALIFIER_DESCRIPTOR = 0x06,
  OTHER_SPEED_CONFIGURATION_DESCRIPTOR = 0x07,
  INTERFACE_POWER_DESCRIPTOR = 0x08,
  OTG_DESCRIPTOR = 0x09,
  DEBUG_DESCRIPTOR = 0x0A,
  INTERFACE_ASSOCIATION_DESCRIPTOR = 0x0B,
  BOS_DESCRIPTOR = 0x0C,
  DEVICE_CAPABILITY_DESCRIPTOR = 0x0D,
  SUPERSPEED_USB_ENDPOINT_COMPANION_DESCRIPTOR = 0x0E,
};

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t bcdUSB;
  uint8_t bDeviceClass;
  uint8_t bDeviceSubClass;
  uint8_t bDeviceProtocol;
  uint8_t bMaxPacketSize;
  uint16_t idVendor;
  uint16_t idProduct;
  uint16_t bcdDevice;
  uint8_t iManufacturer;
  uint8_t iProduct;
  uint8_t iSerialNumber;
  uint8_t bNumConfigurations;
} device_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t wTotalLength;
  uint8_t bNumInterfaces;
  uint8_t bConfigurationValue;
  uint8_t iConfiguration;
  uint8_t bmAttributes;
  uint8_t bMaxPower;
} configuration_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bFirstInterface;
  uint8_t bInterfaceCount;
  uint8_t bFunctionClass;
  uint8_t bFunctionSubClass;
  uint8_t bFunctionProtocol;
  uint8_t iFunction;
} interface_association_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bInterfaceNumber;
  uint8_t bAlternateSetting;
  uint8_t bNumEndpoints;
  uint8_t bInterfaceClass;
  uint8_t bInterfaceSubClass;
  uint8_t bInterfaceProtocol;
  uint8_t iInterface;
} interface_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubType;
  uint16_t bcdUVC;
  uint16_t wTotalLength;
  uint32_t dwClockFrequency;
  uint8_t bInCollection;
  uint8_t baInterfaceNr[1];
} video_control_interface_descriptor_header_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubType;
  uint8_t bTerminalID;
  uint16_t wTerminalType;
  uint8_t bAssocTerminal;
  uint8_t iTerminal;
  uint16_t wObjectiveFocalLengthMin;
  uint16_t wObjectiveFocalLengthMax;
  uint16_t wOcularFocalLength;
  uint8_t bControlSize;
  uint8_t bmControls[3];
} camera_terminal_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubType;
  uint8_t bTerminalID;
  uint16_t wTerminalType;
  uint8_t bAssocTerminal;
  uint8_t bSourceID;
  uint8_t iTerminal;
} streaming_terminal_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubtype;
  uint8_t bNumFormats;
  uint16_t wTotalLength;
  endpoint_address_t bEndpointAddress;
  struct {
    on_off_t dynamic_format_change : 1;
    uint8_t _ : 7;
  } bmInfo;
  uint8_t bTerminalLink;
  uint8_t bStillCaptureMethod;
  uint8_t bTriggerSupport;
  uint8_t bTriggerUsage;
  uint8_t bControlSize;
} video_streaming_interface_descriptor_header_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubtype;
  uint8_t bFormatIndex;
  uint8_t bNumFrameDescriptors;
  uint8_t guidFormat[16];
  uint8_t bBitsPerPixel;
  uint8_t bDefaultFrameIndex;
  uint8_t bAspectRatioX;
  uint8_t bAspectRatioY;
  uint8_t bmInterlaceFlags;
  uint8_t bCopyProtect;
} uncompressed_video_format_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubtype;
  uint8_t bFrameIndex;
  struct {
    on_off_t still_image_supported : 1;
    on_off_t fixed_frame_rate : 1;
    uint8_t _ : 6;
  } bmCapabilities;
  uint16_t wWidth;
  uint16_t wHeight;
  uint32_t dwMinBitRate;
  uint32_t dwMaxBitRate;
  uint32_t dwMaxVideoFrameBufferSize;
  uint32_t dwDefaultFrameInterval;
  uint8_t bFrameIntervalType;
  uint32_t dwMinFrameInterval;
  uint32_t dwMaxFrameInterval;
  uint32_t dwFrameIntervalStep;
} uncompressed_video_frame_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  endpoint_address_t bEndpointAddress;
  struct {
    enum {
      CONTROL = 0,
      ISOCHRONOUS = 1,
      BULK = 2,
      INTERRUPT = 3,
    } transfer_type : 2;
    enum {
      NO_SYNCHRONISATION = 0,
      ASYNCHRONOUS = 1,
      ADAPTIVE = 2,
      SYNCHRONOUS = 3,
    } synchronisation_type : 2;
    enum {
      DATA_ENDPOINT = 0,
      FEEDBACK_ENDPOINT = 1,
      EXPLICIT_FEEDBACK_DATA_ENDPOINT = 2,
    } usage_type : 2;
  } bmAttributes;
  uint16_t wMaxPacketSize;
  uint8_t bInterval;
} endpoint_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t bString[];
} string_descriptor_t;

enum {
  CC_MISCELLANEOUS = 0xEF,
  SC_COMMON_CLASS = 0x02,
  PC_INTERFACE_ASSOCIATION_DESCRIPTOR = 0x01,
};

enum {
  // Universal Serial Bus Device Class Definition for Video Devices Revision 1.5
  // Appendix A. Video Device Class Codes
  // A.1. Video Interface Class Code
  CC_VIDEO = 0x0E,
  // A.2. Video Interface Subclass Codes
  SC_UNDEFINED = 0x00,
  SC_VIDEOCONTROL = 0x01,
  SC_VIDEOSTREAMING = 0x02,
  SC_VIDEO_INTERFACE_COLLECTION = 0x03,
  // A.3. Video Interface Protocol Codes
  PC_PROTOCOL_UNDEFINED = 0x00,
  PC_PROTOCOL_15 = 0x01,
  // A.4. Video Class-Specific Descriptor Types
  CS_UNDEFINED = 0x20,
  CS_DEVICE = 0x21,
  CS_CONFIGURATION = 0x22,
  CS_STRING = 0x23,
  CS_INTERFACE = 0x24,
  CS_ENDPOINT = 0x25,
  // A.5. Video Class-Specific VC Interface Descriptor Subtypes
  VC_DESCRIPTOR_UNDEFINED = 0x00,
  VC_HEADER = 0x01,
  VC_INPUT_TERMINAL = 0x02,
  VC_OUTPUT_TERMINAL = 0x03,
  VC_SELECTOR_UNIT = 0x04,
  VC_PROCESSING_UNIT = 0x05,
  VC_EXTENSION_UNIT = 0x06,
  VC_ENCODING_UNIT = 0x07,
  // A.6. Video Class-Specific VS Interface Descriptor Subtypes
  VS_UNDEFINED = 0x00,
  VS_INPUT_HEADER = 0x01,
  VS_OUTPUT_HEADER = 0x02,
  VS_STILL_IMAGE_FRAME = 0x03,
  VS_FORMAT_UNCOMPRESSED = 0x04,
  VS_FRAME_UNCOMPRESSED = 0x05,
  VS_FORMAT_MJPEG = 0x06,
  VS_FRAME_MJPEG = 0x07,
  VS_FORMAT_MPEG2TS = 0x0A,
  VS_FORMAT_DV = 0x0C,
  VS_COLORFORMAT = 0x0D,
  VS_FORMAT_FRAME_BASED = 0x10,
  VS_FRAME_FRAME_BASED = 0x11,
  VS_FORMAT_STREAM_BASED = 0x12,
  VS_FORMAT_H264 = 0x13,
  VS_FRAME_H264 = 0x14,
  VS_FORMAT_H264_SIMULCAST = 0x15,
  VS_FORMAT_VP8 = 0x16,
  VS_FRAME_VP8 = 0x17,
  VS_FORMAT_VP8_SIMULCAST = 0x18,
  // A.7. Video Class-Specific Endpoint Descriptor Subtypes
  EP_UNDEFINED = 0x00,
  EP_GENERAL = 0x01,
  EP_ENDPOINT = 0x02,
  EP_INTERRUPT = 0x03,
  // A.8. Video Class-Specific Request Codes
  RC_UNDEFINED = 0x00,
  SET_CUR = 0x01,
  SET_CUR_ALL = 0x11,
  GET_CUR = 0x81,
  GET_MIN = 0x82,
  GET_MAX = 0x83,
  GET_RES = 0x84,
  GET_LEN = 0x85,
  GET_INFO = 0x86,
  GET_DEF = 0x87,
  GET_CUR_ALL = 0x91,
  GET_MIN_ALL = 0x92,
  GET_MAX_ALL = 0x93,
  GET_RES_ALL = 0x94,
  GET_DEF_ALL = 0x97,
  // A.9. Control Selector Codes
  // A.9.1. VideoControl Interface Control Selectors
  VC_CONTROL_UNDEFINED = 0x00,
  VC_VIDEO_POWER_MODE_CONTROL = 0x01,
  VC_REQUEST_ERROR_CODE_CONTROL = 0x02,
  // A.9.2. Terminal Control Selectors
  TE_CONTROL_UNDEFINED = 0x00,
  // A.9.3. Selector Unit Control Selectors
  SU_CONTROL_UNDEFINED = 0x00,
  SU_INPUT_SELECT_CONTROL = 0x01,
  // A.9.4. Camera Terminal Control Selectors
  CT_CONTROL_UNDEFINED = 0x00,
  CT_SCANNING_MODE_CONTROL = 0x01,
  CT_AE_MODE_CONTROL = 0x02,
  CT_AE_PRIORITY_CONTROL = 0x03,
  CT_EXPOSURE_TIME_ABSOLUTE_CONTROL = 0x04,
  CT_EXPOSURE_TIME_RELATIVE_CONTROL = 0x05,
  CT_FOCUS_ABSOLUTE_CONTROL = 0x06,
  CT_FOCUS_RELATIVE_CONTROL = 0x07,
  CT_FOCUS_AUTO_CONTROL = 0x08,
  CT_IRIS_ABSOLUTE_CONTROL = 0x09,
  CT_IRIS_RELATIVE_CONTROL = 0x0A,
  CT_ZOOM_ABSOLUTE_CONTROL = 0x0B,
  CT_ZOOM_RELATIVE_CONTROL = 0x0C,
  CT_PANTILT_ABSOLUTE_CONTROL = 0x0D,
  CT_PANTILT_RELATIVE_CONTROL = 0x0E,
  CT_ROLL_ABSOLUTE_CONTROL = 0x0F,
  CT_ROLL_RELATIVE_CONTROL = 0x10,
  CT_PRIVACY_CONTROL = 0x11,
  CT_FOCUS_SIMPLE_CONTROL = 0x12,
  CT_WINDOW_CONTROL = 0x13,
  CT_REGION_OF_INTEREST_CONTROL = 0x14,
  // A.9.5. Processing Unit Control Selectors
  PU_CONTROL_UNDEFINED = 0x00,
  PU_BACKLIGHT_COMPENSATION_CONTROL = 0x01,
  PU_BRIGHTNESS_CONTROL = 0x02,
  PU_CONTRAST_CONTROL = 0x03,
  PU_GAIN_CONTROL = 0x04,
  PU_POWER_LINE_FREQUENCY_CONTROL = 0x05,
  PU_HUE_CONTROL = 0x06,
  PU_SATURATION_CONTROL = 0x07,
  PU_SHARPNESS_CONTROL = 0x08,
  PU_GAMMA_CONTROL = 0x09,
  PU_WHITE_BALANCE_TEMPERATURE_CONTROL = 0x0A,
  PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL = 0x0B,
  PU_WHITE_BALANCE_COMPONENT_CONTROL = 0x0C,
  PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL = 0x0D,
  PU_DIGITAL_MULTIPLIER_CONTROL = 0x0E,
  PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL = 0x0F,
  PU_HUE_AUTO_CONTROL = 0x10,
  PU_ANALOG_VIDEO_STANDARD_CONTROL = 0x11,
  PU_ANALOG_LOCK_STATUS_CONTROL = 0x12,
  PU_CONTRAST_AUTO_CONTROL = 0x13,
  // A.9.6. Encoding Unit Control Selectors
  EU_CONTROL_UNDEFINED = 0x00,
  EU_SELECT_LAYER_CONTROL = 0x01,
  EU_PROFILE_TOOLSET_CONTROL = 0x02,
  EU_VIDEO_RESOLUTION_CONTROL = 0x03,
  EU_MIN_FRAME_INTERVAL_CONTROL = 0x04,
  EU_SLICE_MODE_CONTROL = 0x05,
  EU_RATE_CONTROL_MODE_CONTROL = 0x06,
  EU_AVERAGE_BITRATE_CONTROL = 0x07,
  EU_CPB_SIZE_CONTROL = 0x08,
  EU_PEAK_BIT_RATE_CONTROL = 0x09,
  EU_QUANTIZATION_PARAMS_CONTROL = 0x0A,
  EU_SYNC_REF_FRAME_CONTROL = 0x0B,
  EU_LTR_BUFFER_CONTROL = 0x0C,
  EU_LTR_PICTURE_CONTROL = 0x0D,
  EU_LTR_VALIDATION_CONTROL = 0x0E,
  EU_LEVEL_IDC_LIMIT_CONTROL = 0x0F,
  EU_SEI_PAYLOADTYPE_CONTROL = 0x10,
  EU_QP_RANGE_CONTROL = 0x11,
  EU_PRIORITY_CONTROL = 0x12,
  EU_START_OR_STOP_LAYER_CONTROL = 0x13,
  EU_ERROR_RESILIENCY_CONTROL = 0x14,
  // A.9.7. Extension Unit Control Selectors
  XU_CONTROL_UNDEFINED = 0x00,
  // A.9.8. VideoStreaming Interface Control Selectors
  VS_CONTROL_UNDEFINED = 0x00,
  VS_PROBE_CONTROL = 0x01,
  VS_COMMIT_CONTROL = 0x02,
  VS_STILL_PROBE_CONTROL = 0x03,
  VS_STILL_COMMIT_CONTROL = 0x04,
  VS_STILL_IMAGE_TRIGGER_CONTROL = 0x05,
  VS_STREAM_ERROR_CODE_CONTROL = 0x06,
  VS_GENERATE_KEY_FRAME_CONTROL = 0x07,
  VS_UPDATE_FRAME_SEGMENT_CONTROL = 0x08,
  VS_SYNCH_DELAY_CONTROL = 0x09,
  // Appendix B. Terminal Types
  // B.1. USB Terminal Types
  TT_VENDOR_SPECIFIC = 0x0100,
  TT_STREAMING = 0x0101,
  // B.2. Input Terminal Types
  ITT_VENDOR_SPECIFIC = 0x0200,
  ITT_CAMERA = 0x0201,
  ITT_MEDIA_TRANSPORT_INPUT = 0x0202,
  // B.3. Output Terminal Types
  OTT_VENDOR_SPECIFIC = 0x0300,
  OTT_DISPLAY = 0x0301,
  OTT_MEDIA_TRANSPORT_OUTPUT = 0x0302,
  // B.4. External Terminal Types
  EXTERNAL_VENDOR_SPECIFIC = 0x0400,
  COMPOSITE_CONNECTOR = 0x0401,
  SVIDEO_CONNECTOR = 0x0402,
  COMPONENT_CONNECTOR = 0x0403,
};
