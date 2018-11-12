#include <iostream>
#include <list>
#include <stdlib.h> //srand, random
#include <time.h>   //time
#include "Shapes.hpp"
#include "Grid.hpp"

int main() {

    Grid myGrid = Grid();
    //std::list<Shapes> list;

    myGrid.createList();
    myGrid.pullShape();

    /*int _rando;
    srand(time(NULL));
    _rando = rand() % 7 + 1;    //between 1 and 7

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

    list.push_back(cube);
    list.push_back(line);
    list.push_back(Lshape);*/

    /*int i = 0;
    Shapes tmp;
    for(auto it : list)
    {
        ++i;
        tmp = it;
    }
    tmp.printShape();

    myGrid.insertShape(tmp);
    myGrid.printGrid();


    Shapes temp = _rando;
    myGrid.insertShape(temp);
    myGrid.printGrid();
    std::cout << std::endl;*/


}
