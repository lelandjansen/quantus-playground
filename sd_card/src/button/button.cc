#include "button.h"
#include "../led/led.h"

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect) {
  Led::instance().Toggle();
}

Button::Button() {}

Button &Button::instance() {
  static Button *instance = new Button();
  return *instance;
}

void Button::Setup() const {
  DDRD &= ~(1 << DDD2); // Button | Clear 2nd bit on PORTD (i.e. PD2) => input
  PORTD |= (1 << PORTD2); // turn on button internal pullup

  EICRA |= (1 << ISC01); // Set INT0 to trigger on any logic change
  EIMSK |= (1 << INT0); // Turn on INT0
}
