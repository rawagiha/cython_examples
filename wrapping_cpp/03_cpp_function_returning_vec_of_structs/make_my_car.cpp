#include<string>
#include <vector>

#include "make_my_car.h"


Car::Car() {};

Car::Car( std::string _make, std::string _color, int _mpg )
{
    make = _make;
    color = _color;
    mpg = _mpg;
}

std::vector<Car> make_cars( const std::vector<std::string> & makes,
                            const std::vector<std::string> & colors, const std::vector<int> & mpgs )
{

    std::vector<Car> cars;
    for ( size_t i = 0  ; i < makes.size(); ++i ) {
        cars.emplace_back( Car( makes[i], colors[i], mpgs[i] ) );
    }

    return cars;
}
