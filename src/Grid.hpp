#ifndef GRID_HPP
#define GRID_HPP
#include "Shapes.hpp"
#include <stdlib.h> //srand, random
#include <time.h>   //time
#include <ncurses.h>
#include <unistd.h>
#include <list>

#define FIELDSIZEX 24   // defined macros bc it was easier when changing size of field
#define FIELDSIZEY 24

//tbh ya might wanna keep it as a square, the size of the field

class Grid {
public:
    Grid();
    ~Grid() = default;

    void printGrid(); // i think we can delete this
    void createList();
    Shapes getRandomShape();
    void insertShape(Shapes x, WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void pullShape(WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    int getCoord(int y, int x);
    void resetGrid(); //testing purposes
    void move(WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void moveRight(WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void moveLeft(WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void moveDown();
    void moveAllDown();
    void rotate(WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void clearRow();
    void draw_borders(WINDOW *screen);
    void printField(WINDOW *field);
    void printNextShapes(WINDOW* nextShapes);
    void printScore(WINDOW *score);
    void gameOverDisp(WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void fillRow(); // only used for testing

private:
    int gridMap[FIELDSIZEX][FIELDSIZEY]; //original is 10/24
    //int score;
    std::list<Shapes> shapelist;

    int tempColor;


    int yOne = 0;
    int yTwo = 0;
    int yThree = 0;
    int yFour = 0;

    int nextyOne = 0;
    int nextyTwo = 0;
    int nextyThree = 0;
    int nextyFour = 0;

    int xOne = 0;
    int xTwo = 0;
    int xThree = 0;
    int xFour = 0;

    int nextxOne = 1;
    int nextxTwo = 1;
    int nextxThree = 1;
    int nextxFour = 1;
};


#endif
