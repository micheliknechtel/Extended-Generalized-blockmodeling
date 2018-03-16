//
//  ColumnFunctional.cpp
//  GBlockModeling - current
//
//  Created by Micheli  Knechtel on 12/08/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "ColumnFunctional.hpp"

void ColumnFunctional::columnFunctional()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(CF);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        colFunctional_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        colFunctional_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        colFunctional_Diagonal();
    }
}

void ColumnFunctional::colFunctional_All()
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
                expr_01 += omega[j][k][l];
            
            setConstraint("columnFunctional", CF, expr_01, expr_02, k, l);
        }
    }
    setObjectiveFunction(expr_02);
}

void ColumnFunctional::colFunctional_OffDiagonal()
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
                
                for (int j = l; j<networkSize; j++)
                    expr_01 += omega[j][k][l];
                
                setConstraint("columnFunctional", CF, expr_01, expr_02, k, l);
            }
        }
    }
    setObjectiveFunction(expr_02);
}

void ColumnFunctional::colFunctional_Diagonal()
{
    IloExpr expr_02(env);
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        
        if(DataManager::getDataManager()->getDataManager()->getBlockRelease(CF,RF) == DIAGONAL)
            for (int j = k; j<networkSize; j++)
                expr_01 += omega[j][k][0];
        else
            for (int j = k; j<networkSize; j++)
                expr_01 += omega[j][k][k];
        
        setConstraint("columnFunctional", CF, expr_01, expr_02, k, 0);
        
    }
    
    setObjectiveFunction(expr_02);
}

void ColumnFunctional::setConstraint(string ctrName, FunctionType type,   IloExpr expr_01,  IloExpr expr_02,  int k, int l )
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
    
//    if (itsSymmetricGraph && releaseCurrentProperty!=DIAGONAL)
//    {
//        IloExpr expr_03(env);
//        
//        for (int i = k; i<networkSize; i++)
//            expr_03 += alfa[i][k][l];
//        
//        IloConstraint constraint = (f[get_fPosition(type)][l][k]  >=  expr_03 +  networkSize * networkSize *(- 1 + w[get_fPosition(type)][l][k]));
//        string name = ctrName + SSTR(l) + SSTR(k);
//        constraint.setName(name.c_str());
//        model.add(constraint);
//        expr_02 += f[get_fPosition(type)][l][k];
//    }
    
}


void ColumnFunctional::modulusOmega()
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
                for (int j = l; j<networkSize; j++)
                {
                    IloExpr expr_01(env);
                    
                    for (int i = k; i<j; i++)
                    {
                        expr_01 +=  relationMatrix[i][j] * y[j][i][l][k];
                    }
                    
                    for (int i = max(j+1,k); i<networkSize; i++)
                    {
                        expr_01 += relationMatrix[i][j] * y[i][j][k][l];
                    }
                    
                    if (k==l)
                        expr_01 += relationMatrix[j][j] * x[j][l];
                    
                    IloConstraint constraint_01 = (omega[j][k][l] >= -1 + expr_01 - networkSize * (emptyCluster[l] + emptyCluster[k]) + networkSize * (x[j][l]-1));
                    string name = "omega_p_one" + SSTR(j) + SSTR(k) + SSTR(l);
                    constraint_01.setName(name.c_str());
                    model.add(constraint_01);
                    LOG(name);
                    
                    IloConstraint constraint_02 = (omega[j][k][l] >= 1 - expr_01 - networkSize * (emptyCluster[l]+emptyCluster[k]) + networkSize * (x[j][l]-1));
                    name = "omega_n_one" + SSTR(j) + SSTR(k) + SSTR(l);
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
            
            for (int j = k; j<networkSize; j++)
            {
                IloExpr expr_01(env);
                
                for (int i = k; i<j; i++)
                {
                    expr_01 +=  relationMatrix[i][j] * y[j][i][k][k];
                }
                
                for (int i = max(j+1,k); i<networkSize; i++)
                {
                    expr_01 += relationMatrix[i][j] * y[i][j][k][k];
                }
                
                expr_01 += relationMatrix[j][j] * x[j][k];
                
                if(DataManager::getDataManager()->getDataManager()->getBlockRelease(CF,RF) == DIAGONAL)
                {
                    IloConstraint constraint_01 = (omega[j][k][0] >= -1 + expr_01 - networkSize * (emptyCluster[k] + emptyCluster[k]) + networkSize * (x[j][k]-1));
                    string name = "omega_p_one" + SSTR(j) + SSTR(k) + SSTR(0);
                    constraint_01.setName(name.c_str());
                    model.add(constraint_01);
                    LOG(name);
                    
                    IloConstraint constraint_02 = (omega[j][k][0] >= 1 - expr_01 - networkSize * (emptyCluster[k]+emptyCluster[k]) + networkSize * (x[j][k]-1));
                    name = "omega_n_one" + SSTR(j) + SSTR(k) + SSTR(0);
                    constraint_02.setName(name.c_str());
                    model.add(constraint_02);
                    LOG(name);
                }
                else
                {
                    IloConstraint constraint_01 = (omega[j][k][k] >= -1 + expr_01 - networkSize * (emptyCluster[k] + emptyCluster[k]) + networkSize * (x[j][k]-1));
                    string name = "omega_p_one" + SSTR(j) + SSTR(k) + SSTR(k);
                    constraint_01.setName(name.c_str());
                    model.add(constraint_01);
                    LOG(name);
                    
                    IloConstraint constraint_02 = (omega[j][k][k] >= 1 - expr_01 - networkSize * (emptyCluster[k]+emptyCluster[k]) + networkSize * (x[j][k]-1));
                    name = "omega_n_one" + SSTR(j) + SSTR(k) + SSTR(k);
                    constraint_02.setName(name.c_str());
                    model.add(constraint_02);
                    LOG(name);
                    
                }
            }
        }
}
