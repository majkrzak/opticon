#include "usb.h"
#include "usb_config.h"
#include "usb_descriptors.h"
#include "usb_types.h"

#include "config.h"
#include "frame.h"
#include "log.h"
#include "uart.h"

#include <assert.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>
#include <util/delay.h>

static void _init_pll() {
  PLLCSR = (F_CPU == 16000000UL ? (1 << PINDIV) : 0) | (1 << PLLE);
  loop_until_bit_is_clear(PLLCSR, PLOCK);
}

static void _init_control_endpoint() {
  UENUM = CONTROL_ENDPOINT;
  UECONX = (1 << EPEN);
  UECFG0X = (0b00 << EPTYPE0) | (0 << EPDIR);
  UECFG1X = (0b010 << EPSIZE0) | (0b00 << EPBK0) | (1 << ALLOC);
  assert(bit_is_set(UESTA0X, CFGOK));
  UERST = 1 << CONTROL_ENDPOINT;
  UERST = 0;
  UEIENX = (1 << RXSTPE);
}

static void _init_video_streaming_endpoint() {
  UENUM = VIDEO_STREAMING_ENDPOINT;
  UECONX = (1 << EPEN);
  UECFG0X = (0b10 << EPTYPE0) | (1 << EPDIR);
  UECFG1X = (0b010 << EPSIZE0) | (0b00 << EPBK0) | (1 << ALLOC);
  assert(bit_is_set(UESTA0X, CFGOK));
  UERST = 1 << VIDEO_STREAMING_ENDPOINT;
  UERST = 0;
  UEIENX = (1 << TXINE);
}

void usb_init() {
  cli();
  _init_pll();
  UHWCON |= (1 << UVREGE);
  USBCON |= (1 << USBE) | (1 << OTGPADE);
  USBCON &= ~(1 << FRZCLK);
  UDCON = 0;
  USBCON &= ~(1 << DETACH);
  UDIEN = (1 << EORSTE);
  sei();
}

ISR(USB_GEN_vect) {
  // log_line("ISR(USB_GEN_vect)");
  if (bit_is_set(UDINT, UPRSMI)) {
    // log_line("UPRSMI - Upstream Resume Interrupt");
  }
  if (bit_is_set(UDINT, EORSMI)) {
    // log_line("EORSMI - End Of Resume Interrupt");
  }
  if (bit_is_set(UDINT, WAKEUPI)) {
    // log_line("WAKEUPI - Wake-up CPU Interrupt");
  }
  if (bit_is_set(UDINT, EORSTI)) {
    // log_line("EORSTI - End Of Reset Interrupt");
    _init_control_endpoint();
    _init_video_streaming_endpoint();
  }
  if (bit_is_set(UDINT, SOFI)) {
    // log_line("SOFI - Start Of Frame Interrupt");
  }
  if (bit_is_set(UDINT, SUSPI)) {
    // log_line("SUSPI - Suspend Interrupt");
  }

  UDINT = 0;
}

static void _read(uint8_t *ptr, size_t len) {
  while (len--) {
    *(ptr++) = UEDATX;
  }
}

static void _select_endpoint(uint8_t ep) { UENUM = ep; }

static void _request_stale() { UECONX = (1 << STALLRQ) | (1 << EPEN); }

static void _wait_TXINI() { loop_until_bit_is_set(UEINTX, TXINI); }

static void _clear_TXINI() { UEINTX &= ~(1 << TXINI); }

static void _wait_RXOUTI() { loop_until_bit_is_set(UEINTX, RXOUTI); }

static void _clear_RXOUTI() { UEINTX &= ~(1 << RXOUTI); }

static void _clear_RXSTPI() {
  UEINTX &= ~((1 << RXSTPI) | (1 << RXOUTI) | (1 << TXINI));
}

static void _clear_FIFOCON() { UEINTX &= ~(1 << FIFOCON); }

static bool _read_write_allowed() { return bit_is_set(UEINTX, RWAL); }

static void _data_transmit(const uint8_t *buff, size_t len, size_t max_len,
                           size_t chunk_len) {
  for (const uint8_t *it = buff; it < buff + len && it < buff + max_len; ++it) {
    _wait_TXINI();
    UEDATX = *it;
    if (!(((it - buff) + 1) % chunk_len))
      _clear_TXINI();
  }
}

