//
//  LinearConstraint.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 29/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "LinearConstraint.hpp"

void LinearConstraint::linearizing() //OK OK
{
    xik_plus_xjl_plus_yijkl_equals_one();
    y_smaller_xik();
    y_smaller_xjl();
    
    if(DataManager::getDataManager()->getAdditionalConstraint())
        quadraticAssignmentProblem();
}

/*********************************************************/
/*Quadratic Assignment Problem */
/*********************************************************/
void LinearConstraint::quadraticAssignmentProblem() //OK OK
{
    int limit= 0;
    
    for (int l = 0; l<clusterUpperBound; l++)
    {
        for (int i = 0; i<networkSize; i++)
        {
            for (int j = l; j<i; j++)
            {
                IloExpr expr_01(env);
                
                for(int k = 0; k<=min(i, clusterUpperBound-1); k++)
                {
                    expr_01 += y[i][j][k][l];
                }
                
                IloConstraint constraint = (expr_01 == x[j][l]);
                string name = "quadraticAssignmentProblem" +  SSTR(i) + SSTR(j) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                LOG(name);
                expr_01.end();
            }
            
            if (l>i)   limit = l;
            if (l<=i)  limit = i+1;
            
            
            for (int j = limit; j<networkSize; j++)
            {
                IloExpr expr_01(env);
                
                for(int k = 0; k<=min(i, clusterUpperBound-1); k++)
                {
                    expr_01 += y[j][i][l][k];
                }
                
                IloConstraint constraint = (expr_01 == x[j][l]);
                string name = "quadraticAssignmentProblem" +  SSTR(i) + SSTR(j) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                LOG(name);
                expr_01.end();
            }
        }
    }
}


/*********************************************************/
/*linearizing y */
/*********************************************************/

void LinearConstraint::xik_plus_xjl_plus_yijkl_equals_one()
{
    for (int i = 0; i<networkSize; i++)
    {
        for (int j = 0; j<i; j++)
        {
            for (int k = 0; k<= min(i, clusterUpperBound-1); k++)
            {
                for (int l = 0; l<=min(j, clusterUpperBound-1); l++)
                {
                    IloExpr expr_01(env);
                    string name = "_y" + SSTR(i) + SSTR(j) + SSTR(k) + SSTR(l);
                    
                    expr_01 = x[i][k] + x[j][l] - y[i][j][k][l];
                    
                    IloRange constraint_01 (env, expr_01, 1);
                    constraint_01.setName(name.c_str());
                    expr_01.end();
                    
                    model.add(constraint_01);
                    
                    LOG(name);
                }
            }
        }
    }
}

void LinearConstraint::y_smaller_xik()
{
    int limit = clusterUpperBound-1;
    
    
    for (int i = 0; i<networkSize; i++)
    {
        for (int j = 0; j<i; j++)
        {
            for (int k = 0; k<=min(i, clusterUpperBound-1); k++)
            {
                
                for (int l = 0; l<=min(j, limit); l++)
                {
                    IloExpr expr_02(env);
                    string name =  "y" + SSTR(i) + SSTR(j) + SSTR(k) + SSTR(l) + "_sOe_" + "x" + SSTR(i) + SSTR(k);
                    IloConstraint constraint_02 = (y[i][j][k][l]<= x[i][k] );
                    constraint_02.setName(name.c_str());
                    expr_02.end();
                    model.add(constraint_02);
                    LOG(name);
                }
            }
        }
    }
}

void LinearConstraint::y_smaller_xjl()
{
    for (int i = 0; i<networkSize; i++)
    {
        for (int j = 0; j<i; j++)
        {
            for (int k = 0; k<= min(i, clusterUpperBound-1); k++)
            {
                for (int l = 0; l<= min(j, clusterUpperBound-1); l++)
                {
                    string name_01 =  "y" + SSTR(i) + SSTR(j) + SSTR(k) + SSTR(l) + "_sOe_" + "x" + SSTR(j) + SSTR(l);
                    string name_02 =  "y" + SSTR(i) + SSTR(j) + SSTR(k) + SSTR(l) + "_sOe_" + "x" + SSTR(i) + SSTR(k);
                    
                    IloConstraint constraint_01 = (y[i][j][k][l]<= x[j][l] );
                    IloConstraint constraint_02 = (y[i][j][k][l]<= x[i][k] );
                    constraint_01.setName(name_01.c_str());
                    constraint_02.setName(name_02.c_str());
                    model.add(constraint_01);
                    model.add(constraint_02);
                    LOG(name_01);
                    LOG(name_02);
                }
            }
        }
    }
}

