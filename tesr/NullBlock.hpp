//
//  NullBlock.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 28/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef NullBlock_hpp
#define NullBlock_hpp

#include <stdio.h>
#include "Constraints.hpp"

class NullBlock: public Constraints
{
    
public:
    void nullBlockDiagonalEqualsOne();
    void nullBlockDiagonalEqualsZero();
    void nullBlockWithoutDiagonal();
    
    void addConstraintDiagonalEqualsOne(IloExpr expr_02, int k, int l);
    void addConstraintDiagonalEqualsZero(IloExpr expr_02, int k, int l);
    void addConstraintWithoutDiagonal(IloExpr expr_02, int k, int l);
    
    void setConstraint(string ctrName, FunctionType type, IloExpr expr_01, IloExpr expr_02, int k, int l);
    
};

#endif /* NullBlock_hpp */