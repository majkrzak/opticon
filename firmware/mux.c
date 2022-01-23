#include "mux.h"

#include <avr/cpufunc.h>
#include <avr/io.h>

void mux_init() { DDRB = 1 << PB4 | 1 << PB5 | 1 << PB6 | 1 << PB7; }

void mux_select(size_t idx) {
  PORTB &= ~(1 << PB7);
  _NOP();
  for (size_t i = 0; i < 3; ++i) {
    if (idx & 1 << i) {
      PORTB |= 1 << (i + PB4);
    } else {
      PORTB &= ~(1 << (i + PB4));
    }
  }
  _NOP();
  PORTB |= 1 << PB7;
}
