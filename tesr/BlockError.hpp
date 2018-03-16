//
//  BlockError.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef BlockError_hpp
#define BlockError_hpp

#include <stdio.h>
#include <map>
#include <vector>

using namespace std;
class BlockError
{
    int **relationMatrix;
public:
    BlockError();
    int colFunctional(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    int rowFunctional(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    int regularBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    int rowRegular(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    int colRegular(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    int rowDominant(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    int colDominant(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    int nullBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    int completeBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
};

#endif /* BlockError_hpp */
