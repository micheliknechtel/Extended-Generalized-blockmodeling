//
//  ConstraintManager.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 16/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef ConstraintManager_hpp
#define ConstraintManager_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include "Definitions.h"
#include "Constraints.hpp"

typedef void (Constraints::*ptrFunctions)();

struct correlation
{
    string name;
    bool isAlreadyAdded;
    constraintsEnum type;
    FunctionRelease release;
};

class ConstraintManager {
    
    static ConstraintManager *ctrManager;

    map<string, correlation> constraintManager;
    map<string, vector<string>> functionConstraintMap;
    void loadingStructure();

    ptrFunctions allFunctions [46]=
    {
        &Constraints::sharedConstraints,
        &Constraints::diagonalSumEqualsZero,
        &Constraints::diagonalSumEqualsOne,
        &Constraints::totalBlockSumEqualsZero,
        &Constraints::totalBlockSumEqualsOne,
        &Constraints::nullBlockDiagonalEqualsZero,
        &Constraints::nullBlockDiagonalEqualsOne,
        &Constraints::nullBlockWithoutDiagonal,
        &Constraints::completeBlockDiagonalZero,
        &Constraints::completeBlockDiagonalOne,
        &Constraints::completeBlockWithoutDiagonal,
        &Constraints::rowRegular,
        &Constraints::rowRegularError,
        &Constraints::sumEmptyCluster,
        &Constraints::colRegular,
        &Constraints::colRegularError,
        &Constraints::regularBlock,
        &Constraints::rowDominantWithoutDiagonal,
        &Constraints::sumOverF,
        &Constraints::w_sum,
        &Constraints::z_sum,
        &Constraints::z_smaller_x,
        &Constraints::linesError,
        &Constraints::o_bigger_lineError_plus_bigM,
        &Constraints::o_smaller_lineError,
        &Constraints::o_smaller_z,
        &Constraints::h_smaller_lineError,
        &Constraints::h_bigger_o,
        &Constraints::colDominantWithoutDiagonal,
        &Constraints::b_sum,
        &Constraints::b_smaller_x,
        &Constraints::columnsError,
        &Constraints::a_smaller_columnError,
        &Constraints::a_smaller_b,
        &Constraints::c_smaller_columnError,
        &Constraints::c_bigger_a,
        &Constraints::a_bigger_columnError_plus_bigM,
        &Constraints::rowDominantDiagonalZero,
        &Constraints::rowDominantDiagonalOne,
        &Constraints::colDominantDiagonalZero,
        &Constraints::colDominantDiagonalOne,
        &Constraints::columnFunctional,
        &Constraints::modulusOmega,
        &Constraints::rowFunctional,
        &Constraints::modulusAlfa
};

    
public:
    static ConstraintManager* getConstraintManager();
    ConstraintManager();
    void addFunctionConstraints(FunctionType type, Constraints *c);
    vector<string>getSet(FunctionType type);
};
#endif /* ConstraintManager_hpp */
