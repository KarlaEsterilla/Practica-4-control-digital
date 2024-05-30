#include <Arduino.h>
#include <leds_off.h>


void leds_off(int (num_leds)){
    for (int i = 0; i < num_leds; i++) {
      digitalWrite(num_leds[i],0);
    }
}