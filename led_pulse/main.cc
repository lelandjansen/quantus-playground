#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>

// include interrupt
// include time?

#include <avr/interrupt.h>

int main () {
  DDRB |= (1 << 0); // Set LED as output
  TIMSK |= (1 << TOIE1); // Enable overflow interrupt
  sei(); // Enable global interrupts
  TCCR1B |= (1 << CS11); // Start timer at Fcpu/8

  for (;;);
}

ISR(TIMER1_OVF_vect) {
  PORTB ^= (1 << 0); // Toggle the LED
}