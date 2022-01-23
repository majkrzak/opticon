#include "adc.h"
#include "config.h"
#include "frame.h"
#include "log.h"
#include "mux.h"
#include "scanner.h"
#include "timer.h"
#include "uart.h"
#include "usb.h"

#include <util/delay.h>

int main() {

  uart_init();
  usb_init();
  adc_init();
  mux_init();
  timer_init();
  scanner_init();

  while (1) {
    _delay_ms(100);
  }
}
