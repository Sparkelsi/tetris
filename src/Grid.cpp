#include "Grid.hpp"
#include "Shapes.hpp"
#include <ncurses.h>
#include <iostream>
#include <random>

// #define FIELDSIZE = 24;

Grid::Grid()
    {
        for(int i = 0; i < FIELDSIZE; i++) {
            for(int j = 0; j < FIELDSIZE; j++) {
                gridMap[i][j] = 0; //nullptr
            }
        }
    }

void Grid::printGrid()
{
    for(int i = 0; i < FIELDSIZE; i++) {
        for(int j = 0; j < FIELDSIZE; j++) {
            if(gridMap[i][j] == 0){ //nullptr
                printw("%d", 0);
            } else {
                printw("%d", gridMap[i][j]);// = nullptr;
            }
        }
       // std::cout << "\n";
    }
}

void Grid::insertShape(Shapes z) //will always be inserted at same insertion point
{
    int x;
    int y;                                   //i and j are at insertion point
        for(int i = 1; i < 3; i++) {        //when you make the final grid, be sure to add the numbers in the middle of the grid in the right spots
            for(int j = 10; j < 14; j++) {
                x = i - 1;// - 9;
                y = j - 10;// - 1;
                gridMap[i][j] = z.getShape(y, x);
            }
        }
}

void Grid::createList()
{

    for(int i = 0; i < 5; i++)
    {
        shapelist.push_back(getRandomShape());
    }
    //printList();
    //std::cout << "list created^^\n";
}

Shapes Grid::getRandomShape()
{
    std::random_device placeShape;
    std::mt19937 gen(placeShape());
    std::uniform_int_distribution<> distOne(1, 7);
    Shapes tmp(distOne(gen));
    // int temp = distOne(gen);
    // Shapes tmp(temp);
    return tmp;
}

void Grid::pullShape()
{
    if(shapelist.empty()) {
        createList();
    }

    insertShape(shapelist.front());
    //if(!shapelist.empty())
    shapelist.pop_front();
    //int temp = getRandomShape();
    //Shapes tmp(getRandomShape());
    //mvprintw(1, 1, tmp);
    shapelist.push_back(getRandomShape());

}

// void Grid::addShape()
// {
//     shapelist.push_back(getRandomShape());
// }

int Grid::getCoord(int y, int x)
{
    return gridMap[x][y];
}

void Grid::printList(WINDOW* nextShapes)
{
    int y = 3;
    int x = 10;
    int i = 0;
    Shapes tmp;
  // mvwprintw(nextShapes, y, x, "%d", 4);
    //mvwprintw(score, 1, 1, "Score: ");
    for(auto it : shapelist) {
        tmp = it.getShapeID();
        tmp.printShape(nextShapes, y, x);
        //wprintw(nextShapes, "%d", tmp.printShape(x, y));
        y += 3;
        //wrefresh(nextShapes);
       // tmp.printShape();
        //printw("\n");
        i++;
    }
}

void Grid::resetGrid()
{
    for(int i = 0; i < FIELDSIZE; i++) {
        for(int j = 0; j < FIELDSIZE; j++)
        {
            gridMap[i][j] = 0;
        }
    }
}
