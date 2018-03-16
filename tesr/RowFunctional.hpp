//
//  RowFunctional.hpp
//  GBlockModeling - current
//
//  Created by Micheli  Knechtel on 13/08/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef RowFunctional_hpp
#define RowFunctional_hpp

#include <stdio.h>
#include "Constraints.hpp"

class RowFunctional:public Constraints {
    
public:
    void rowFunctional();
    void modulusAlfa();
    void rowFunctional_All();
    void rowFunctional_OffDiagonal();
    void rowFunctional_Diagonal();
    void setConstraint(string ctrName, FunctionType type, IloExpr expr_01, IloExpr expr_02, int k, int l);
};

#endif /* RowFunctional_hpp */
