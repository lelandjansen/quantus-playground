#ifndef OO_HELPER_H_
#define OO_HELPER_H_

namespace helper {
  template <class T> const T &Confine(const T &x, const T &lower_bound, const T &upper_bound);
  template <class T> const T &Scale(const T &x, const T &min, const T &max);
}

#endif
