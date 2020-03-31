#ifndef MP_HPP
#define MP_HPP

namespace MP {
  template <typename Fragment>
  class BasicInteger {
  public:
    BasicInteger(long value = 0);
    ~BasicInteger();

    operator long() const;

  private:
    bool positive;
    int size;
    Fragment* fragments;
  };

  typedef BasicInteger<unsigned char> Integer;
}

#include "mp.template"

#endif
