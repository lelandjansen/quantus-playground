#ifndef F_CPU
#define F_CPU 16000000UL // 8 MHz
#endif

#include <avr/io.h>
#include <avr/interrupt.h>


ISR(INT0_vect) {
  PORTD ^= (1<<PORTD5);
  PORTD ^= (1<<PORTD6);
  PORTB ^= (1<<PORTB1);
}


int main() {
  DDRD |= (1<<DDB5); // RED   | Set 5th bit on PORTD (i.e. PD5) => output
  DDRD |= (1<<DDB6); // GREEN | Set 6th bit on PORTD (i.e. PD6) => output
  DDRB |= (1<<DDB1); // BLUE  | Set 1st bit on PORTB (i.e. PB1) => output

  DDRD &= ~(1 << DDD2); // Button | Clear 2nd bit on PORTD (i.e. PD2) => input
  PORTD |= (1 << PORTD2); // turn on button internal pullup


  EICRA |= (1 << ISC01); // Set INT0 to trigger on any logic change
  EIMSK |= (1 << INT0); // Turn on INT0

  sei(); // Enable interrupts

  for (;;);
}
