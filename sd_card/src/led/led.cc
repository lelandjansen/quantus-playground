#include "led.h"

#include <avr/io.h>
#include <avr/interrupt.h>

Led::Led() {}

Led &Led::instance() {
  static Led *instance = new Led();
  return *instance;
}

void Led::Setup() const {
  DDRD |= (1<<DDB5); // RED   | Set 5th bit on PORTD (i.e. PD5) => output
  DDRD |= (1<<DDB6); // GREEN | Set 6th bit on PORTD (i.e. PD6) => output
  DDRB |= (1<<DDB1); // BLUE  | Set 1st bit on PORTB (i.e. PB1) => output
}

void Led::White() const {
  PORTD |= (1<<PORTD5);
  PORTD |= (1<<PORTD6);
  PORTB |= (1<<PORTB1);
}

void Led::Red() const {
  PORTD |= (1<<PORTD5);
  PORTD &= ~(1<<PORTD6);
  PORTB &= ~(1<<PORTB1);
}

void Led::Yellow() const {
  PORTD |= (1<<PORTD5);
  PORTD |= (1<<PORTD6);
  PORTB &= ~(1<<PORTB1);
}

void Led::Green() const {
  PORTD &= ~(1<<PORTD5);
  PORTD |= (1<<PORTD6);
  PORTB &= ~(1<<PORTB1);
}

void Led::Cyan() const {
  PORTD &= ~(1<<PORTD5);
  PORTD |= (1<<PORTD6);
  PORTB |= (1<<PORTB1);
}

void Led::Blue() const {
  PORTD &= ~(1<<PORTD5);
  PORTD &= ~(1<<PORTD6);
  PORTB |= (1<<PORTB1);
}

void Led::Magenta() const {
  PORTD |= (1<<PORTD5);
  PORTD &= ~(1<<PORTD6);
  PORTB |= (1<<PORTB1);
}

void Led::Off() const {
  PORTD &= ~(1<<PORTD5);
  PORTD &= ~(1<<PORTD6);
  PORTB &= ~(1<<PORTB1);
}

void Led::Toggle() const {
  PORTD ^= (1<<PORTD5);
  PORTD ^= (1<<PORTD6);
  PORTB ^= (1<<PORTB1);
}
