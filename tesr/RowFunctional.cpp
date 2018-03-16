//
//  RowFunctional.cpp
//  GBlockModeling - current
//
//  Created by Micheli  Knechtel on 13/08/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "RowFunctional.hpp"

void RowFunctional::rowFunctional()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(RF);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        rowFunctional_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        rowFunctional_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        rowFunctional_Diagonal();
    }
}

void RowFunctional::rowFunctional_All()
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
            
            for (int j = k; j<networkSize; j++)
                expr_01 += alfa[j][k][l];
            
            setConstraint("rowFunctional", RF, expr_01, expr_02, k, l);
        }
    }
    setObjectiveFunction(expr_02);
}

void RowFunctional::rowFunctional_OffDiagonal()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if(k!=l)
            {
                IloExpr expr_01(env);
                
                for (int j = k; j<networkSize; j++)
                    expr_01 += alfa[j][k][l];
                
                setConstraint("rowFunctional", RF, expr_01, expr_02, k, l);
            }
        }
    }
    setObjectiveFunction(expr_02);
}

void RowFunctional::rowFunctional_Diagonal()
{
    IloExpr expr_02(env);
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        if(DataManager::getDataManager()->getDataManager()->getBlockRelease(CF,RF) == DIAGONAL)
            for (int j = k; j<networkSize; j++)
                expr_01 += alfa[j][k][0];
        else
            for (int j = k; j<networkSize; j++)
                expr_01 += alfa[j][k][k];
        setConstraint("rowFunctional", RF, expr_01, expr_02, k, 0);
        
    }
    setObjectiveFunction(expr_02);
    
}

void RowFunctional::setConstraint(string ctrName, FunctionType type,   IloExpr expr_01,  IloExpr expr_02,  int k, int l )
{
    FunctionRelease releaseCurrentProperty  = DataManager::getDataManager()->getCurrentfDetails().release;
    
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
    
//    if (itsSymmetricGraph && k!=l && releaseCurrentProperty!=DIAGONAL)
//    {
//        IloExpr expr_03(env);
//        
//        for (int j = l; j<networkSize; j++)
//            expr_03 += omega[j][k][l];
//        
//        IloConstraint constraint = (f[get_fPosition(type)][l][k]  >=  expr_03 +  networkSize  * networkSize *  (- 1 + w[get_fPosition(type)][l][k]));
//        string name = ctrName + SSTR(l) + SSTR(k);
//        constraint.setName(name.c_str());
//        model.add(constraint);
//        expr_02 += f[get_fPosition(type)][l][k];
//    }
    
}

void RowFunctional::modulusAlfa()
{
    int limit = clusterUpperBound-1;
    
    FunctionRelease releaseCurrentProperty  = DataManager::getDataManager()->getCurrentfDetails().release;
    
    if (releaseCurrentProperty!=DIAGONAL)
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit = k;
            
            for (int l = 0; l<=limit; l++)
            {
                for (int i = k; i<networkSize; i++)
                {
                    IloExpr expr_01(env);
                    
                    for (int j = l; j<i; j++)
                    {
                        expr_01 += relationMatrix[i][j] * y[i][j][k][l];
                    }
                    
                    for (int j = max(i+1,l); j<networkSize; j++)
                    {
                        expr_01 += relationMatrix[i][j] * y[j][i][l][k];
                    }
                    if (k==l)
                        expr_01 += relationMatrix[i][i] * x[i][k];
                    
                    IloConstraint constraint_01 = (alfa[i][k][l] >= -1 + expr_01  - networkSize * (emptyCluster[l] + emptyCluster[k]) + networkSize * (x[i][k]-1));
                    string name = "alfa_p_one" + SSTR(i) + SSTR(k) + SSTR(l);
                    constraint_01.setName(name.c_str());
                    model.add(constraint_01);
                    LOG(name);
                    
                    IloConstraint constraint_02 = (alfa[i][k][l] >= 1 - expr_01  - networkSize * (emptyCluster[l] + emptyCluster[k])  + networkSize * (x[i][k]-1));
                    name = "alfa_n_one" + SSTR(i) + SSTR(k) + SSTR(l);
                    constraint_02.setName(name.c_str());
                    model.add(constraint_02);
                    LOG(name);
                }
            }
        }
    else
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit = k;
            for (int i = k; i<networkSize; i++)
            {
                IloExpr expr_01(env);
                
                
                for (int j = k; j<i; j++)
                {
                    expr_01 += relationMatrix[i][j] * y[i][j][k][k];
                }
                
                for (int j = max(i+1,k); j<networkSize; j++)
                {
                    expr_01 += relationMatrix[i][j] * y[j][i][k][k];
                }
                
                expr_01 += relationMatrix[i][i] * x[i][k];
                
                if(DataManager::getDataManager()->getDataManager()->getBlockRelease(CF,RF) == DIAGONAL)
                {
                    
                    IloConstraint constraint_01 = (alfa[i][k][0] >= -1 + expr_01  - networkSize * (emptyCluster[k] + emptyCluster[k]) + networkSize * (x[i][k]-1));
                    string name = "alfa_p_one" + SSTR(i) + SSTR(k) + SSTR(k);
                    constraint_01.setName(name.c_str());
                    model.add(constraint_01);
                    LOG(name);
                    
                    IloConstraint constraint_02 = (alfa[i][k][0] >= 1 - expr_01  - networkSize * (emptyCluster[k] + emptyCluster[k])  + networkSize * (x[i][k]-1));
                    name = "alfa_n_one" + SSTR(i) + SSTR(k) + SSTR(k);
                    constraint_02.setName(name.c_str());
                    model.add(constraint_02);
                    LOG(name);
                }
                else
                {
                    
                    IloConstraint constraint_01 = (alfa[i][k][k] >= -1 + expr_01  - networkSize * (emptyCluster[k] + emptyCluster[k]) + networkSize * (x[i][k]-1));
                    string name = "alfa_p_one" + SSTR(i) + SSTR(k) + SSTR(k);
                    constraint_01.setName(name.c_str());
                    model.add(constraint_01);
                    LOG(name);
                    
                    IloConstraint constraint_02 = (alfa[i][k][k] >= 1 - expr_01  - networkSize * (emptyCluster[k] + emptyCluster[k])  + networkSize * (x[i][k]-1));
                    name = "alfa_n_one" + SSTR(i) + SSTR(k) + SSTR(k);
                    constraint_02.setName(name.c_str());
                    model.add(constraint_02);
                    LOG(name);
                }
            }
        }
}
