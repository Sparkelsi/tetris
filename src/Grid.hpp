/*
Tetris Inspired Game - Project for Data Structures
Kelsi Andrews
Karen Nason

Header file for Grid Class in Tetris Inspired Game

*/

#ifndef GRID_HPP
#define GRID_HPP
#include "Shapes.hpp"
#include <stdlib.h> //srand, random
#include <time.h>   //time
#include <ncurses.h>
#include <unistd.h>
#include <list>

#define FIELDSIZE 24   // defined macros bc it was easier when changing size of field
//#define FIELDSIZE 24

// tbh ya might wanna keep it as a square, the size of the field
// if we do that, we don't need 2 macros anymore

class Grid {
public:
    Grid();
    ~Grid() = default;

    void createList();
    Shapes getRandomShape();
    void insertShape(Shapes x, WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions);
    void pullShape(WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions);
    int getCoord(int y, int x);
    void resetGrid(); //testing purposes
    void colorParams(WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions, WINDOW *menu);    void move(WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void moveRight(WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void moveLeft(WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void moveDown();
    void moveAllDown();
    void rotate(int gridShape, WINDOW *field, WINDOW *nextShapes, WINDOW *score);
    void clearRow();
    void shiftRow();
    void draw_borders(WINDOW *screen);
    void printMenu(WINDOW *menu);
    void printField(WINDOW *field);
    void printNextShapes(WINDOW* nextShapes);
    void printScore(WINDOW *score);
    void printInstructions(WINDOW *instructions);
    void gameOverDisp(WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions);
    void runGame(WINDOW *field, WINDOW *nextShapes, WINDOW *score, WINDOW *instructions);
    void fillRow(); // only used for testing
    void insertNum(int gridShape);
    void incrementNextX();
    void incrementNextY();
    void decrementNextX();
    void incrementX();
    void incrementY();
    void decrementX();
    void makeZero();

private:
    int gridMap[FIELDSIZE][FIELDSIZE]; //original is 10/24
    std::list<Shapes> shapelist;

    static int _score;

    int whichRow;

    int gridShape = 0;
    int shapeRotation = 0;


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
