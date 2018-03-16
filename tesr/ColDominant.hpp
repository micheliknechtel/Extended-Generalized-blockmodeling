//
//  ColDominant.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 27/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef ColDominant_hpp
#define ColDominant_hpp

#include <stdio.h>
#include "Constraints.hpp"

class ColDominant:public Constraints {
    
public:
    
    void colDominantWithoutDiagonal();
    void colDominantWithoutDiagonal_All();
    void colDominantWithoutDiagonal_OffDiagonal();
    void colDominantWithoutDiagonal_Diagonal();
    
    void colDominantDiagonalZero();
    void colDominantDiagonalZero_All();
    void colDominantDiagonalZero_OffDiagonal();
    void colDominantDiagonalZero_Diagonal();
    
    void colDominantDiagonalOne();
    void colDominantDiagonalOne_All();
    void colDominantDiagonalOne_OffDiagonal();
    void colDominantDiagonalOne_Diagonal();
    void setConstraint(IloExpr expr_01, IloExpr expr_02, FunctionType type, FunctionRelease release, string ctrName, int k, int l);
};

#endif /* ColDominant_hpp */
