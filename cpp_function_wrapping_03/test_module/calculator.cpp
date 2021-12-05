#include <string>
#include <vector>

#include "result.h"
#include "calculator.h"

std::vector<rslt::Result> calc::calculate( const std::vector<int> &
        first_inputs,
        const std::vector<int> & second_inputs,
        const std::vector<std::string> & operations )
{
    std::vector<rslt::Result> results;
    for ( size_t i = 0; i < first_inputs.size(); ++i ) {
        results.emplace_back( rslt::Result( first_inputs[i], second_inputs[i],
                                            operations[i] ) );
    }
    return results;
}
