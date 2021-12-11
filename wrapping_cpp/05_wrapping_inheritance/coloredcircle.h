#ifndef COLOREDCIRCLE_H
#define COLOREDCIRCLE_H 

#include "circle.h"

struct ColoredCircle : public Circle {
    std::string color_;

    ColoredCircle(int, const std::string &);

    void change_color(const std::string &);
};


#endif
