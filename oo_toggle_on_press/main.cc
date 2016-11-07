#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdlib.h> // no cstdlib?


// Source:
// http://www.avrfreaks.net/forum/avr-c-micro-how?name=PNphpBB2&file=viewtopic&t=59453

void * operator new(size_t size) { return malloc(size); }

void operator delete(void * ptr) { free(ptr); }

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};

extern "C" void __cxa_pure_virtual(void);

void __cxa_pure_virtual(void) {};




namespace helper {
  template <class T> const T &Swap(const T &a, const T &b) {
    a ^= b;
    b ^= a;
    a ^= b;
  }

  template <class T> const T &Confine(const T &x, const T &lower_bound, const T &upper_bound) {
    if (upper_bound < lower_bound) Swap(lower_bound, upper_bound);
    if (x < lower_bound) return lower_bound;
    if (upper_bound < x) return upper_bound;
    return x;
  }

  template <class T> const T &Scale(const T &x, const T &x_min, const T &x_max, const T &new_min, const T &new_max) {
    return new_min + (new_max - new_min) * x / (x_max - x_min);
  }
}




struct Color {
  Color(unsigned int red, unsigned int greed, unsigned int blue);
  unsigned int red;
  unsigned int green;
  unsigned int blue;
}

Color::Color(unsigned int red, unsigned int green, unsigned int blue)  : red(red), green(green), blue(blue) {}



class Led {
 public:
  static Led &instance();
  void Setup() const;
  void On() const;
  void Off() const;
  void Toggle() const;
  void SetColor(Color color) const;
  void Pulse(Color color1, Color color2);
 private:
  Led();
  const bool common_anode = false;
  int cycle_ = 0;
  const int cycle_size_ = 255;
};

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

void Led::On() const {
  PORTD |= (1<<PORTD5);
  PORTD |= (1<<PORTD6);
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

void Led::SetColor(Color color) const {
  if (common_anode) {
    color.red   = UINT_MAX - color.red;
    color.green = UINT_MAX - color.green;
    color.blue  = UINT_MAX - color.blue;
  }
}

void Led::Pulse(Color color1, Color color2) {
  cycle_ = (++cycle_) % cycle_size_;
  // scale
  // set color
}





class Button {
 public:
  static Button &instance();
  void Setup() const;
 private:
   Button();
};

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

ISR(INT0_vect) {
  Led::instance().Toggle();
}




void Setup() { // replace this with a class later
  Led::instance().Setup();
  Button::instance().Setup();
  sei(); // Enable interrupts
}

int main() {
  Setup();
  for (;;);
}
