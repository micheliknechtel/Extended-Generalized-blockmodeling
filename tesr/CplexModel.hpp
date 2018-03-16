//
//  CplexModel.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 16/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef CplexModel_hpp
#define CplexModel_hpp

#include <stdio.h>
#include "Constraints.hpp"

class CplexModel {
    bool injected = false;
      
public:
    void solveCplexModel();
    void setParam(IloCplex cplex);
    void setMIPstart(Constraints *constraints, IloEnv env, IloCplex cplex);
};

#endif /* CplexModel_hpp */
