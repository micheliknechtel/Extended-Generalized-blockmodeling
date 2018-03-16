//
//  Preprocessing.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 13/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Preprocessing.hpp"
#include "DataManager.hpp"

Preprocessing::Preprocessing(int networkSize, int** relationMatrix)
{
    this->networkSize = networkSize;
    this->relationMatrix = relationMatrix;
}

Graph *  Preprocessing::processingData()
{
    return  new Graph (isSymmetric(),diagonalType());
}

bool Preprocessing::isSymmetric()
{
    for (int i = 1; i<=networkSize-1; i++)
    {
        for (int j = 0; j<=i-1; j++)
        {
            if(relationMatrix[i][j] != relationMatrix[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

bool Preprocessing::diagonalType()
{
    for (int i = 0; i<networkSize; i++)
    {
        if(relationMatrix[i][i] != 1)
        {
            return false;
        }
    }
    return true;
}

