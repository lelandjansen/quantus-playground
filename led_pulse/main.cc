#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int DUTY_CYCLE = 64;

int main() {
  DDRD |= (1<<DDB6);

  TCCR0A |= (1<<COM0A1);

  // Clear OC0A on Compare Match, set OC0A at BOTTOM (none-inverting mode).
  // interesting thought, could use inverting or none-inverting depending on LED
  //  polarity??

  TCCR0A |= (1<<WGM00) | (1<<WGM01);
  // Waveform generation mode
  // Timer/counter mode of operation: Fast PWM
  // TOP: 0xFF
  // Update of OCRx at: BOTTOM
  // TOV Flag set on: MAX

  TIMSK0 |= (1<<TOIE0); // set overflow interrupt



  OCR0A = DUTY_CYCLE;

  TCCR0B |= (1<<CS00); // no prescaling

  sei();


  for(;;) {
    DUTY_CYCLE = (++DUTY_CYCLE)%255;
    _delay_ms(10);
  }

}


ISR(TIMER0_OVF_vect) {
  OCR0A = DUTY_CYCLE;
}


// Waveform generation mode (WGM) p. 130
// We want mode 14
//   Fast PWM
//   Top: ICR1
//   Update of OCR1x at: BOTTOM
//   TOV1 Flag Set on: TOP

// Create period (using ICR)
// 2^16-1 = 65535

// Prescaler (CS10-12)
// 5 for 8 MHz, 10 for 16 MHz





// ICR1 and prescaler values
// Resting adult breath rate is between 12 and 20 breaths per minute
// = 1 breath every 3 to 5 seconds
// Say, 1 breath every 4 seconds
// 16000000 cycles/second * 4 seconds = 64000000 cycle_size_
// Timer 1 resolution

// N[Solve[(4*8000000)/(2^16*x) == 100, x]]
//   {{x -> 4.88281}}
//   prescaler = 5

// N[Solve[(4*16000000)/(2^16*x) == 100, x]]
//   {{x -> 9.76563}}
//   prescaler = 10




// ICR1 = 2^16-1
// Prescaler = 5 (10 for 16 MHz)
//


// page 110 for CS10-12
