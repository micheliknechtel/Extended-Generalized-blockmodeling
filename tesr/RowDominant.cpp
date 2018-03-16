//
//  RowDominant.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 22/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "RowDominant.hpp"


void RowDominant::rowDominantWithoutDiagonal()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(RDWD);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        rowDominantWithoutDiagonal_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        rowDominantWithoutDiagonal_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        rowDominantWithoutDiagonal_Diagonal();
    }
}

void RowDominant::rowDominantWithoutDiagonal_Diagonal()
{
    IloExpr expr_02(env);
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        
        IloExpr expr_01(env);
        
    
        for (int j = k; j<networkSize; j++)
                expr_01 += o[j][k][k];
        
        setConstraint(expr_01, expr_02, RDWD, DIAGONAL, "rowDominantWithoutDiagonal", k,k);

    }
    
    setObjectiveFunction(expr_02);
}

void RowDominant::rowDominantWithoutDiagonal_OffDiagonal()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_01(env);
            
            if (k!=l)
            {
                
                for (int i = k; i<networkSize; i++)
                    expr_01 += o[i][k][l];
                
                setConstraint(expr_01, expr_02, RDWD, OFF_DIAGONAL, "rowDominantWithoutDiagonal", k,l);

            }
        }
    }
    
    setObjectiveFunction(expr_02);
}

void RowDominant::rowDominantWithoutDiagonal_All()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_01(env);
            
            for (int i = k; i<networkSize; i++)
                expr_01 += o[i][k][l];
            
            setConstraint(expr_01, expr_02, RDWD, ALL, "rowDominantWithoutDiagonal", k,l);

        }
    }
    
    setObjectiveFunction(expr_02);
}


void RowDominant::rowDominantDiagonalZero()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(RDDZ);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        rowDominantDiagonalZero_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        rowDominantDiagonalZero_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        rowDominantDiagonalZero_Diagonal();
    }
}

void RowDominant::rowDominantDiagonalZero_Diagonal()
{
    IloExpr expr_02(env);
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        
        IloExpr expr_01(env);
        
        
       for (int j = k; j<networkSize; j++)
                expr_01 += o[j][k][k];
        
        expr_01+= dsOne[k][0];
        
        setConstraint(expr_01, expr_02, RDDZ, DIAGONAL, "rowDominantDiagonalZero", k,k);
    
    }
    
    setObjectiveFunction(expr_02);
}

void RowDominant::rowDominantDiagonalZero_OffDiagonal()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_01(env);
            
            if (k!=l)
            {
                for (int i = k; i<networkSize; i++)
                    expr_01 += o[i][k][l];
                
                setConstraint(expr_01, expr_02, RDDZ, OFF_DIAGONAL, "rowDominantDiagonalZero", k,l);
            }
        }
    }
    
    setObjectiveFunction(expr_02);
}

void RowDominant::rowDominantDiagonalZero_All()
{
    IloExpr expr_02(env);
    
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_01(env);
            
            for (int i = k; i<networkSize; i++)
                expr_01 += o[i][k][l];
            
            if (k==l)
                expr_01+= dsOne[k][0];
            
            setConstraint(expr_01, expr_02, RDDZ, ALL, "rowDominantDiagonalZero", k,l);

        }
    }
    
    setObjectiveFunction(expr_02);
}

void RowDominant::rowDominantDiagonalOne()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(RDDO);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        rowDominantDiagonalOne_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        rowDominantDiagonalOne_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        rowDominantDiagonalOne_Diagonal();
    }
}

void RowDominant::rowDominantDiagonalOne_Diagonal()
{
    IloExpr expr_02(env);
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        
        IloExpr expr_01(env);
        
        
       for (int j = k; j<networkSize; j++)
                expr_01 += o[j][k][k];
        
        expr_01+= dsZero[k][0];
        
        setConstraint(expr_01, expr_02, RDDO, DIAGONAL, "rowDominantDiagonalOne", k,k);
    }
    
    setObjectiveFunction(expr_02);
}

void RowDominant::rowDominantDiagonalOne_OffDiagonal()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_01(env);
            
            if (k!=l)
            {
                for (int i = k; i<networkSize; i++)
                    expr_01 += o[i][k][l];
                
                setConstraint(expr_01, expr_02, RDDO, OFF_DIAGONAL, "rowDominantDiagonalOne", k,l);
            }
        }
    }
    
    setObjectiveFunction(expr_02);
}

void RowDominant::rowDominantDiagonalOne_All()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_01(env);
            
            for (int i = k; i<networkSize; i++)
                expr_01 += o[i][k][l];
            
            if (k==l)
                expr_01+= dsZero[k][0] + networkSize * (- 1 + w[get_fPosition(RDDO)][k][l]);
            
            setConstraint(expr_01, expr_02, RDDO, ALL, "rowDominantDiagonalOne", k,l);
            
        }
    }
    
    setObjectiveFunction(expr_02);
}

void RowDominant::setConstraint(IloExpr expr_01, IloExpr expr_02, FunctionType type, FunctionRelease release, string ctrName, int k, int l)
{
//    if (itsSymmetricGraph && k!=l)
//    {
//        IloExpr expr_03(env);
//        
//        for (int j = k; j<networkSize; j++)
//            expr_03 += a[j][k][l];
//        
//        IloConstraint constraint = (f[get_fPosition(type)][l][k]  >=  expr_03 +  networkSize * (- 1 + w[get_fPosition(type)][l][k]));
//        string name = ctrName + SSTR(l) + SSTR(k);
//        constraint.setName(name.c_str());
//        model.add(constraint);
//        expr_02 += f[get_fPosition(type)][l][k];
//    }
    
    if (release != DIAGONAL)
    {
        IloConstraint constraint = (f[get_fPosition(type)][k][l]  >=  expr_01 +  networkSize * (- 1 + w[get_fPosition(type)][k][l]));
        string name = ctrName + SSTR(k) + SSTR(l);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_02 += f[get_fPosition(type)][k][l];
    }
    
    if (release == DIAGONAL)
    {
        IloConstraint constraint = (f[get_fPosition(type)][k][0]  >=  expr_01 +  networkSize * (- 1 + w[get_fPosition(type)][k][0]));
        string name = ctrName + SSTR(k) + SSTR(l);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_02 += f[get_fPosition(type)][k][0];
    }
}




