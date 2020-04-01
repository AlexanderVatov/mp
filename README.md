# Multiple precision integers
The multiple-precision arithmetic is implemented in the `mp.hpp` header and does not need
to be compiled separately. The unit test depends the Boost unit testing framework; the
other programs have no special dependencies. To install Boost, run `brew install boost`
on macOS or `sudo apt-get install libboost-dev` on Debian, Ubuntu, or derivatives. To build
the unit tests on GNU/Linux or macOS, run `g++ mp_test.cpp -o test && ./test --log_level=all`
(or run the included binary for macOS: `./test --log_level=all`). `factorial` and `fibonacci`
can be built in the same way: `g++ fibonacci.cpp -o fibonacci && ./fibonacci` or
`g++ factorial.cpp -o factorial && ./factorial`, respectively. Again, binaries are included
for macOS. To run expmod, run `python expmod.py [a] [b] [n]`.
