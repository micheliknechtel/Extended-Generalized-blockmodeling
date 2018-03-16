//
//  NullBlock.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 28/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "NullBlock.hpp"

void NullBlock::nullBlockDiagonalEqualsOne()
{
    IloExpr expr_02(env);
    
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(NBDO);
    addFunction(fDetails);
    
    int limit = clusterUpperBound-1;
    
    if (fDetails.release == ALL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit=k;
            
            for (int l = 0; l<=limit; l++)
                addConstraintDiagonalEqualsOne(expr_02,  k,  l);
        }
    }
    
    if(fDetails.release == DIAGONAL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
            addConstraintDiagonalEqualsOne(expr_02,  k, k);
    }
    
    if(fDetails.release == OFF_DIAGONAL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit=k;
            
            for (int l = 0; l<=limit; l++)
                if (k!=l) addConstraintDiagonalEqualsOne(expr_02,  k, l);
        }
    }
    setObjectiveFunction(expr_02);
}

void NullBlock::nullBlockWithoutDiagonal()
{
    IloExpr expr_02(env);
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(NBWD);
    addFunction(fDetails);
    
    int limit = clusterUpperBound-1;
    
    if (fDetails.release == ALL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit=k;
            
            for (int l = 0; l<=limit; l++)
                addConstraintWithoutDiagonal(expr_02,  k, l);
        }
    }
    else if(fDetails.release == DIAGONAL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
            addConstraintWithoutDiagonal(expr_02,  k, k);
    }
    else if(fDetails.release == OFF_DIAGONAL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit=k;
            
            for (int l = 0; l<=limit; l++)
                if (k!=l) addConstraintWithoutDiagonal(expr_02,   k, l);
        }
    }
    setObjectiveFunction(expr_02);
}


void NullBlock::nullBlockDiagonalEqualsZero()
{
    IloExpr expr_02(env);
    
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(NBDZ);
    addFunction(fDetails);
    
    int limit = clusterUpperBound-1;
    
    if(fDetails.release == ALL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit=k;
            
            for (int l = 0; l<=limit; l++)
                addConstraintDiagonalEqualsZero(expr_02,  k,  l);
        }
    }
    
    if(fDetails.release == DIAGONAL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
            addConstraintDiagonalEqualsZero(expr_02,  k, k);
    }
    
    if(fDetails.release == OFF_DIAGONAL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit=k;
            
            for (int l = 0; l<=limit; l++)
                if (k!=l) addConstraintDiagonalEqualsZero(expr_02,  k, l);
        }
    }
    
    setObjectiveFunction(expr_02);
}

void NullBlock::addConstraintDiagonalEqualsOne(IloExpr expr_02, int k, int l)
{
    IloExpr expr_01(env);
    FunctionRelease releaseSharedVariable   = DataManager::getDataManager()->releaseNullBlock;
    
    if (k == l && releaseSharedVariable==DIAGONAL)
        expr_01 = tbsOne[k][0] + dsZero[k][0];
    
    if (k == l && releaseSharedVariable != DIAGONAL)
        expr_01 = tbsOne[k][l] + dsZero[k][0];
    
    if (k != l)
        expr_01 = tbsOne[k][l];
    
    setConstraint("nullBlockDiagonalEqualsOne", NBDO, expr_01, expr_02, k, l);
}

void NullBlock::addConstraintDiagonalEqualsZero(IloExpr expr_02, int k, int l)
{
    IloExpr expr_01(env);
    
    FunctionRelease releaseSharedVariable   = DataManager::getDataManager()->releaseNullBlock;
   
    if (k == l && releaseSharedVariable==DIAGONAL)
        expr_01 = tbsOne[k][0] + dsOne[k][0];
    
    if (k == l && releaseSharedVariable == OFF_DIAGONAL)
        expr_01 = tbsOne[k][l] + dsOne[k][0];
    
    if (k != l)
        expr_01 = tbsOne[k][l];
    
    setConstraint("nullBlockDiagonalEqualsZero", NBDZ, expr_01, expr_02, k, l);
}

void NullBlock::addConstraintWithoutDiagonal(IloExpr expr_02, int k, int l)
{
    
    FunctionRelease releaseSharedVariable   = DataManager::getDataManager()->releaseNullBlock;
    
    IloExpr expr_01(env);
    
    if (releaseSharedVariable==DIAGONAL)
        expr_01 = tbsOne[k][0];
    else
        expr_01 = tbsOne[k][l];
    
    setConstraint("nullBlockWithoutDiagonal", NBWD, expr_01, expr_02, k, l);
}

void NullBlock::setConstraint(string ctrName, FunctionType type,   IloExpr expr_01,  IloExpr expr_02,  int k, int l )
{
    FunctionRelease releaseCurrentProperty  = DataManager::getDataManager()->getCurrentfDetails().release;
   // bool areThereNonSymmetricProperties     = DataManager::getDataManager()->areThereNonSymmetricPropertie();
    
    if (releaseCurrentProperty == DIAGONAL)
    {
        IloConstraint constraint = (f[get_fPosition(type)][k][0]  >=  expr_01 + networkSize * networkSize * (- 1 + w[get_fPosition(type)][k][0]));
        string name = ctrName + SSTR(k) + SSTR(k);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_02 += f[get_fPosition(type)][k][0];
    }
    
    if (releaseCurrentProperty!=DIAGONAL)
    {
        IloConstraint constraint = (f[get_fPosition(type)][k][l]  >=  expr_01 + networkSize * networkSize * (- 1 + w[get_fPosition(type)][k][l]));
        string name = ctrName + SSTR(k) + SSTR(l);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_02 += f[get_fPosition(type)][k][l];
    }
    
//    if (itsSymmetricGraph && areThereNonSymmetricProperties && k!=l )
//    {
//        IloConstraint constraint = (f[get_fPosition(type)][l][k]  >=  expr_01  + networkSize * networkSize * (- 1 + w[get_fPosition(type)][l][k]));
//        string name = ctrName + SSTR(l) + SSTR(k);
//        constraint.setName(name.c_str());
//        model.add(constraint);
//        expr_02 += f[get_fPosition(type)][l][k];
//    }
}
