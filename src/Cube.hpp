#ifndef CUBE_HPP
#define CUBE_HPP

#include "Shapes.hpp"

class Cube : public Shapes {
public:
    Cube();
    ~Cube() = default;

    int getShapeID() { return shapeID; }




private:
    int shapeID = 1;
    int shape[4][4];


};



#endif
