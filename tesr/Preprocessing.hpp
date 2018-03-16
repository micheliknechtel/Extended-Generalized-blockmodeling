//
//  Preprocessing.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 13/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Preprocessing_hpp
#define Preprocessing_hpp

#include <stdio.h>
#include "Graph.hpp"

class Preprocessing {
    int networkSize ;
    int** relationMatrix;
public:
    Preprocessing(int networkSize, int** relationMatrix);
    Graph * processingData();
    bool isSymmetric();
    bool diagonalType();
    
};
#endif /* Preprocessing_hpp */
