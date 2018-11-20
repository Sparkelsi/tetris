#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <ncurses.h>

#define SHAPEI  2
#define SHAPEJ  4

class Shapes {
public:
    Shapes();
    Shapes(int shapeID);
    ~Shapes() = default;

    int getShapeID();
    int getShape(int x, int y);
    void makeShape(int shapeID);
    void printShape(WINDOW *nextShapes, int y, int x);


private:
    int shapeID;
    int shape[2][4];


};



#endif
