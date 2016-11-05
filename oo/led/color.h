#ifndef OO_COLOR_H_
#define OO_COLOR_H_

class Color {
 public:
  Color();
  Color(int r, int g, int b);
  void SetColor(int r, int g, int b);
 private:
  int red = 0, green = 0, blue = 0;
};

#endif
