#include <iostream>
#include "Rectangle.h"


namespace shapes {

    Rectangle::Rectangle () {}

    Rectangle::Rectangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) {
        this->x0 = x0;
        this->y0 = y0;
        this->x1 = x1;
        this->y1 = y1;
    }

    Rectangle::~Rectangle () {}

    unsigned int Rectangle::getArea () {
        return (this->x1 - this->x0) * (this->y1 - this->y0);
    }
    
    void Rectangle::getSize (unsigned int *width, unsigned int *height) {
        (*width) = x1 - x0;
        (*height) = y1 - y0;
    }

    void Rectangle::move (int dx, int dy) {
        this->x0 += dx;
        this->y0 += dy;
        this->x1 += dx;
        this->y1 += dy;
    }
} 
