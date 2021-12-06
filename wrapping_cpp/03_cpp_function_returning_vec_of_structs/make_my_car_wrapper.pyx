from libcpp.string cimport string
from libcpp.vector cimport vector


cdef extern from "make_my_car.h":
    cdef cppclass Car:
        Car() except +
        Car(string, string, int) except +
        string make, color
        int mpg

    vector[Car] make_cars(vector[string] &, vector[string] & , vector[int] &)


def py_make_cars(makes, colors, mpgs):
    cars = make_cars(makes, colors, mpgs)
    carlst = []
    for car in cars:
        d = {}
        d["make"] = car.make
        d["color"] = car.color
        d["mpg"] = car.mpg
        
        carlst.append(d)
    
    return carlst 
