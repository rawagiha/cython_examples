#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

#include "result.h"

namespace calc {
std::vector<rslt::Result> calculate( const std::vector<int> &,
                                     const std::vector<int> &,
                                     const std::vector<std::string> & );
}
#endif
