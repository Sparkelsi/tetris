#ifndef GRID_HPP
#define GRID_HPP
#include "Shapes.hpp"
#include <ncurses.h>
#include <list>

#define FIELDSIZE 24

class Grid {
public:
    Grid();
    ~Grid() = default;

    void printGrid();
    void insertShape(Shapes x);
    void createList();
    Shapes getRandomShape();
    void pullShape();
    // void addShape();
    int getCoord(int y, int x);
    void printList(WINDOW* nextShapes); //for testing purposes only
    void resetGrid(); //testing purposes

private:
    int gridMap[FIELDSIZE][FIELDSIZE]; //original is 10/24
    //int score;
    std::list<Shapes> shapelist;
};


#endif
