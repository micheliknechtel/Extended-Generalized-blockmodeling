//
//  RegularBlock.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 19/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "RegularBlock.hpp"

void RegularBlock::regularBlock()
{
    IloExpr expr_02(env);
    FunctionDetails fDetails = DataManager::getDataManager()->getfDetails(RB);
    
    addFunction(fDetails);
    
    int limit = clusterUpperBound-1;
    
    if (fDetails.release == ALL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit = k;
            
            for (int l = 0; l<=limit; l++)
            {
                IloExpr expr_01(env);
                
                for (int i = 0; i<networkSize; i++)
                {
                    expr_01 += colError[i][k][l] + rowError[i][k][l] ;
                }
                
                setConstraint("RegularBlock", RB, expr_01, expr_02, k, l);

            }
        }
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph)
                limit = k;
            
            for (int l = 0; l<=limit; l++)
            {
                if (k!=l)
                {
                    IloExpr expr_01(env);
                    for (int i = 0; i<networkSize; i++)
                    {
                        expr_01 += colError[i][k][l] + rowError[i][k][l];
                    }
                    
                    setConstraint("RegularBlock", RB, expr_01, expr_02, k, l);
                }
            }
        }
    }
    
    if (fDetails.release == DIAGONAL)
    {
        FunctionRelease releaseSharedVariable   = DataManager::getDataManager()->releaseRegularBlock;
        
        for (int k = 0; k<clusterUpperBound; k++)
        {
            IloExpr expr_01(env);
            
            if (releaseSharedVariable==DIAGONAL)
            {
                for (int i = 0; i<networkSize; i++)
                    expr_01 += colError[i][k][0] + rowError[i][k][0];
            }
            
            if (releaseSharedVariable!=DIAGONAL)
            {
                for (int i = 0; i<networkSize; i++)
                    expr_01 += colError[i][k][k] + rowError[i][k][k];
            }
            
            setConstraint("RegularBlock", RB, expr_01, expr_02, k, k);

        }
    }
    
    setObjectiveFunction(expr_02);
}


void RegularBlock::setConstraint(string ctrName, FunctionType type,   IloExpr expr_01,  IloExpr expr_02,  int k, int l )
{
    FunctionRelease releaseCurrentProperty  = DataManager::getDataManager()->getCurrentfDetails().release;
    //bool areThereNonSymmetricProperties     = DataManager::getDataManager()->areThereNonSymmetricPropertie();
    
    if (releaseCurrentProperty == DIAGONAL)
    {
        IloConstraint constraint = (f[get_fPosition(type)][k][0]  >=  expr_01 +  networkSize * (- 1 + w[get_fPosition(type)][k][0]));
        string name = ctrName + SSTR(k) + SSTR(k);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_02 += f[get_fPosition(type)][k][0];
    }
    
    if (releaseCurrentProperty!=DIAGONAL)
    {
        IloConstraint constraint = (f[get_fPosition(type)][k][l]  >=  expr_01 + networkSize * (- 1 + w[get_fPosition(type)][k][l]));
        string name = ctrName + SSTR(k) + SSTR(l);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_02 += f[get_fPosition(type)][k][l];
    }
    
//    if (itsSymmetricGraph && areThereNonSymmetricProperties  && k!=l )
//    {
//        IloConstraint constraint = (f[get_fPosition(type)][l][k]  >=  expr_01 +  networkSize * (- 1 + w[get_fPosition(type)][l][k]));
//        string name = ctrName + SSTR(l) + SSTR(k);
//        constraint.setName(name.c_str());
//        model.add(constraint);
//        expr_02 += f[get_fPosition(type)][l][k];
//    }
}
