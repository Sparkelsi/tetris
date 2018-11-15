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
    //int getShapej(int x, int y);
    void makeShape(int shapeID);
    void printShape(WINDOW *nextShapes, int y, int x);
    //int getShapeID() { return shapeID; }


private:
    int shapeID;
    int shape[SHAPEI][SHAPEJ];


};



#endif
