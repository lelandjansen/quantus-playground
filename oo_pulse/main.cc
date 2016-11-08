#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdlib.h> // no cstdlib?
#include <limits.h> // no climits?

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
  Color();
  Color(unsigned char red, unsigned char greed, unsigned char blue);
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

Color::Color() : red(0), green(0), blue(0) {}
Color::Color(unsigned int red, unsigned int green, unsigned int blue) : red(red), green(green), blue(blue) {}



class Led {
 public:
  static Led &instance();
  void Setup() const;
  void SetColor(Color &color) const;
  void Pulse(Color &color1, Color &color2);
 private:
  Led();
  const bool common_anode = false; // could also change pwm mode to inverted?
  int cycle_ = 0;
  const int cycle_size_ = 255;
};

Led::Led() {}

Led &Led::instance() {
  static Led *instance = new Led();
  return *instance;
}

void Led::Setup() const {
  DDRD |= (1<<DDB5); // red
  DDRD |= (1<<DDB6); // green
  DDRB |= (1<<DDB1); // blue

  // command ouput mode
  TCCR0A |= (1<<COM0B1); // red
  TCCR0A |= (1<<COM0A1); // green
  TCCR1A |= (1<<COM1A1); // blue

  // set PWM mode
  TCCR0A |= (1<<WGM00) | (1<<WGM01);
  TCCR1A |= (1<<WGM10);
  TCCR1B |= (1<<WGM12);

  // set overflow interrupt
  TIMSK0 |= (1<<TOIE0);
  TIMSK1 |= (1<<TOIE1);

  // no prescaling
  TCCR0B |= (1<<CS00);
  TCCR1B |= (1<<CS10);
}

void Led::SetColor(Color &color) const {
  OCR0B = color.red;
  OCR0A = color.green;
  OCR1A = color.blue;
}

void Led::Pulse(Color &color1, Color &color2) {
  // cycle function
  cycle_ = (++cycle_) % cycle_size_;


  // scale between color1 and color2
  Color color;
  color.red   = helper::scale(color1.red,   color2.red);
  color.green = helper::scale(color1.green, color2.green);
  color.blue  = helper::scale(color1.blue,  color2.blue);

  SetColor(color);
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
  // do something on press
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
