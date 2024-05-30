
#include "Delay_not_block.h"
#include <Arduino.h>

int16_t Delay_not_block(int16_t t_delay) {
  int16_t t_base = 1;
  static int16_t count = 0;
  int16_t n_time = t_delay / t_base;
  if (count >= n_time) {
    count = 0;
    return 1;
  } else {
    delay(1);
    count++;
    return 0;
  }
}