static void _data_receive(uint8_t *buff, size_t len, size_t max_len,
                          size_t chunk_len) {
  for (uint8_t *it = buff; it < buff + len && it < buff + max_len; ++it) {
    _wait_RXOUTI();
    *it = UEDATX;
    if (!(((it - buff) + 1) % chunk_len) || it + 1 == buff + len ||
        it + 1 == buff + max_len)
      _clear_RXOUTI();
  }
}

static bool _control_is_ok;

static void _control_get_descriptor(uint16_t wValue, uint16_t wLength) {
  union {
    struct {
      uint8_t index;
      uint8_t type;
    } t;
    uint16_t b;
  } descriptor = {.b = wValue};
  switch (descriptor.t.type) {
  case DEVICE_DESCRIPTOR:
    _data_transmit((const uint8_t *)&device_descriptor,
                   sizeof device_descriptor, wLength, 32);
    break;
  case CONFIGURATION_DESCRIPTOR:
    _data_transmit((const uint8_t *)&configuration_descriptor_bundle,
                   sizeof configuration_descriptor_bundle, wLength, 32);
    break;
  case STRING_DESCRIPTOR:
    switch (descriptor.t.index) {
    case 0:
      _data_transmit((const uint8_t *)&string_descriptor_zero,
                     string_descriptor_zero.bLength, wLength, 32);
      break;
    case 1:
      _data_transmit((const uint8_t *)&string_descriptor_one,
                     string_descriptor_one.bLength, wLength, 32);
      break;
    default:
      _control_is_ok = false;
    }
    break;

  case DEVICE_QUALIFIER_DESCRIPTOR:
  case OTHER_SPEED_CONFIGURATION_DESCRIPTOR:
  default:
    _control_is_ok = false;
  }
}

static void _control_set_address(uint16_t wValue) {
  _wait_TXINI();
  UDADDR = wValue | (1 << ADDEN);
}

static void _control_set_configuration(uint16_t) {
  //_init_video_streaming_endpoint();
  //_select_endpoint(CONTROL_ENDPOINT);
}
static void _control_get_configuration(uint16_t wLength) {
  _data_transmit((uint8_t[]){1}, 1, wLength, 32);
}

static void _control_video_get_def(uint16_t wValue, uint16_t wLength) {
  switch (wValue >> 8) {
  case VS_PROBE_CONTROL:
    _data_transmit((const uint8_t *)&video_probe_controls,
                   sizeof video_probe_controls, wLength, 32);
    break;
  default:
    _control_is_ok = false;
  };
}

static void _control_video_get_cur(uint16_t wValue, uint16_t wLength) {
  switch (wValue >> 8) {
  case VS_PROBE_CONTROL:
    _data_transmit((const uint8_t *)&video_probe_controls,
                   sizeof video_probe_controls, wLength, 32);
    break;
  default:
    _control_is_ok = false;
  };
}

static void _control_video_get_min(uint16_t wValue, uint16_t wLength) {
  switch (wValue >> 8) {
  case VS_PROBE_CONTROL:
    _data_transmit((const uint8_t *)&video_probe_controls,
                   sizeof video_probe_controls, wLength, 32);
    break;
  default:
    _control_is_ok = false;
  };
}

static void _control_video_get_max(uint16_t wValue, uint16_t wLength) {
  switch (wValue >> 8) {
  case VS_PROBE_CONTROL:
    _data_transmit((const uint8_t *)&video_probe_controls,
                   sizeof video_probe_controls, wLength, 32);
    break;
  default:
    _control_is_ok = false;
  };
}

static void _control_video_set_cur(uint16_t, uint16_t wLength) {
  uint8_t buff[wLength];
  _data_receive(buff, sizeof buff, wLength, 32);
}

