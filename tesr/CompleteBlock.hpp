//
//  CompleteBlock.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 29/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef CompleteBlock_hpp
#define CompleteBlock_hpp

#include <stdio.h>
#include "Constraints.hpp"

class CompleteBlock : public Constraints{
    
public:
    void completeBlockDiagonalOne();
    void completeBlockDiagonalZero();
    void completeBlockWithoutDiagonal();
    void addConstraintDiagonalEqualsOne(IloExpr expr_02, int k, int l);
    void addConstraintDiagonalEqualsZero(IloExpr expr_02, int k, int l);
    void addConstraintWithoutDiagonal(IloExpr expr_02, int k, int l);
    void setConstraint(string ctrName, FunctionType type,   IloExpr expr_01,  IloExpr expr_02,  int k, int l );
};
#endif /* CompleteBlock_hpp */