/*********************************************************/
/*w_sum*/
/*********************************************************/

void LinearConstraint::w_sum() //OK OK
{
    int limit = clusterUpperBound-1;
    
    bool flag = false;
    
    IloExpr expr_01(env);

    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        expr_01 += 1-emptyCluster[k];
        
        
        if(itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_02(env);
            
            for (int i = 0; i<fPSize; i++)
            {
                FunctionRelease release = DataManager::getDataManager()->functionMapping[i].release;
                
                if(release == ALL)
                {
                    expr_02 += w[i][k][l];
                    flag = true;
                }
                else if(release == DIAGONAL)
                {
                    if(k==l)
                    {
                        expr_02 += w[i][k][0];
                        flag = true;
                    }
                }
                else if(release == OFF_DIAGONAL)
                {
                    if(k!=l)
                    {
                        expr_02 += w[i][k][l];
                        flag = true;
                    }
                }
            }
            if (flag)
            {
                string name = "w_sum" +  SSTR(k) + SSTR(l);
                IloRange constraint(env,1,expr_02, 1);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_02.end();
                flag = false;
            }
        }
    }
    
    model.add(IloRange(env, clusterLowerBound,expr_01));
}

/*********************************************************/
/*z_smaller_x*/
/*********************************************************/
void LinearConstraint::z_smaller_x()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        z_smaller_x_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        z_smaller_x_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        z_smaller_x_Diagonal();
    }
}

void LinearConstraint::z_smaller_x_All()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int i = k; i<networkSize; i++)
            {
                IloConstraint constraint = (z[i][k][l]  <= emptyCluster[k] + x[i][k]);
                string name = "z_smaller_x" + SSTR(i)+ SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
            }
        }
    }
}

void LinearConstraint::z_smaller_x_OffDiagonal()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                for (int i = k; i<networkSize; i++)
                {
                    IloConstraint constraint = (z[i][k][l] <= emptyCluster[k] + x[i][k]);
                    string name = "z_smaller_x"+ SSTRL(i)+ SSTRL(k) + SSTRL(l);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                }
            }
        }
    }
}

void LinearConstraint::z_smaller_x_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int i = k; i<networkSize; i++)
        {
            IloConstraint constraint = (z[i][k][k] <=  emptyCluster[k] + x[i][k]);
            string name = "z_smaller_x"+ SSTRL(i)+ SSTRL(k) + SSTRL(k);
            constraint.setName(name.c_str());
            model.add(constraint);
        }
    }
}

/*********************************************************/
/*z_sum*/
/*********************************************************/

void LinearConstraint::z_sum()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        z_sum_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        z_sum_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        z_sum_Diagonal();
    }
}

void LinearConstraint::z_sum_All()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_01(env);
            
            for (int i = k; i<networkSize; i++)
            {
                expr_01 += z[i][k][l];
            }
            IloConstraint constraint = (expr_01 == 1-emptyCluster[k]);
            string name = "z_sum" + SSTR(k) + SSTR(l);
            constraint.setName(name.c_str());
            model.add(constraint);
        }
    }
}

void LinearConstraint::z_sum_OffDiagonal()
{
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
                for (int i = k; i<networkSize; i++)
                {
                    expr_01 += z[i][k][l];
                }
                
                IloConstraint constraint = (expr_01 == 1-emptyCluster[k]);
                string name = "z_sum" + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
            }
        }
    }
}

void LinearConstraint::z_sum_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        for (int i = k; i<networkSize; i++)
        {
            expr_01 += z[i][k][k];
        }
        IloConstraint constraint = (expr_01 == 1-emptyCluster[k]);
        string name = "z_sum" + SSTR(k) + SSTR(k);
        constraint.setName(name.c_str());
        model.add(constraint);
    }
}

/*********************************************************/
/*o_bigger_lineError_plus_bigM*/
/*********************************************************/

