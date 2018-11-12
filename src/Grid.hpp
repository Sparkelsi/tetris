#ifndef GRID_HPP
#define GRID_HPP
#include "Shapes.hpp"
#include <list>

class Grid {
public:
    Grid();
    ~Grid() = default;

    void printGrid();
    void insertShape(Shapes x);
    void createList();
    Shapes getRandomShape();
    void pullShape();

private:
    int gridMap[12][12]; //original is 10/24
    std::list<Shapes> shapelist;
};


#endif
