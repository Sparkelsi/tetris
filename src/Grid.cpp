#include "Grid.hpp"
#include "Shapes.hpp"
#include <iostream>

Grid::Grid()
    {
        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 12; j++) {
                gridMap[i][j] = 0; //nullptr
            }
        }
    }

void Grid::printGrid()
{
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 12; j++) {
            if(gridMap[i][j] == 0){ //nullptr
                std::cout << 0;
            } else {
                std::cout << gridMap[i][j];// = nullptr;
            }
        }
        std::cout << "\n";
    }
}

void Grid::insertShape(Shapes x) //will always be inserted at same insertion point
{
    int w;                                   //i and j are at insertion point
        for(int i = 0; i < 2; i++) {        //when you make the final grid, be sure to add the numbers in the middle of the grid in the right spots
            for(int j = 3; j < 7; j++) {
                w = j - 4;
                gridMap[i][j] = x.getShape(i, w);
            }
        }
}

void Grid::createList()
{

    for(int i = 0; i < 5; i++)
    {
        shapelist.push_back(getRandomShape());
    }
}

Shapes Grid::getRandomShape()
{
    int _rando;
    srand(time(NULL));
    _rando = rand() % 7 + 1;    //between 1 and 7

    Shapes temp = _rando;
    return temp;
}

void Grid::pullShape()
{
    Shapes tmp = shapelist.front().getShapeID();

    insertShape(tmp);
    printGrid();
    //if(shapelist.front() == tmp)
    //shapelist.remove(tmp);
    shapelist.push_back(getRandomShape());


    //check if empty
}