void LinearConstraint::o_bigger_lineError_plus_bigM()
{
    
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        o_bigger_lineError_plus_bigM_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        o_bigger_lineError_plus_bigM_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        o_bigger_lineError_plus_bigM_Diagonal();
    }
}

void LinearConstraint::o_bigger_lineError_plus_bigM_All()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int i = k; i<networkSize; i++)
            {
                IloExpr expr_01(env);
                
                expr_01 = lineError[i][k][l] + networkSize * (z[i][k][l]-1);
                
                IloConstraint constraint = (o[i][k][l] >= expr_01);
                string name = "o_bigger_lineError" + SSTR(i) + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                
            }
        }
    }
}

void LinearConstraint::o_bigger_lineError_plus_bigM_OffDiagonal()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                for (int i = 0; i<networkSize; i++)
                {
                    IloExpr expr_01(env);
                    expr_01 = lineError[i][k][l] + networkSize * (z[i][k][l]-1);
                    
                    IloConstraint constraint = (o[i][k][l] >= expr_01);
                    string name = "o_bigger_lineError" + SSTRL(i) + SSTRL(k) + SSTRL(l);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                }
            }
        }
    }
}

void LinearConstraint::o_bigger_lineError_plus_bigM_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int i = 0; i<networkSize; i++)
        {
            IloExpr expr_01(env);
            expr_01 = lineError[i][k][k] + networkSize * (z[i][k][k]-1);
            
            IloConstraint constraint = (o[i][k][k] >= expr_01);
            string name = "o_bigger_lineError" + SSTRL(i) + SSTRL(k) + SSTRL(k);
            constraint.setName(name.c_str());
            model.add(constraint);
            
        }
    }
}

/*********************************************************/
/*o_smaller_lineError*/
/*********************************************************/

void LinearConstraint::o_smaller_lineError()
{
    
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        o_smaller_Error_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        o_smaller_Error_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        o_smaller_Error_Diagonal();
    }
}

void LinearConstraint::o_smaller_Error_All()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int i = k; i<networkSize; i++)
            {
                IloConstraint constraint = (o[i][k][l] <= lineError[i][k][l]);
                string name = "o_smaller_lineError" + SSTR(i) + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
            }
        }
    }
}

void LinearConstraint::o_smaller_Error_OffDiagonal()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                for (int i = k; i<networkSize; i++)
                {
                    IloConstraint constraint = (o[i][k][l] <= lineError[i][k][l]);
                    string name = "o_smaller_lineError" + SSTRL(i) + SSTRL(k) + SSTRL(l);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                }
                
            }
        }
    }
}

void LinearConstraint::o_smaller_Error_Diagonal()
{
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int i = k; i<networkSize; i++)
        {
            IloConstraint constraint = (o[i][k][k] <= lineError[i][k][k]);

            string name = "o_smaller_lineError" + SSTRL(i) + SSTRL(k) + SSTRL(k);
            constraint.setName(name.c_str());
            model.add(constraint);
        }
    }
}

/*********************************************************/
/*h_bigger_o*/
/*********************************************************/

void LinearConstraint::h_bigger_o()
{
    
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        //        h_bigger_o_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        //        h_bigger_o_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        //        h_bigger_o_Diagonal();
    }
}

void LinearConstraint::h_bigger_o_All()
{
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l<clusterUpperBound; l++)
        {
            IloExpr expr_01(env);
            for (int i = k; i<networkSize; i++)
            {
                expr_01 += o[i][k][l];
            }
            IloConstraint constraint = (h[k][l] >= expr_01);
            string name = "h_bigger_o" + SSTRL(k) + SSTRL(k);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
        }
    }
}

void LinearConstraint::h_bigger_o_OffDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l<clusterUpperBound; l++)
        {
            if (k!=l)
            {
                IloExpr expr_01(env);
                for (int i = k; i<networkSize; i++)
                {
                    expr_01 += o[i][k][l];
                }
                IloConstraint constraint = (h[k][l] >= expr_01);
                string name = "h_bigger_o" + SSTRL(k) + SSTRL(k);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_01.end();
            }
        }
    }
}

void LinearConstraint::h_bigger_o_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        for (int i = k; i<networkSize; i++)
        {
            expr_01 += o[i][k][0];
        }
        
        IloConstraint constraint = (h[k][0] >= expr_01);
        string name = "h_bigger_o" + SSTRL(k) + SSTRL(k);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_01.end();
    }
}

