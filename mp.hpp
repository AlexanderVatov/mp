#ifndef MP_HPP
#define MP_HPP

// C++11 is required for performance reasons.
#pragma clang diagnostic ignored "-Wc++11-extensions"

#include <limits>
#include <string>

namespace MP {
  template <typename Fragment>
  class BasicInteger {
    static_assert (std::numeric_limits<Fragment>::is_integer
      && !std::numeric_limits<Fragment>::is_signed,
    "Fragment type must be of integer type and unsigned (unsigned char, unsigned short, unsigned int, etc)");

  public:
    BasicInteger(long value = 0);
    BasicInteger(BasicInteger<Fragment> &&) = default; //Default move constructor
    ~BasicInteger();


    inline unsigned int size() const;
    unsigned int effectiveSize() const;
    std::string hex(bool prepend0x = true) const;

    operator long() const;
    BasicInteger<Fragment> operator+(BasicInteger<Fragment> const &) const;
    BasicInteger<Fragment> operator*(BasicInteger<Fragment> const &) const;
    BasicInteger<Fragment>& operator+=(BasicInteger<Fragment> const &);
    BasicInteger<Fragment>& operator*=(BasicInteger<Fragment> const &);
    BasicInteger<Fragment>& operator=(BasicInteger<Fragment> const &); // Copy
    BasicInteger<Fragment>& operator=(BasicInteger<Fragment> && other); // Move

  protected:
    BasicInteger(long value, unsigned int size);
    void relocate(int newSize);

  private:
    bool positive;
    unsigned int _size;
    Fragment* fragments;
  };

  typedef BasicInteger<uint16_t> Integer;
}

#include "mp.template"

#endif
