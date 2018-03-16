//
//  RegularBlock.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 19/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef RegularBlock_hpp
#define RegularBlock_hpp

#include <stdio.h>
#include "Constraints.hpp"
#include "NullBlock.hpp"

class RegularBlock:public Constraints{
    
public:
    void regularBlock();
    void setConstraint(string ctrName, FunctionType type,   IloExpr expr_01,  IloExpr expr_02,  int k, int l );
};

#endif /* RegularBlock_hpp */