/*********************************************************/
/*h_smaller_lineErrors*/
/*********************************************************/

void LinearConstraint::h_smaller_lineError()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        //        h_smaller_lineErrorAll();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        //        h_smaller_lineErrorOffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        //        h_smaller_lineErrorDiagonal();
    }
}

void LinearConstraint::h_smaller_lineErrorAll()
{
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l<clusterUpperBound; l++)
        {
            IloExpr expr_01(env);
            for (int i = k; i<networkSize; i++)
            {
                expr_01 += lineError[i][k][l] + networkSize * (1-x[i][k]);
            }
            
            IloConstraint constraint = (h[k][l] <= expr_01);
            string name = "h_smaller_lineError" + SSTRL(k) + SSTRL(l);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
        }
    }
}

void LinearConstraint::h_smaller_lineErrorOffDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l<clusterUpperBound; l++)
        {
            if (k!=l)
            {
                IloExpr expr_01(env);
                
                for (int i = k; i<networkSize; i++)
                {
                    expr_01 += lineError[i][k][l] + networkSize * networkSize * (1-x[i][k]);
                }
                
                IloConstraint constraint = (h[k][l] <= expr_01);
                string name = "h_smaller_lineError" + SSTRL(k) + SSTRL(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_01.end();
            }
        }
    }
}

void LinearConstraint::h_smaller_lineErrorDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        
        for (int i = k; i<networkSize; i++)
            expr_01 += lineError[i][k][k] + networkSize * networkSize * (1-x[i][k]);
        
        IloConstraint constraint;
        FunctionRelease releaseSharedVariable   = DataManager::getDataManager()->releaseNullBlock;
        
        if (releaseSharedVariable!=DIAGONAL)
            constraint = (h[k][0] <= expr_01);
        
        if (releaseSharedVariable==DIAGONAL)
         constraint = (h[k][k] <= expr_01);
        
        string name = "h_smaller_lineError" + SSTRL(k) + SSTRL(k);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_01.end();
    }
}


/*********************************************************/
/*o_smaller_z*/
/*********************************************************/

void LinearConstraint::o_smaller_z()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        o_smaller_NzAll();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        o_smaller_NzOffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        o_smaller_NzDiagonal();
    }
}

void LinearConstraint::o_smaller_NzAll()
{
    int limit = clusterUpperBound-1;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int i = k; i<networkSize; i++)
            {
                add_o_smaller_Nz(k,l,i);
            }
        }
    }
}

void LinearConstraint::o_smaller_NzOffDiagonal()
{
    int limit = 0;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<limit; l++)
        {
            if (k!=l)
            {
                
                for (int i = limit; i<networkSize; i++)
                {
                    add_o_smaller_Nz(k,l,i);
                }
            }
        }
    }
}

void LinearConstraint::o_smaller_NzDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int i = k; i<networkSize; i++)
        {
            add_o_smaller_Nz(k,0,i);
        }
    }
}

void LinearConstraint::add_o_smaller_Nz(int k, int l, int i)
{
    
    IloExpr expr_01(env);
    expr_01 = networkSize  * z[i][k][l];
    IloConstraint constraint = (o[i][k][l] <= expr_01);
    string name = "o_smaller_z" + SSTR(i)+ SSTR(k) + SSTR(l);
    constraint.setName(name.c_str());
    model.add(constraint);
    expr_01.end();
    
}

/*********************************************************/
/*b_sum*/
/*********************************************************/

void LinearConstraint::b_sum()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        b_sum_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        b_sum_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        b_sum_Diagonal();
    }
}

void LinearConstraint::b_sum_All()
{
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
                expr_01 += b[j][k][l];
            }
            IloConstraint constraint = (expr_01 == 1-emptyCluster[k]);
            string name = "b_sum" + SSTR(k) + SSTR(l);
            constraint.setName(name.c_str());
            model.add(constraint);
        }
    }
}

void LinearConstraint::b_sum_OffDiagonal()
{
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
                {
                    expr_01 += b[j][k][l];
                }
                IloConstraint constraint = (expr_01 == 1-emptyCluster[k]);
                string name = "b_sum" + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                
            }
        }
    }
}

