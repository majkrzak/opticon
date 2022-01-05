#include "log.h"
#include "uart.h"
#include "usb.h"

#include "adc.h"
#include "config.h"
#include "frame.h"

#include <avr/interrupt.h>

#include <avr/io.h>
#include <util/delay.h>

int main() {

  uart_init();

  usb_init();

  adc_init();

  _delay_ms(500);

  while (1) {
    for (size_t j = 0; j < WIDTH; ++j) {
      for (size_t i = 0; i < HEIGHT; ++i) {
        adc_read(i, frame + i * WIDTH + j);
        _delay_ms(1);
      }
    }
    frame_ready = true;
    _delay_ms(100 - WIDTH * HEIGHT);
  }

  return 0;
}
