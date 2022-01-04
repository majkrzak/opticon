#pragma once

#include <stdint.h>

#include <stddef.h>

/// Initialize the Analog to Digital Converter
void adc_init();

/// Read value out of the Analog to Digital Converter
/**
 *  Reads value out of the `idx`'th analog pin into the `res`.
 *  Arduino Leonardo pin numbering is used for `idx`
 */
void adc_read(size_t idx, uint16_t *res);