void LinearConstraint::b_sum_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        
        for (int j = k; j<networkSize; j++)
        {
            expr_01 += b[j][k][k];
        }
        IloConstraint constraint = (expr_01 == 1-emptyCluster[k]);
        string name = "b_sum" + SSTR(k) + SSTR(k);
        constraint.setName(name.c_str());
        model.add(constraint);
    }
}

/*********************************************************/
/*b_smaller_x*/
/*********************************************************/
void LinearConstraint::b_smaller_x()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        b_smaller_x_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        b_smaller_x_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        b_smaller_x_Diagonal();
    }
}

void LinearConstraint::b_smaller_x_All()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int j = l; j<networkSize; j++)
            {
                //Essa alteraçao foi eu quem inseriu :-D
                IloConstraint constraint = (b[j][k][l] <= emptyCluster[l] + x[j][l]);
                string name = "b_smaller_x" + SSTR(j)+ SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
            }
        }
    }
}

void LinearConstraint::b_smaller_x_OffDiagonal()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                for (int j = l; j<networkSize; j++)
                {
                    IloConstraint constraint = (b[j][k][l] <= emptyCluster[l] + x[j][l]);
                    string name = "b_smaller_x" + SSTR(j)+ SSTR(k) + SSTR(l);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                }
                
            }
        }
    }
}

void LinearConstraint::b_smaller_x_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int j = k; j<networkSize; j++)
        {
            IloConstraint constraint = (b[j][k][k] <= emptyCluster[k] + x[j][k]);
            string name = "b_smaller_x" + SSTR(j)+ SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
        }
    }
}

/*********************************************************/
/*a_bigger_columnError_plus_bigM*/
/*********************************************************/

void LinearConstraint::a_bigger_columnError_plus_bigM()
{
    
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        a_bigger_columnError_plus_bigM_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        a_bigger_columnError_plus_bigM_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        a_bigger_columnError_plus_bigM_Diagonal();
    }
}

void LinearConstraint::a_bigger_columnError_plus_bigM_All()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int j = l; j<networkSize; j++)
            {
                IloExpr expr_01(env);
                
                expr_01 = columnError[j][k][l] + networkSize * (b[j][k][l]-1);
                
                IloConstraint constraint = (a[j][k][l] >= expr_01);
                string name = "a_bigger_columnError" + SSTR(j) + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
            }
        }
    }
}

void LinearConstraint::a_bigger_columnError_plus_bigM_OffDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        int limit = clusterUpperBound-1;
        
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                for (int j = l; j<networkSize; j++)
                {
                    IloExpr expr_01(env);
                    
                    expr_01 = columnError[j][k][l] + networkSize * (b[j][k][l]-1);
                    
                    IloConstraint constraint = (a[j][k][l] >= expr_01);
                    string name = "a_bigger_columnError" + SSTR(j) + SSTR(k) + SSTR(l);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                }
                
            }
        }
    }
}

void LinearConstraint::a_bigger_columnError_plus_bigM_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int j = 0; j<networkSize; j++)
        {
            IloExpr expr_01(env);
            
            expr_01 = columnError[j][k][k] + networkSize * (b[j][k][k]-1);
            IloConstraint constraint = (a[j][k][k] >= expr_01);
            string name = "a_bigger_columnError" + SSTR(j) + SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
        }
    }
}
/*********************************************************/
/*a_smaller_columnError*/
/*********************************************************/

void LinearConstraint::a_smaller_columnError()
{
    
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        a_smaller_Error_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        a_smaller_Error_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        a_smaller_Error_Diagonal();
    }
}

void LinearConstraint::a_smaller_Error_All()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int j = l; j<networkSize; j++)
            {
                IloConstraint constraint = (a[j][k][l] <= columnError[j][k][l]);
                string name = "a_smaller_columnError" + SSTR(j) + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
            }
        }
    }
}

void LinearConstraint::a_smaller_Error_OffDiagonal()
{
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                for (int j = l; j<networkSize; j++)
                {
                    IloConstraint constraint = (a[j][k][l] <= columnError[j][k][l]);
                    string name = "a_smaller_columnError" + SSTR(j) + SSTR(k) + SSTR(l);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                }
            }
        }
    }
}

