#ifndef SHAPES_HPP
#define SHAPES_HPP

class Shapes {
public:
    Shapes();
    Shapes(int shapeID);
    ~Shapes() = default;

    int getShapeID();
    int getShape(int x, int y);
    //int getShapej(int x, int y);
    void makeShape(int shapeID);
    void printShape();
    //int getShapeID() { return shapeID; }


private:
    int shapeID;
    int shape[4][4];


};



#endif
