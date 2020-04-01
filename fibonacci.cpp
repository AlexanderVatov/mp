#include "mp.hpp"

#include <iostream>

int main(int argc, char** argv) {
  MP::BasicInteger<uint8_t> a = 0, b = 1, c;
  for(int i = 0; i < 100; ++i) {
    c = a + b;
    a = b;
    b = c;
  }
  if(c.hex() == "0x1f12062f76909038c5")
    std::cout << "Result for u100 matches the expected value!\n";

  std::cout << "u101 (in hexadecimal): " << (a + b).hex() << std::endl;
}
