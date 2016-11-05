#include "helper.h"

namespace helper {
  template <class T> const T &Confine(const T &x, const T &lower_bound, const T &upper_bound) {
    if (x < lower_bound) return lower_bound;
    if (upper_bound < x) return upper_bound;
    return x;
  }

  template <class T> const T &Scale(const T &x, const T &min, const T &max) {
    
  }
}
