#include "log.h"

#include "uart.h"

void log_line(const char *str) {
  while (*str) {
    uart_putc(*str);
    ++str;
  }
  uart_putc('\r');
  uart_putc('\n');
}
