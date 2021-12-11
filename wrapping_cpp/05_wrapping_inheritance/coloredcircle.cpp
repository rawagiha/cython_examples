#include <string>

#include "circle.h"
#include "coloredcircle.h"


ColoredCircle::ColoredCircle(int r, const std::string & color) : Circle(r) {
    color_ = color;
}

void ColoredCircle::change_color(const std::string & new_color) {
    color_ = new_color;
}


