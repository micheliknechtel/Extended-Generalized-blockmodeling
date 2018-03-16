//
//  Graph.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 13/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Graph.hpp"

#include <iostream>
using namespace std;

Graph::Graph(bool itsSymmetricGraph, bool diagonalLoop)
{
    this->itsSymmetricGraph = itsSymmetricGraph;
    this->diagonalLoop = diagonalLoop;
}

void Graph::toString()
{
    cout<<"itsSymmetricGraph = "<<(itsSymmetricGraph==true?"yes":"no")<<" diagonalLoop = "<<(diagonalLoop==true?"yes":"no")<<endl;
}