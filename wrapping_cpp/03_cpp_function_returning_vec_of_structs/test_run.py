#!/usr/bin/env python3

from make_my_car import py_make_cars

makes = [b"toyota", b"nissan", b"honda"]
colors = [b"white", b"gray", b"silver"]
mpgs = [11, 21, 34]

def make_input():
    return makes, colors, mpgs

mycars = py_make_cars( * make_input())
for mycar in mycars:
    print(mycar)
