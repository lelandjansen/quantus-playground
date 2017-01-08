#include "led.h"

#include <avr/io.h>

Led::Led() {}

Led &Led::instance() {
  static Led *instance = new Led();
  return *instance;
}

void Led::Setup() const {
  DDRB |= (1<<DDB5); // BLUE  | Set 1st bit on PORTB (i.e. PB1) => output
}

void Led::On() const {
  PORTB |= (1<<PORTB5);
}

void Led::Off() const {
  PORTB &= ~(1<<PORTB5);
}

void Led::Toggle() const {
  PORTB ^= (1<<PORTB5);
}
