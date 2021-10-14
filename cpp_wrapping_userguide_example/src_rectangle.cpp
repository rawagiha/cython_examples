#include "Rectangle.h"
#include "iostream"

int main() {
    shapes::Rectangle r1(3, 4, 12, 7);

    unsigned int w ;
    unsigned int h;

    r1.getSize(&w, &h);
    std::cout << "width is: " << w << " and height is: " << h << std::endl;
    

}
