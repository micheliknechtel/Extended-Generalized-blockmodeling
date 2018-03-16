//
//  RowDominant.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 22/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef RowDominant_hpp
#define RowDominant_hpp

#include "Constraints.hpp"
#include <stdio.h>

class RowDominant:public Constraints {
    
public:
    void rowDominantWithoutDiagonal();
    void rowDominantWithoutDiagonal_All();
    void rowDominantWithoutDiagonal_OffDiagonal();
    void rowDominantWithoutDiagonal_Diagonal();
    
    void rowDominantDiagonalZero();
    void rowDominantDiagonalZero_All();
    void rowDominantDiagonalZero_OffDiagonal();
    void rowDominantDiagonalZero_Diagonal();
    
    void rowDominantDiagonalOne();
    void rowDominantDiagonalOne_All();
    void rowDominantDiagonalOne_OffDiagonal();
    void rowDominantDiagonalOne_Diagonal();
    void setConstraint(IloExpr expr_01, IloExpr expr_02, FunctionType type, FunctionRelease release, string ctrName, int k, int l);
};

#endif /* RowDominant_hpp */
