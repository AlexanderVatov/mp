// #include "mp.hpp"

#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {
  // MP::BasicInteger<unsigned char> x = 255, y = 255;
  // // std::cout << long(x + y) << std::endl;
  // x += y;
  // std::cout << long(x) << std::endl;
  //
  // return 0;

  uint8_t x = 100, y = 100, z = 250;
  x *= y;
  x += z;
  cout << int(x) << endl;
}
