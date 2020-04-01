#include <iostream>
using std::cout;

#include "mp.hpp"

MP::BasicInteger<uint16_t> factorial(unsigned int n) {
  MP::BasicInteger<uint16_t> x = 1;
  for(unsigned int i = 2; i <= n; ++i) x*= i;
  return x;
}

int main(int argc, char const *argv[]) {
  cout << "30! = " << factorial(30).hex() << "; expected value: 0x0d13f6370f96865df5dd54000000\n";
  cout << "40! = " << factorial(40).hex()<< "; expected value: 0x8eeae81b84c7f27e080fde64ff05254000000000\n";
}
