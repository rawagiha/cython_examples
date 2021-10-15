#include "Rectangle.h"
#include "iostream"

int main() {
    shapes::Rectangle r1(-3, -4, 2, 7);

    int w ;
    int h;

    r1.getSize(&w, &h);
    std::cout << "width is: " << w << " and height is: " << h << std::endl;
}
