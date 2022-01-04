#include "adc.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stddef.h>
#include <stdlib.h>

static uint8_t _map_idx(size_t idx) {
  switch (idx) {
  case 0:
    return 7;
  case 1:
    return 6;
  case 2:
    return 5;
  case 3:
    return 4;
  case 4:
    return 1;
  case 5:
    return 0;
  default:
    abort();
  }
}

static void _select_mux(size_t idx) { ADMUX = _map_idx(idx); }

static void _start() { ADCSRA |= ADEN; }

static uint16_t *_res;

ISR(ADC_vect) { *_res = ADC; }

void adc_init() {
  ADCSRA = (1 << ADEN) | (1 << ADIE);
  ADCSRB = 0;
}

void adc_read(size_t idx, uint16_t *res) {
  _res = res;
  _select_mux(idx);
  _start();
}
