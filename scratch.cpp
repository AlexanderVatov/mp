#include "mp.hpp"

#include <iostream>

int main(int argc, char const *argv[]) {
  MP::BasicInteger<unsigned char> x = 255, y = 255;
  // std::cout << long(x + y) << std::endl;
  x += y;
  std::cout << long(x) << std::endl;

  return 0;
}
