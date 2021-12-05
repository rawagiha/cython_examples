#ifndef RESULT_H
#define RESULT_H

# include <string>  

namespace rslt {


    struct Result {
        int x;
        int y;
        int z;
        std::string operation;

        Result(int, int, std::string);
    
        std::string get_result();
    };


} // end of res

#endif
