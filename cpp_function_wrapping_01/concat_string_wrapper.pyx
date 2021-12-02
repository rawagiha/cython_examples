from libcpp.string cimport string
from libcpp.vector cimport vector

cdef extern from "concat_string.h" namespace "my_str_space":
    string concat(vector[string])

 
def py_concat(v):
    return concat(v)
