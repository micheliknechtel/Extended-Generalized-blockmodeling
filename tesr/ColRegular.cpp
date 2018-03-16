
//
//  ColRegular.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 19/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "ColRegular.hpp"

void ColRegular::colRegular()
{
    
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(CRB);
    addFunction(fDetails);
    
    if (fDetails.release == ALL)
    {
        colRegularAll();
    }
    if (fDetails.release == OFF_DIAGONAL)
    {
        colRegularOffDiagonal();
    }
    if (fDetails.release == DIAGONAL)
    {
        colRegularDiagonal();
    }
    
}


void ColRegular::colRegularAll()
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
            
            for (int j = l; j<networkSize; j++)
                expr_01 += colError[j][k][l];
          
            
            if (itsSymmetricGraph)
            {
                for (int i = k; i<networkSize; i++)
                {
                    expr_03 += rowError[i][k][l];
                }
                
                expr_03+= networkSize * (- 1 + w[get_fPosition(CRB)][l][k]);
                
                IloConstraint constraint = (f[get_fPosition(CRB)][l][k]  >=  expr_03);
                string name = "colRegular" + SSTR(l) + SSTR(k);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_02 += f[get_fPosition(CRB)][l][k];
            }

            expr_01 += networkSize * (- 1 + w[get_fPosition(CRB)][k][l]);
            IloConstraint constraint = (f[get_fPosition(CRB)][k][l]  >=  expr_01);
            string name = "colRegular" + SSTR(k) + SSTR(l);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_02 += f[get_fPosition(CRB)][k][l];
        }
    }
    setObjectiveFunction(expr_02);
}

void ColRegular::colRegularOffDiagonal()
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
                    expr_01 += colError[i][k][l];
                }
                if (itsSymmetricGraph)
                {
                    for (int i = k; i<networkSize; i++)
                    {
                        expr_03 += rowError[i][k][l];
                    }
                    
                    expr_03+= networkSize * (- 1 + w[get_fPosition(CRB)][l][k]);
                   
                    IloConstraint constraint = (f[get_fPosition(CRB)][l][k]  >=  expr_03);
                    string name = "colRegular" + SSTR(l) + SSTR(k);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                    expr_02 += f[get_fPosition(CRB)][l][k];
                }

                expr_01+= networkSize * (- 1 + w[get_fPosition(CRB)][k][l]);
                
                IloConstraint constraint = (f[get_fPosition(CRB)][k][l]  >=  expr_01);
                string name = "colRegular" + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_02 += f[get_fPosition(CRB)][k][l];
                
            }
        }
    }
    setObjectiveFunction(expr_02);

}

void ColRegular::colRegularDiagonal()
{
    IloExpr expr_02(env);
    FunctionRelease releaseSharedVariable   = DataManager::getDataManager()->releaseRegularBlock;

    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        if (releaseSharedVariable==DIAGONAL)
        {
            for (int i = k; i<networkSize; i++)
                expr_01 += colError[i][k][0] ;
        }
        if (releaseSharedVariable!=DIAGONAL)
        {
            for (int i = k; i<networkSize; i++)
                expr_01 += colError[i][k][k];
        }

        IloConstraint constraint = (f[get_fPosition(CRB)][k][0]  >=  expr_01 + networkSize * (- 1 + w[get_fPosition(CRB)][k][0]));
        string name = "colRegular" + SSTR(k) + SSTR(k);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_02 += f[get_fPosition(CRB)][k][0];
    }
    setObjectiveFunction(expr_02);

}
