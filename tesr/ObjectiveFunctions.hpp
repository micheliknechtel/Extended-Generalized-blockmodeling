//
//  ObjectiveFunctions.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 19/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef ObjectiveFunctions_hpp
#define ObjectiveFunctions_hpp
#include "Definitions.h"
#include <stdio.h>

class ObjectiveFunctions
{
    IloEnv env;
    IloModel model;
    int clusterUpperBound;
public:
    ObjectiveFunctions(IloEnv env, IloModel model);
    void setObjectiveFunctionMax(IloExpr objectiveFunction);
    void setObjectiveFunctionMin(IloExpr objectiveFunction);
};

#endif /* ObjectiveFunctions_hpp */
