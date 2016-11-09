#ifndef MAKEFILE_SRC_LED_H_
#define MAKEFILE_SRC_LED_H_

class Led {
 public:
  static Led &instance();
  void Setup() const;
  void On() const;
  void Off() const;
  void Toggle() const;
 private:
  Led();
};


#endif
