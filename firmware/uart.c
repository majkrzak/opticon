#include "uart.h"

#include <avr/io.h>

void uart_init() {
  UBRR1 = 103; // 9600 @ 16M
  // UBRR1 = 0; // 1M @ 16M
  UCSR1B = 1 << TXEN1;
  UCSR1C = (1 << USBS1) | (3 << UCSZ10);
}

void uart_putc(unsigned char data) {
  while (!(UCSR1A & (1 << UDRE1)))
    ;
  UDR1 = data;
}
