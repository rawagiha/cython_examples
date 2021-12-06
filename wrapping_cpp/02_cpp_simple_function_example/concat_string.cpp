#include <string>
#include <vector>

#include "concat_string.h"

std::string my_str_space::concat( std::vector<std::string> v )
{

    std::string ret = "";
    for ( std::vector<std::string>::iterator itr = v.begin(); itr != v.end();
            ++ itr ) {
        ret += ( *itr );
    }

    return ret;
}
