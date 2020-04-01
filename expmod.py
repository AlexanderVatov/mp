#!/usr/bin/env python
from sys import argv
a, b, n = (int(x) for x in argv[1:])
c = 1
for i in reversed(range(b.bit_length())):
    c = c**2 % n
    if b & (1 << i):
        c = (c * a) % n
print(c)