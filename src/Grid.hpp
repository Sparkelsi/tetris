#ifndef GRID_HPP
#define GRID_HPP
#include "Shapes.hpp"

class Grid {
public:
    Grid();
    ~Grid() = default;

    void printGrid();
    void insertShape(Shapes x);

private:
    int gridMap[12][12]; //original is 10/24
};


#endif
