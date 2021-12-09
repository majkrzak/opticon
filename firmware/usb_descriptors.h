#pragma once

#include "usb_types.h"

extern device_descriptor_t device_descriptor;

typedef struct USB_STRUCT {
  video_control_interface_descriptor_header_t
      video_control_interface_descriptor_header;
  camera_terminal_descriptor_t camera_terminal_descriptor;
  streaming_terminal_descriptor_t streaming_terminal_descriptor;
} video_control_interface_descriptor_bundle_t;

typedef struct USB_STRUCT {
  video_streaming_interface_descriptor_header_t
      video_streaming_interface_descriptor_header;
  uncompressed_video_format_descriptor_t uncompressed_video_format_descriptor;
  uncompressed_video_frame_descriptor_t uncompressed_video_frame_descriptor;
  endpoint_descriptor_t video_streaming_endpoint_descriptor;
} video_streaming_interface_descriptor_bundle_t;

typedef struct USB_STRUCT {
  configuration_descriptor_t configuration_descriptor;
  interface_association_descriptor_t interface_association_descriptor;
  interface_descriptor_t video_control_interface_descriptor;
  video_control_interface_descriptor_bundle_t
      video_control_interface_descriptor_bundle;
  interface_descriptor_t video_streaming_interface_descriptor;
  video_streaming_interface_descriptor_bundle_t
      video_streaming_interface_descriptor_bundle;
} configuration_descriptor_bundle_t;

extern configuration_descriptor_bundle_t configuration_descriptor_bundle;

extern string_descriptor_t string_descriptor_zero;

extern string_descriptor_t string_descriptor_one;
