#pragma once

#include <stdint.h>

#define USB_STRUCT                                                             \
  __attribute__((packed, scalar_storage_order("little-endian")))

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
  uint16_t bString[];
} string_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bInterfaceNumber;
  uint8_t bAlternateSetting;
  uint8_t bNumEndpoints;
  uint8_t bInterfaceSubClass;
  uint8_t bInterfaceProtocol;
  uint8_t iInterface;
} interface_descriptor_t;

typedef struct USB_STRUCT {
  uint8_t bLength;
  uint8_t bDescriptorType;
  struct {
    uint8_t number : 4;
    uint8_t _ : 3;
    enum {
      OUT = 0,
      IN = 1,
    } direction : 1;
  } bEndpointAddress;
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

enum {
  CC_VIDEO = 0x0E,
  SC_VIDEOSTREAMING = 0x02,
  PC_PROTOCOL_15 = 0x01,
};
