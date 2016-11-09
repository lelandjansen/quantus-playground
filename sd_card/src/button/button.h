#ifndef MAKEFILE_SRC_BUTTON_H_
#define MAKEFILE_SRC_BUTTON_H_

class Button {
 public:
  static Button &instance();
  void Setup() const;
 private:
   Button();
};

#endif
