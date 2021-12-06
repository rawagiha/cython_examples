#include <iostream>
#include <vector>
#include <string>

#include "result.h"
#include "calculator.h"

int main() {
    std::vector<int> x = {4, 3, 6, 8};
    std::vector<int> y = {76, 42, 21, 467};
    std::vector<std::string> op = {"addition", "subtraction", "subtraction", "addition"};

    std::vector<rslt::Result> res = calc::calculate(x, y, op);

    for (size_t i = 0; i < res.size(); ++i) {
        std::cout << res[i].get_result() << std::endl;
    }
}
