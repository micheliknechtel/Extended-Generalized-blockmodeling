//
//  ColumnFunctional.hpp
//  GBlockModeling - current
//
//  Created by Micheli  Knechtel on 12/08/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef ColFunctional_hpp
#define ColFunctional_hpp

#include <stdio.h>
#include "Constraints.hpp"

class ColumnFunctional:public Constraints {
    
public:
    void columnFunctional();
    void modulusOmega();
    void colFunctional_All();
    void colFunctional_OffDiagonal();
    void colFunctional_Diagonal();
    void setConstraint(string ctrName, FunctionType type, IloExpr expr_01, IloExpr expr_02, int k, int l);
};

#endif /* ColFunctional_hpp */
