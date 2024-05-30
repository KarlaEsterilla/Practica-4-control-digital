#include <Arduino.h>
#include <math.h>
#include <Delay_not_block.h>
#include <interrupcion.h>
#include <leds_off.h>

const int16_t ledRojo = 12;
const int16_t ledVerde = 11;
const int16_t ledNaranja = 10;
const int16_t ledAzul = 9;
bool  state_led=0;
bool  flag_seq = 0;
int16_t sw1 = 7;
int16_t sw2 = 6;
int16_t sw3 = 5;
int16_t sw4 = 4;
int32_t timer[2] = {12500,46875};

 struct arreglo_leds
 {
   int leds[4];
   int numero_leds;
 }
arreglo_leds = {{ledRojo,ledVerde,ledNaranja,ledAzul},4};

typedef enum {
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_FALLING,
  BUTTON_RISING
} ButtonState_t;

typedef struct {
  ButtonState_t state;
  int16_t pin;
} Button_t;

Button_t button1;
Button_t button2;
Button_t button3;
Button_t button4;

void ButtonInit(Button_t* button, int16_t pin);
void ButtonUpdate(Button_t* button);
void ButtonPressed(int16_t pin);
void ButtonReleased(int16_t pin);
void ButtonError(Button_t* button);


void setup() {
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(sw4, INPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledNaranja, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  
  ButtonInit(&button1, sw1);
  ButtonInit(&button2, sw2);
  ButtonInit(&button3, sw3);
  ButtonInit(&button4, sw4);

  leds_off(arreglo_leds.numero_leds);
  
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= B00000100;
  TIMSK1 |= B00000010;
  OCR1A = 12500;
  interrupts();
}

ISR(TIMER1_COMPA_vect){
  leds_off(arreglo_leds.numero_leds);
  TCNT1 = 0;
  state_led = !state_led;
  interrupcion(flag_seq,state_led);   
}

void loop() {
  ButtonUpdate(&button1);
  ButtonUpdate(&button2);
  ButtonUpdate(&button3);
  ButtonUpdate(&button4); 
}

void ButtonInit(Button_t* button, int16_t pin) {
  button->state = BUTTON_DOWN;
  button->pin = pin;
}

void ButtonUpdate(Button_t* button) {
  switch (button->state) {
    case BUTTON_UP:
      if (digitalRead(button->pin) == 0) {
        button->state = BUTTON_FALLING;
      }
      break;
    case BUTTON_DOWN:
      if (digitalRead(button->pin)) {
        button->state = BUTTON_RISING;
      }
      break;
    case BUTTON_FALLING:
      if (Delay_not_block(40)) {
        if (digitalRead(button->pin) == 0) {
          button->state = BUTTON_DOWN;
          ButtonPressed(button->pin);
        } else {
          button->state = BUTTON_UP;
        }
      }
      break;
    case BUTTON_RISING:
      if (Delay_not_block(40)) {
        if (digitalRead(button->pin)) {
          button->state = BUTTON_UP;
          ButtonReleased(button->pin);
        } else {
          button->state = BUTTON_DOWN;
        }
      }
      break;
    default:
      ButtonError(button);
      break;
  }
}

void ButtonError(Button_t* button) {
  button->state = BUTTON_DOWN;
}

void ButtonPressed(int16_t pin) {
  if (pin == sw1) {	
    flag_seq = 0;
  } else if (pin == sw2) {
	flag_seq = 1;
  } else if (pin == sw3) {  
    OCR1A = timer[0];
  } else if (pin == sw4) { 
    OCR1A = timer[1]; 
  } else {
    ;
  }
}

void ButtonReleased(int16_t pin) {
}

