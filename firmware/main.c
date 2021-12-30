#include "log.h"
#include "uart.h"
#include "usb.h"

#include <avr/io.h>
#include <util/delay.h>

int main() {

  uart_init();

  usb_init();

  _delay_ms(500);

  while (1) {
    _delay_ms(100);
  }

  return 0;
}
