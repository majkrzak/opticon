#include "scanner.h"

#include "adc.h"
#include "frame.h"
#include "timer.h"

#include <stdlib.h>

// TODO refactor, build proper state machine.

static enum {
  PENDING,
  SELECTING_COLUMN,
  SCANNING,
} _state = PENDING;

static size_t ctr = 0;
static size_t row = 0;
static size_t col = 0;

static void _tick() {
  switch (_state) {
  case PENDING:
    if (!ctr) {
      _state = SELECTING_COLUMN;
    }
    break;
  case SELECTING_COLUMN:
    // select_col;
    _state = SCANNING;
    break;
  case SCANNING:
    adc_read(row, frame + row * WIDTH + col);
    row += 1;
    row %= HEIGHT;
    if (!row) {
      col += 1;
      col %= WIDTH;
      if (!col) {
        _state = PENDING;
        frame_ready = true;
      } else {
        _state = SELECTING_COLUMN;
      }
    }
    break;
  }
  ctr += 1;
  ctr %= 100;
}

void scanner_init() { timer_handler = _tick; }
