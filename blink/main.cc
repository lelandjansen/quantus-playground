#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>

int main() {
  DDRD |= (1<<DDB5); // RED   | Set 5th bit on PORTD (i.e. PD5) to 1 => output
  DDRD |= (1<<DDB6); // GREEN | Set 6th bit on PORTD (i.e. PD6) to 1 => output
  DDRB |= (1<<DDB1); // BLUE  | Set 1st bit on PORTB (i.e. PB1) to 1 => output

  for (;;) {
    PORTD ^= (1<<PORTD5);
    PORTD ^= (1<<PORTD6);
    PORTB ^= (1<<PORTB1);
    _delay_ms(1000);
  }
}
