#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace shapes {
    class Rectangle {
        public:
            unsigned int x0, y0, x1, y1;
            Rectangle();
            Rectangle(unsigned int x01, unsigned int y0, unsigned int x1, unsigned int y1);
            ~Rectangle();

            unsigned int getArea();
            void getSize(unsigned int* width, unsigned int* height);
            void move(int dx, int dy);
    };   
} //end of name space 

#endif 
