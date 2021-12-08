#include "log.h"
#include "uart.h"
#include "usb.h"

#include <avr/io.h>
#include <util/delay.h>

int main() {

  uart_init();

  log_line("\n\n");

  usb_init();

  log_line("System initialized");

  while (1) {
    _delay_ms(500);
  }

  return 0;
}
