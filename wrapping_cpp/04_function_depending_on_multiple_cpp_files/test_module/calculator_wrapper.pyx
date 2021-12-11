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
        
        # populate class member using return from the c++ function
        self.result_lst = [results[i].get_result().decode() for i in range(n)]
        print(self.result_lst)
        
        # must to allocate in heap
        cdef Result *prslt
        
        prslt = new Result(4, 5, "subtraction")
        
        try:
            print(prslt.get_result())
        finally:
            del prslt

        #for i in range(n):
        #    print(results[i].get_result())
        
