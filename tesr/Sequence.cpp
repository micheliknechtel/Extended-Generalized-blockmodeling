//
//  Sequence.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "Sequence.hpp"
#include "DataControler.hpp"

Sequence::Sequence()
{
    networkSize =  DataManager::getDataManager()->networkSize;

}

vector<int> Sequence::random()
{
    vector<int> radomVector;
    
    for (int i =0 ; i<networkSize; i++)
    {
        srand(unsigned(time(0)));
        int radomInteger =  rand() % networkSize  ;
        auto v = find(radomVector.begin(), radomVector.end(), radomInteger);
        while (v !=  radomVector.end())
        {
            radomInteger =  rand() % networkSize  ;
            v = find(radomVector.begin(), radomVector.end(), radomInteger);
        }
        radomVector.push_back(radomInteger);
    }
    random_shuffle (radomVector.begin(), radomVector.end());
    return radomVector;
}

vector<int>Sequence::sequential()
{
    vector<int> sequential;
    
    for (int i =0 ; i<networkSize; i++)
        sequential.push_back(i);
    
    return sequential;
}
