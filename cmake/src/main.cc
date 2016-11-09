#include <avr/interrupt.h>
#include <stdlib.h>

#include "main.h"
#include "led/led.h"
#include "button/button.h"


void * operator new(size_t size) { return malloc(size); }
void operator delete(void * ptr) { free(ptr); }
int __cxa_guard_acquire(__guard *g) { return !*(char *)(g); };
void __cxa_guard_release (__guard *g) { *(char *)g = 1; };
void __cxa_guard_abort (__guard *) {};
void __cxa_pure_virtual(void) {};


void Setup() { // replace this with a class later
  Led::instance().Setup();
  Button::instance().Setup();
  sei(); // Enable interrupts
}

int main() {
  Setup();
  Led::instance().On();
  for (;;);
}
