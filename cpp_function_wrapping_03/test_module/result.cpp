#include <string>

#include "result.h"
#include "addition.h"
#include "subtraction.h"

rslt::Result::Result(int _x, int _y, std::string _operation) {
        x = _x;
        y = _y;
       
        operation = _operation;

        if (_operation == "addition") {
            z = ad::add(_x, _y);
        }
        else {
            z = sb::subtract(_x, _y);
        }
}
    
std::string rslt::Result::get_result() {
        std::string first_input = std::to_string(x);
        std::string second_input = std::to_string(y);
        
        std::string op = "";
        if (operation == "addition") {
            op = " + ";
        }
        else if (operation == "subtraction") {
            op = " - ";
        }
        else {
            
        }
        
        return first_input + op + second_input + " = " + std::to_string(z); 
}
