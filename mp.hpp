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

//////////////////////////////////////////////////////
/*            Start of implementation               */
//////////////////////////////////////////////////////

#include <sstream>
#include <iostream>
#include <iomanip>

#define MP_TempIntFrag template <typename Fragment>
#define MP_IntFrag MP::BasicInteger<Fragment>

MP_TempIntFrag
MP_IntFrag::BasicInteger(long value) {
  positive = true;
  if (value < 0) {
    positive = false;
    value = -value;
  }
  else if(value == 0) {
    _size = 0;
    fragments = nullptr;
  }
  Fragment unitMask = std::numeric_limits<Fragment>::max();

  _size = 0;
  long value2 = value;
  while(value2) {
    ++_size;
    value2 = value2 >> 8*sizeof(Fragment);
  }

  //Now allocate the array
  fragments = new Fragment[_size]; //Legal even if _size == 0
  for (int i = 0; i < _size; ++i) {
    fragments[i] = value & unitMask;
    value = value >> 8*sizeof(Fragment);
  }

}

MP_TempIntFrag
MP_IntFrag::BasicInteger(long value, unsigned int size) {
  if(value >= 0) positive = true;
  else {
    positive = false;
    value = -value;
  }
  _size = size;

  Fragment unitMask = std::numeric_limits<Fragment>::max();
  fragments = new Fragment[_size];

  for (int i = 0; i < _size; ++i) {
    fragments[i] = value & unitMask;
    value = value >> 8*sizeof(Fragment);
  }
}


MP_TempIntFrag
MP_IntFrag::~BasicInteger() {
  if(fragments) delete [] fragments;
}

MP_TempIntFrag
inline unsigned int MP_IntFrag::size() const {
  return _size;
}

MP_TempIntFrag
unsigned int MP_IntFrag::effectiveSize() const {
  for(int i = _size - 1; i >= 0; --i)
    if (fragments[i] != 0)
      return i + 1;
  return 0;
}

MP_TempIntFrag
std::string MP_IntFrag::hex(bool prepend0x) const {
  std::ostringstream out;
  if(!positive) out << "-";
  if(prepend0x) out << "0x";
  out << std::hex << std::setfill('0');
  for(int i = effectiveSize() - 1; i >= 0; --i) {
    out << std::setw(2*sizeof(Fragment)) << uintmax_t(fragments[i]);
  }
  return out.str();
}


MP_TempIntFrag
MP_IntFrag::operator long() const {
  long result = 0;
  for(int i = 0; i < _size; ++i) {
    result += (unsigned long)fragments[i] << i*8*sizeof(Fragment);
  }
  if(!positive) result = -result;
  return result;
}

MP_TempIntFrag
MP_IntFrag MP_IntFrag::operator+(MP_IntFrag const& other) const {
  //TODO: Replace with subtraction if either is negative
  assert(positive && other.positive);

  const MP_IntFrag *shorter, *longer;
  if(this->_size <= other._size) {
    shorter = this;
    longer = &other;
  } else {
    shorter = &other;
    longer = this;
  }

  MP_IntFrag result(0, longer->_size + 1);

  Fragment carry = 0;
  Fragment max = std::numeric_limits<Fragment>::max();
  int i;
  for(i = 0; i < shorter->_size; ++i) {
    Fragment temp = carry;
    carry = 0;
    if(temp > max - fragments[i]) carry += 1;
    //C++ standard guarrantees modulo overflow for unsigned types
    temp += fragments[i];
    if(temp > max - other.fragments[i]) carry += 1;
    temp += other.fragments[i];

    result.fragments[i] = temp;
  }

  for(; i < longer->_size; ++i) {
    Fragment temp = carry;
    carry = 0;
    if(temp > max - fragments[i]) carry += 1;
    //C++ standard guarrantees modulo overflow for unsigned types
    temp += longer->fragments[i];
    result.fragments[i] = temp;
  }
  result.fragments[result._size - 1] = carry;

  return result;
}

MP_TempIntFrag
MP_IntFrag MP_IntFrag::operator*(MP_IntFrag const& other) const {
    unsigned int k = effectiveSize(), l = other.effectiveSize();
    Fragment carry = 0;
    Fragment base = std::numeric_limits<Fragment>::max();
    MP_IntFrag result(0,  k + l);
    result.positive = (positive == other.positive);
    uintmax_t temp = 0;
    for(unsigned int i = 0; i < k; ++i) {
      carry = 0;
      for (unsigned int j = 0; j < l; ++j) {
        temp = fragments[i] * other.fragments[j] + result.fragments[i+j] + carry;
        carry = temp/base;
        result.fragments[i+j] = temp;
      }
      result.fragments[i + l] = carry;
    }

    return result;
}

MP_TempIntFrag
MP_IntFrag & MP_IntFrag::operator+=(MP_IntFrag const & other) {
  *this = *this + other;
  return *this;
}

MP_TempIntFrag
MP_IntFrag & MP_IntFrag::operator*=(MP_IntFrag const & other) {
  *this = *this * other;
  return *this;
}

MP_TempIntFrag
MP_IntFrag & MP_IntFrag::operator=(MP_IntFrag const & other) {
  if(fragments) delete[] fragments;
  _size = other._size;
  fragments = new Fragment[_size];
  for(int i = 0; i < _size; ++i) fragments[i] = other.fragments[i];
  return *this;
}

//Move assignment
MP_TempIntFrag
MP_IntFrag & MP_IntFrag::operator=(MP_IntFrag&& other) {
    if(this != &other) {
        if(fragments) delete[] fragments;
        fragments = other.fragments;
        _size = other._size;

        // The other object should be left in a valid state
        other.fragments = nullptr;
        other._size = 0;
    }
    return *this;
}

MP_TempIntFrag
void MP_IntFrag::relocate(int newSize) {
  if(_size >= newSize) {
    return;
  }
  Fragment* newFragments = new Fragment[newSize];

  int i = 0;
  for(; i < _size; ++i) newFragments[i] = fragments[i];
  for(; i < newSize; ++i) newFragments[i] = 0;
  _size = newSize;
  fragments = newFragments;
}


#undef MP_TempIntFrag
#undef MP_IntFrag

#endif
