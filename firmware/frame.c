#include "frame.h"
#include <stdbool.h>
#include <stdint.h>

#include "config.h"

uint16_t frame[WIDTH * HEIGHT] = {};
bool frame_ready = false;
