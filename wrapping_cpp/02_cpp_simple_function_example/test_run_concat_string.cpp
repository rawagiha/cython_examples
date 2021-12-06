#include <iostream>
#include <vector>
#include <string>

#include "concat_string.h"

int main()
{
    std::vector<std::string> input = {"THIS", "_", "IS_A", "_PEN.\n"};

    std::cout << my_str_space::concat( input );
}
