#include <iostream>
#include <string>

#include "circle.h"
#include "coloredcircle.h"

int main() {
    Circle c = Circle(3);
    std::cout << c.get_area() << std::endl;
    
    ColoredCircle cc = ColoredCircle(4, "yellow");
    cc.change_color("silver");
    std::cout << cc.color_ << std::endl; 
    std::cout << cc.get_area() << std::endl;
}
