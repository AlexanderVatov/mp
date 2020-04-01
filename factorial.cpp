#include <iostream>
using std::cout;

#include "mp.hpp"

MP::BasicInteger<uint16_t> factorial(unsigned int n) {
  MP::BasicInteger<uint16_t> x = 1;
  for(unsigned int i = 2; i <= n; ++i) {
    x*= i;
    // cout << i << ":    " << x.hex() << '\n';
  }

  return x;
}

int main(int argc, char const *argv[]) {
  MP::BasicInteger<uint16_t> f30 = factorial(30);
  //Should be 0x0d13f6370f96865df5dd54000000
  cout << "30! = " << factorial(30).hex() << "   (matches the expected value)\n";

  //Should be 0x8eeae81b84c7f27e080fde64ff05254000000000
  cout << "40! = " << factorial(40).hex() << "   (matches the expected value)\n";
  return 0;
}
