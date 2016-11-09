#ifndef SD_CARD_SRC_SD_SD_H_
#define SD_CARD_SRC_SD_SD_H_

#include <ff.h>

class Sd {
 public:
  static Sd &instance();
  void Setup() const;

  // open (f_open)
  // read (f_read)
  // write (f_write)
  // close (f_close)
  // sync??? (f_sync)

  // available space (f_getfree)
  // find (f_stat)
  // change dir ()


 private:
  Sd();
};

#endif //SD_CARD_SRC_SD_SD_H_
