#include "sd.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <ff.h>

ISR(INT1_vect) {
  // If Sd card is inserted/removed
}

Sd::Sd() {}

Sd &Sd::instance() {
  static Sd *instance = new Sd();
  return *instance;
}

void Sd::Setup() const {
  // This is code for the button. Change this for the SD card card detect pin.
  // Also set up code for SPI interface.

//  DDRD &= ~(1 << DDD2); // Button | Clear 2nd bit on PORTD (i.e. PD2) => input
//  PORTD |= (1 << PORTD2); // turn on button internal pullup
//
//  EICRA |= (1 << ISC01); // Set INT0 to trigger on any logic change
//  EIMSK |= (1 << INT0); // Turn on INT0
}
