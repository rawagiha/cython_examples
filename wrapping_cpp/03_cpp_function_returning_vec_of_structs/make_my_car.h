#ifndef MAKE_MY_CAR_H
#define MAKE_MY_CAR_H

#include<string>
#include <vector>

struct Car {
    std::string make;
    std::string color;
    int mpg;

    Car ();
    Car ( std::string make, std::string color, int mpg );
};

std::vector<Car> make_cars( const std::vector<std::string> &,
                            const std::vector<std::string> &, const std::vector<int> & );

#endif
