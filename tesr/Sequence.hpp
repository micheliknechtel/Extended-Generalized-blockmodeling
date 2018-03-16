//
//  Sequence.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef Sequence_hpp
#define Sequence_hpp

#include <cmath>
#include <stdio.h>
#include <map>
#include <vector>
#include "DataManager.hpp"

//using namespace std;

class Sequence {
    int networkSize;

    
public:
    Sequence();
    vector<int> random();
    vector<int> sequential();
};

#endif /* Sequence_hpp */
