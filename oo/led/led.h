#include "color.h"

#ifndef OO_LED_H_
#define OO_LED_H_

class Led {
 public:
   static Led& instance();
   void Setup();
   void NextCycle();
   void SetColor(Color color);
   void Pulse(Color color1, Color color2);
 private:
   Led();
   int cycle_;
   int cycle_size_ = 255;
};

#endif
