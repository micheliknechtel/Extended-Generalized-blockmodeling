//
//  RowRegular.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 18/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "RowRegular.hpp"

void RowRegular::rowRegular()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(RRB);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        rowRegular_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        rowRegular_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        rowRegular_Diagonal();
    }
}


void RowRegular::rowRegular_All()
{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_01(env), expr_03(env);
            
            for (int i = k; i<networkSize; i++)
                expr_01 += rowError[i][k][l];
            
            if (itsSymmetricGraph && k!=l)
            {
                for (int i = k; i<networkSize; i++)
                {
                    expr_03 += colError[i][k][l];
                }
  
                expr_03+= networkSize * (- 1 + w[get_fPosition(RRB)][l][k]);
                
                IloConstraint constraint = (f[get_fPosition(RRB)][l][k]  >=  expr_03);
                string name = "rowRegular" + SSTR(l) + SSTR(k);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_02 += f[get_fPosition(RRB)][l][k];
            }
            
            expr_01+= networkSize * (- 1 + w[get_fPosition(RRB)][k][l]);
            IloConstraint constraint = (f[get_fPosition(RRB)][k][l]  >=  expr_01);
            string name = "rowRegular" + SSTR(k) + SSTR(l);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_02 += f[get_fPosition(RRB)][k][l];
        }
    }
    
    setObjectiveFunction(expr_02);
}




void RowRegular::rowRegular_OffDiagonal()
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
                IloExpr expr_01(env), expr_03(env);
                
                for (int i = k; i<networkSize; i++)
                {
                    expr_01 += rowError[i][k][l];
                }
                
                if (itsSymmetricGraph && k!=l)
                {
                    for (int i = k; i<networkSize; i++)
                    {
                        expr_03 += colError[i][k][l];
                    }
                    
                    expr_03+= networkSize * (- 1 + w[get_fPosition(RRB)][l][k]);
                    
                    IloConstraint constraint = (f[get_fPosition(RRB)][l][k]  >=  expr_03);
                    string name = "rowRegular" + SSTR(l) + SSTR(k);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                    expr_02 += f[get_fPosition(RRB)][l][k];
                }
                
                
                expr_01 +=  networkSize * (- 1 + w[get_fPosition(RRB)][k][l]);
                
                IloConstraint constraint = (f[get_fPosition(RRB)][k][l]  >=  expr_01);
                string name = "rowRegular" + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_02 += f[get_fPosition(RRB)][k][l];
            }
        }
    }
    setObjectiveFunction(expr_02);
}


void RowRegular::rowRegular_Diagonal()
{
    IloExpr expr_02(env);
    FunctionRelease releaseSharedVariable   = DataManager::getDataManager()->releaseRegularBlock;

    for (int k = 0; k<clusterUpperBound; k++)
    {
        
        IloExpr expr_01(env);
       
        if (releaseSharedVariable==DIAGONAL)
        {
            for (int i = k; i<networkSize; i++)
                expr_01 += rowError[i][k][0];
        }
        
        if (releaseSharedVariable!=DIAGONAL)
        {
            for (int i = k; i<networkSize; i++)
                expr_01 += rowError[i][k][k];
        }
        
        IloConstraint constraint = (f[get_fPosition(RRB)][k][0]  >=  expr_01 + networkSize * (- 1 + w[get_fPosition(RRB)][k][0]));
        string name = "rowRegular" + SSTR(k) + SSTR(k);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_02 += f[get_fPosition(RRB)][k][0];
        

       
    }
    setObjectiveFunction(expr_02);
}
