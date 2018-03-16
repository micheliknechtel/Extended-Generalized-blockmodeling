//
//  Graph.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 13/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>

class Graph {
    bool diagonalLoop;
public:
    bool itsSymmetricGraph;
    Graph(bool itsSymmetricGraph, bool diagonalLoop);
    void toString();
};
#endif /* Graph_hpp */