static void _control_setup() {
  _select_endpoint(CONTROL_ENDPOINT);

  setup_request request;
  _read(request.b, sizeof request);

  _clear_RXSTPI();
  _control_is_ok = true;

  switch (request.t.bmRequestType.direction) {
  case HOST_TO_DEVICE:
    _clear_TXINI();
    break;
  case DEVICE_TO_HOST:
    _wait_TXINI();
    break;
  }

  switch (request.t.bmRequestType.recipient) {
  case DEVICE:
    switch (request.t.bRequest) {
    case GET_STATUS:
      _data_transmit((uint8_t[]){0, 0}, 2, request.t.wLength, 32);
      break;
    case GET_DESCRIPTOR:
      _control_get_descriptor(request.t.wValue, request.t.wLength);
      break;
    case SET_ADDRESS:
      _control_set_address(request.t.wValue);
      break;
    case SET_CONFIGURATION:
      _control_set_configuration(request.t.wValue);
      break;
    case GET_CONFIGURATION:
      _control_get_configuration(request.t.wLength);
      break;
    default:
      _control_is_ok = false;
    }
    break;
  case INTERFACE:
    switch (request.t.wIndex) {
    case 0x01: // Video Streaming Interface
      switch ((int)request.t.bRequest) {
      case GET_STATUS:
        _data_transmit((uint8_t[]){0, 0}, 2, request.t.wLength, 32);
        break;
      case GET_DEF:
        _control_video_get_def(request.t.wValue, request.t.wLength);
        break;
      case GET_CUR:
        _control_video_get_cur(request.t.wValue, request.t.wLength);
        break;
      case GET_MIN:
        _control_video_get_min(request.t.wValue, request.t.wLength);
        break;
      case GET_MAX:
        _control_video_get_max(request.t.wValue, request.t.wLength);
        break;
      case SET_CUR:
        _control_video_set_cur(request.t.wValue, request.t.wLength);
        break;
      case SET_INTERFACE:
        UERST = 1 << VIDEO_STREAMING_ENDPOINT;
        UERST = 0;
        break;
      default:
        _control_is_ok = false;
      }
      break;
    default:
      _control_is_ok = false;
    }
    break;
  case ENDPOINT:
    //     switch (request.t.wIndex) {
    //     case (0x80 & VIDEO_STREAMING_ENDPOINT)<<8:
    switch ((int)request.t.bRequest) {
    case GET_STATUS:
      _data_transmit((uint8_t[]){0, 0}, 2, request.t.wLength, 32);
      break;
    case CLEAR_FEATURE:
      break;
    default:
      _control_is_ok = false;
    }
    break;
    //     default:
    //       _control_is_ok = false;
    //     }
    //     break;
  default:
    _control_is_ok = false;
  }

  if (_control_is_ok) {
    _clear_TXINI();
  } else {
    _request_stale();
  }
}

static bool _is_control_setup() {
  if (bit_is_set(UEINT, EPINT0)) {
    _select_endpoint(CONTROL_ENDPOINT);
    if (bit_is_set(UEINTX, RXSTPI)) {
      return true;
    }
  }
  return false;
}

static size_t _video_streaming_byte_idx = 0;
static size_t _video_streaming_frame_idx = 0;

static void _video_streaming() {
  _clear_TXINI();
  while (bit_is_set(UEINTX, RWAL) &&
         _video_streaming_byte_idx != (WIDTH * HEIGHT + 2)) {
    switch (_video_streaming_byte_idx) {
    case 0:
      UEDATX = 2;
      break;
    case 1:
      UEDATX = 0b10000000 | (_video_streaming_frame_idx % 2);
      break;
    default:
      UEDATX = frame[_video_streaming_byte_idx - 2] >> 2;
      break;
    }
    _video_streaming_byte_idx += 1;
  }
  if (_video_streaming_byte_idx == (WIDTH * HEIGHT + 2)) {
    _video_streaming_frame_idx += 1;
    _video_streaming_frame_idx %= WIDTH * HEIGHT;
    _video_streaming_byte_idx = 0;
  }
  _clear_FIFOCON();
}

static bool _is_video_streaming() {
  if (bit_is_set(UEINT, EPINT1)) {
    _select_endpoint(VIDEO_STREAMING_ENDPOINT);
    if (bit_is_set(UEINTX, TXINI)) {
      return true;
    }
  }
  return false;
}

ISR(USB_COM_vect) {
  if (_is_control_setup()) {
    _control_setup();
  } else if (_is_video_streaming()) {
    _video_streaming();
  }
}
