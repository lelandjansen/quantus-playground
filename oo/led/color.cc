#include "color.h"
#include "helper.h"

Color::Color() {}

Color::Color(int r, int g, int b) {
  SetColor(r, g, b);
}

void Color::SetColor(int r, int g, int b) {
  red   = helper::Confine(r, 0, 255);
  green = helper::Confine(g, 0, 255);
  blue  = helper::Confine(b, 0, 255);
}
