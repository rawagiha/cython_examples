#!/usr/bin/env python3

from make_my_car import py_make_cars

makes = [b"toyota", b"nissan", b"honda"]
colors = [b"white", b"gray", b"silver"]
mpgs = [11, 21, 34]

mycars = py_make_cars(makes, colors, mpgs)
for mycar in mycars:
    print(mycar)
