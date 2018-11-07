#include <iostream>
#include <list>
#include "Shapes.hpp"
#include "Grid.hpp"

int main() {

    Grid myGrid = Grid();

    Shapes empty = Shapes();
    Shapes cube = Shapes(1);
    Shapes line = Shapes(2);
    Shapes Tshape = Shapes(3);
    Shapes Sshape = Shapes(4);
    Shapes Zshape = Shapes(5);
    Shapes Lshape = Shapes(6);
    Shapes mirroredL = Shapes(7);

    mirroredL.printShape();

    std::cout << "shape^^ \n\n";

    myGrid.insertShape(mirroredL);

    myGrid.printGrid();

}
