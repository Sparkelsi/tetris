#include <iostream>
#include <list>
#include "Shapes.hpp"
#include "Grid.hpp"

int main() {


//this is a commented line.
    // std::random_device whatShapes;
    // std::mt19937 gen(whatShapes());
    // std::uniform_int_distribution<int> distOne(1, 5);

    //std::list<Shapes> shapeList
    Grid myGrid = Grid();
    //myGrid.printGrid();

    Shapes first = Shapes();
    //first.printShape();
    //std::cout << "first\n\n";
    Shapes second = Shapes(1);
    //second.printShape();
    //std::cout << "second\n\n";
    myGrid.insertShape(second);

    myGrid.printGrid();
    //Shapes second = Shapes(1);
    //second.printShape();

}
