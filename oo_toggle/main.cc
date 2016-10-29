#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include <avr/io.h>
#include <avr/interrupt.h>


class Pin {
 public:
  virtual ~Pin();
  virtual void Setup() = 0;
};

class AnalogInput : public Pin { // is a pin
 private:
 public:
  virtual ~AnalogInput();
  AnalogInput();
//  int Read(bool level);
};

class DigitalInput { // is a pin
 public:
  virtual ~DigitalInput();
//  bool Read(bool level);
};

class DigitalOutput { // is a pin
 private:
 public:
  virtual ~DigitalOutput();
//  void Set(bool level);
};


class Button { // is a digital input
 private:
 public:
  Button();
  void Setup();
};

Button::Button() {
  DDRD &= ~(1 << DDD2); // Button | Clear 2nd bit on PORTD (i.e. PD2) => input
  PORTD |= (1 << PORTD2); // turn on button internal pullup


  EICRA |= (1 << ISC01); // Set INT0 to trigger on any logic change
  EIMSK |= (1 << INT0); // Turn on INT0
}

class RedLed { // is a digital output
 private:
 public:
  RedLed();
};

class GreenLed { // is a digital output
 private:
 public:
  GreenLed();
};

class BlueLed { // is a digital output
 private:
 public:
  BlueLed();
};


class Led { // has a red pin, has a green pin, has a blue pin
 private:
  enum Color { kOff, kRed, kYellow, kGreen, kCyan, kBlue, kMagenta, kWhite };
  Color color_;

 public:
  Led();
  void SetColor(Color color);
  void NextColor(Color color);
};

Led::Led() {
  DDRD |= (1<<DDB5); // RED   | Set 5th bit on PORTD (i.e. PD5) => output
  DDRD |= (1<<DDB6); // GREEN | Set 6th bit on PORTD (i.e. PD6) => output
  DDRB |= (1<<DDB1); // BLUE  | Set 1st bit on PORTB (i.e. PB1) => output

//  SetColor(kOff);
}


ISR(INT0_vect) {
  PORTD ^= (1<<PORTD5);
  PORTD ^= (1<<PORTD6);
  PORTB ^= (1<<PORTB1);
}


int main() {


  sei(); // Enable interrupts

  for (;;);
}









class UltrasonicSensor { // is a sensor
 private:
 public:
};

class TemperatureSensor { // is a sensor
 private:
  int cache_;
 public:
};
