#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace shapes {
    class Rectangle {
            int x0, y0, x1, y1;
        public:    
            Rectangle();
            Rectangle(int x01, int y0, int x1, int y1);
            ~Rectangle();
            int getArea();
            void getSize(int* width, int* height);
            void move(int dx, int dy);
    };   
} //end of name space 

#endif 
