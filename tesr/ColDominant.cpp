//
//  ColDominant.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 27/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "ColDominant.hpp"

/*********************************************************/
/*Without Diagonal*/
/*********************************************************/

void ColDominant::colDominantWithoutDiagonal()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(CDWD);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        colDominantWithoutDiagonal_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        colDominantWithoutDiagonal_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        colDominantWithoutDiagonal_Diagonal();
    }
}


void ColDominant::colDominantWithoutDiagonal_All()
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
            
            for (int j = l; j<networkSize; j++)
                expr_01 += a[j][k][l];
            
            setConstraint(expr_01, expr_02, CDWD , ALL, "colDominantWithoutDiagonal", k,l);

        }
    }
    setObjectiveFunction(expr_02);
}

void ColDominant::colDominantWithoutDiagonal_OffDiagonal()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;

    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                IloExpr expr_01(env);
                
                for (int j = l; j<networkSize; j++)
                    expr_01 += a[j][k][l];
                
                setConstraint(expr_01, expr_02, CDWD, OFF_DIAGONAL, "colDominantWithoutDiagonal", k,l);

            }
        }
    }
    setObjectiveFunction(expr_02);
}

void ColDominant::colDominantWithoutDiagonal_Diagonal()
{
    IloExpr expr_02(env);
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
   
        for (int j = k; j<networkSize; j++)
                expr_01 += a[j][k][k];
        
        setConstraint(expr_01, expr_02, CDWD, DIAGONAL, "colDominantWithoutDiagonal", k,k);

    }
    setObjectiveFunction(expr_02);
   
}

/*********************************************************/
/*Diagonal Zero*/
/*********************************************************/

void ColDominant::colDominantDiagonalZero()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(CDDZ);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        colDominantDiagonalZero_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        colDominantDiagonalZero_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        colDominantDiagonalZero_Diagonal();
    }
}


void ColDominant::colDominantDiagonalZero_All()
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
            
            for (int j = l; j<networkSize; j++)
            {
                expr_01 += a[j][k][l];
            }
            if (k==l)
                expr_01+= dsOne[k][0];
            
            setConstraint(expr_01, expr_02, CDDZ, ALL, "colDominantDiagonalZero", k,l);

        }
    }
    setObjectiveFunction(expr_02);
}

void ColDominant::colDominantDiagonalZero_OffDiagonal()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                IloExpr expr_01(env);
                
                for (int j = l; j<networkSize; j++)
                    expr_01 += a[j][k][l];
                
                setConstraint(expr_01, expr_02, CDDZ, OFF_DIAGONAL, "colDominantDiagonalZero", k,l);

            }
        }
    }
    setObjectiveFunction(expr_02);
}

void ColDominant::colDominantDiagonalZero_Diagonal()
{
    IloExpr expr_02(env);
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        

        for (int j = k; j<networkSize; j++)
            expr_01 += a[j][k][k];
        
        
        expr_01+= dsOne[k][0];
        
        setConstraint(expr_01, expr_02, CDDZ, DIAGONAL, "colDominantDiagonalZero", k,k);
    }
    setObjectiveFunction(expr_02);
    
}

/*********************************************************/
/*Diagonal One*/
/*********************************************************/

void ColDominant::colDominantDiagonalOne()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(CDDO);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        colDominantDiagonalOne_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        colDominantDiagonalOne_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        colDominantDiagonalOne_Diagonal();
    }
}

void ColDominant::colDominantDiagonalOne_All()
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
            
            for (int j = l; j<networkSize; j++)
                expr_01 += a[j][k][l];
            
             if (k==l)
                 expr_01+= dsZero[k][0];
            
            setConstraint(expr_01, expr_02, CDDO, ALL, "colDominantDiagonalOne", k,l);
        }
    }
    setObjectiveFunction(expr_02);
}

void ColDominant::colDominantDiagonalOne_OffDiagonal()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                IloExpr expr_01(env);
                
                for (int j = l; j<networkSize; j++)
                    expr_01 += a[j][k][l];
                
                setConstraint(expr_01, expr_02, CDDO, OFF_DIAGONAL, "colDominantDiagonalOne", k,l);
            }
        }
    }
    setObjectiveFunction(expr_02);
}

void ColDominant::colDominantDiagonalOne_Diagonal()
{
    IloExpr expr_02(env);
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        
        for (int j = k; j<networkSize; j++)
            expr_01 += a[j][k][k];
        
        expr_01+= dsZero[k][0];
        setConstraint(expr_01, expr_02, CDDO, DIAGONAL, "colDominantDiagonalOne", k,k);
    }
    setObjectiveFunction(expr_02);
}

void ColDominant::setConstraint(IloExpr expr_01, IloExpr expr_02, FunctionType type, FunctionRelease release, string ctrName, int k, int l)
{
//    if (itsSymmetricGraph && k!=l)
//    {
//        IloExpr expr_03(env);
//        
//        for (int i = k; i<networkSize; i++)
//            expr_03 += o[i][k][l];
//        
//        IloConstraint constraint = (f[get_fPosition(type)][l][k]  >=  expr_03 +  networkSize * (- 1 + w[get_fPosition(type)][l][k]));
//        string name = ctrName + SSTR(l) + SSTR(k);
//        constraint.setName(name.c_str());
//        model.add(constraint);
//        expr_02 += f[get_fPosition(type)][l][k];
//    }
    
    if (release != DIAGONAL )
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
