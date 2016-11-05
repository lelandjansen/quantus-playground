#include "led.h"
#include <cmath>

Led::Led() {}

Led &Led::instance() {
  static Led *instance = new Led();
  return *instance;
}

void Led::NextCycle() {
  cycle_ = (++cycle_)%cycle_size_;
  return 255 * (exp(sin(cycle_) + 1) - 1) / (exp(2) - 1);
}

void Led::Pulse(Color color1, Color color2) {
  NextCycle();
}
