#include "mp.hpp"

#include <iostream>

int main(int argc, char** argv) {
  MP::BasicInteger<uint8_t> a = 0, b = 1, c;
  for(int i = 0; i < 100; ++i) {
    c = a + b;
    a = b;
    b = c;
  }
  std::cout << "u100 = " << c.hex() << "; expected value: 0x1f12062f76909038c5\n";
  std::cout << "u101 = " << (a+b).hex() << "; expected value: 0x3245e1a61e5624f888\n";
}
