#include "timer.h"

#include <avr/interrupt.h>
#include <avr/io.h>

void timer_init() {
  // configure 1ms tick for 16MHz clock
  TCCR0A = (1 << WGM01);              // CTC mode
  TCCR0B = (1 << CS01) | (1 << CS00); // 1/64 prescaler
  OCR0A = 250;
  TIMSK0 = (1 << OCIE0A);
}

void (*timer_handler)() = 0;

ISR(TIMER0_COMPA_vect) {
  if (timer_handler) {
    timer_handler();
  }
}