void LinearConstraint::a_smaller_Error_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int j = 0; j<networkSize; j++)
        {
            IloConstraint constraint = (a[j][k][k] <= columnError[j][k][k]);
            string name = "a_smaller_columnError" + SSTR(j) + SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
        }
    }
}

/*********************************************************/
/*a_smaller_b*/
/*********************************************************/

void LinearConstraint::a_smaller_b()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        a_smaller_NzAll();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        a_smaller_NzOffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        a_smaller_NzDiagonal();
    }
}

void LinearConstraint::a_smaller_NzAll()
{
    int limit = clusterUpperBound-1;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int j = l; j<networkSize; j++)
            {
                add_a_smaller_Nz(k,l,j);
            }
        }
    }
}

void LinearConstraint::a_smaller_NzOffDiagonal()
{
    int limit = clusterUpperBound-1;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (k!=l)
            {
                for (int j = l; j<networkSize; j++)
                {
                    add_a_smaller_Nz(k,l,j);
                }
            }
            
        }
    }
}

void LinearConstraint::a_smaller_NzDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int j = k; j<networkSize; j++)
        {
            add_a_smaller_Nz(k,0,j);
        }
    }
}

void LinearConstraint::add_a_smaller_Nz(int k, int l, int i)
{
    
    IloExpr expr_01(env);
    expr_01 = networkSize * networkSize * b[i][k][l];
    IloConstraint constraint = (a[i][k][l] <= expr_01);
    string name = "a_smaller_b" + SSTR(k) + SSTR(l);
    constraint.setName(name.c_str());
    model.add(constraint);
    expr_01.end();
    
}

/*********************************************************/
/*c_smaller_lineErrors*/
/*********************************************************/

void LinearConstraint::c_smaller_columnError()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
//        c_smaller_columnError_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
//        c_smaller_columnError_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
//        c_smaller_columnError_Diagonal();
    }
}

void LinearConstraint::c_smaller_columnError_All()
{
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
                expr_01 += columnError[j][k][l] + networkSize * networkSize * (1-x[j][l]);
            }
            
            IloConstraint constraint = (c[k][l] <= expr_01);
            string name = "c_smaller_columnError" + SSTR(k) + SSTR(l);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
        }
    }
}

void LinearConstraint::c_smaller_columnError_OffDiagonal()
{
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
                {
                    expr_01 += columnError[j][k][l] + networkSize * networkSize * (1-x[j][l]);
                }
                
                IloConstraint constraint = (c[k][l] <= expr_01);
                string name = "c_smaller_columnError" + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_01.end();
                
            }
        }
    }
}

void LinearConstraint::c_smaller_columnError_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        
        for (int j = k; j<networkSize; j++)
            expr_01 += columnError[j][k][k] + networkSize * networkSize * (1-x[j][k]);
        
        IloConstraint constraint;
        
        FunctionRelease releaseSharedVariable   = DataManager::getDataManager()->releaseNullBlock;
        
        if (releaseSharedVariable==DIAGONAL)
            constraint = (c[k][0] <= expr_01);
        
        if (releaseSharedVariable!=DIAGONAL)
            constraint = (c[k][k] <= expr_01);
        
        string name = "c_smaller_columnError" + SSTR(k) + SSTR(k);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_01.end();
    }
}

/*********************************************************/
/*c_bigger_a*/
/*********************************************************/

void LinearConstraint::c_bigger_a()
{
    
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
//        c_bigger_a_All();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
//        c_bigger_a_OffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
//        c_bigger_a_Diagonal();
    }
}

void LinearConstraint::c_bigger_a_All()
{
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
            IloConstraint constraint = (c[k][l] >= expr_01);
            string name = "c_bigger_a" + SSTR(k) + SSTR(l);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
        }
    }
}

void LinearConstraint::c_bigger_a_OffDiagonal()
{
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
                {
                    expr_01 += a[j][k][l];
                }
                IloConstraint constraint = (c[k][l] >= expr_01);
                string name = "c_bigger_a" + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_01.end();
                
            }
        }
    }
}

void LinearConstraint::c_bigger_a_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        
        IloExpr expr_01(env);
        for (int j = k; j<networkSize; j++)
        {
            expr_01 += a[j][k][k];
        }
        IloConstraint constraint = (c[k][0] >= expr_01);
        string name = "c_bigger_a" + SSTR(k) + SSTR(k);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_01.end();
    }
}

