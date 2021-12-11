#include <string>

#include "circle.h"

static double PI = 3.14;

Circle::Circle(int r) {
    r_ = r;
}

double Circle::get_area() {
    return (r_ * r_ * PI);   
}


/*void ColoredCircle::change_color(const std::string & new_color) {
    color_ = new_color;
}
*/

