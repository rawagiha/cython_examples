from libcpp.string cimport string
from libcpp.vector cimport vector


cdef extern from "result.h" namespace "rslt":
    cdef cppclass Result:
        Result(int, int, string) except +
        
        int x, y, z
        string operation
        
        string get_result()
        

cdef extern from "calculator.h" namespace "calc":
    vector[Result] calculate(vector[int] &, vector[int] &, vector[string] &)
    
    
class RunCalculator(object):
    def __init__(self, first_inputs, second_inputs, operations):
        results = calculate(first_inputs, second_inputs, operations)
        n = results.size()
        
        for i in range(n):
            print(results[i].get_result())
        
