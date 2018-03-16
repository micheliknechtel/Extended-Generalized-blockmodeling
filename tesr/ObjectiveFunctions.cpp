//
//  ObjectiveFunctions.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 19/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "ObjectiveFunctions.hpp"
#include "DataManager.hpp"


ObjectiveFunctions::ObjectiveFunctions(IloEnv env, IloModel model)
{
    this->env = env;
    this->model = model;
}

void ObjectiveFunctions::setObjectiveFunctionMax(IloExpr objectiveFunction)
{
    model.add(IloMaximize(env, objectiveFunction));
}

void ObjectiveFunctions::setObjectiveFunctionMin(IloExpr objectiveFunction)
{
    model.add(IloMinimize(env, objectiveFunction));
}
