#ifndef MAKEFILE_SRC_LED_H_
#define MAKEFILE_SRC_LED_H_

class Led {
 public:
  static Led &instance();
  void Setup() const;
  void White() const;
  void Red() const;
  void Yellow() const;
  void Green() const;
  void Cyan() const;
  void Blue() const;
  void Magenta() const;
  void Off() const;
  void Toggle() const;
 private:
  Led();
};


#endif
