//
//  SharedConstraint.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 28/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "SharedConstraint.hpp"

void SharedConstraint::diagonalSumEqualsOne()
{
    for (int k = 0; k< clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        string name = "diagonalEqualsOne" + SSTR(k) + SSTR(k);
        
        for (int i = k; i<networkSize; i++)
        {
            expr_01 += relationMatrix[i][i] * x[i][k];
            expr_01.setName(name.c_str());
            LOG(name);
        }
        
        IloConstraint constraint = (expr_01 == dsOne[k][0]);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_01.end();
        
    }
}

void SharedConstraint::diagonalSumEqualsZero()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    for (int k = 0; k< clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        string name = "diagonalSumEqualsZero" + SSTR(k) + SSTR(k);
        
        for (int i = k; i<networkSize; i++)
        {
            expr_01 += (1-relationMatrix[i][i]) * x[i][k];
            
        }
        
        IloConstraint constraint = (dsZero[k][0] == expr_01);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_01.end();
        
    }
}

void SharedConstraint::totalBlockSumEqualsOne()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    
    if(fDetails.release == ALL)
    {
        totalBlockSumEqualsOne_All();
    }
    if(fDetails.release == OFF_DIAGONAL)
    {
        totalBlockSumEqualsOne_OffDiagonal();
    }
    if(fDetails.release == DIAGONAL)
    {
        totalBlockSumEqualsOne_Diagonal();
    }
}

void SharedConstraint::totalBlockSumEqualsOne_All()
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
                
                for (int j = l; j<i; j++)
                {
                    expr_01 += relationMatrix[i][j] * y[i][j][k][l];
                }
                
                for (int j = max(i+1,l); j<networkSize; j++)
                {
                    expr_01 += relationMatrix[i][j] * y[j][i][l][k];
                }
            }
            
            IloConstraint constraint = (expr_01 == tbsOne[k][l]);
            string name = "tbsOne" + SSTR(k) + SSTR(l);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
            LOG(name);
        }
    }
    
}

void SharedConstraint::totalBlockSumEqualsOne_OffDiagonal()
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
                    for (int j = l; j<i; j++)
                    {
                        expr_01 += relationMatrix[i][j] * y[i][j][k][l];
                    }
                    
                    for (int j = max(i+1,l); j<networkSize; j++)
                    {
                        expr_01 += relationMatrix[i][j] * y[j][i][l][k];
                    }
                }
                
                IloConstraint constraint = (expr_01 == tbsOne[k][l]);
                string name = "tbsOne" + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_01.end();
                LOG(name);
                
            }
        }
    }
}
void SharedConstraint::totalBlockSumEqualsOne_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        
        for (int i = k; i<networkSize; i++)
        {
            for (int j = k; j<i; j++)
            {
                expr_01 += relationMatrix[i][j] * y[i][j][k][k];
            }
            
            for (int j = max(i+1,k); j<networkSize; j++)
            {
                expr_01 += relationMatrix[i][j] * y[j][i][k][k];
            }
        }
        
        FunctionRelease releaseSharedVariable = DataManager::getDataManager()->releaseNullBlock;
        
        if (releaseSharedVariable == DIAGONAL)
        {
            IloConstraint constraint = (expr_01 == tbsOne[k][0]);
            string name = "tbsOne" + SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
            LOG(name);
        }
        if (releaseSharedVariable != DIAGONAL)
        {
            IloConstraint constraint = (expr_01 == tbsOne[k][k]);
            string name = "tbsOne" + SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
            LOG(name);
        }
    }
}

void SharedConstraint::totalBlockSumEqualsZero()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if(fDetails.release == ALL)
    {
        totalBlockSumEqualsZero_All();
    }
    if(fDetails.release == OFF_DIAGONAL)
    {
        totalBlockSumEqualsZero_OffDiagonal();
    }
    if(fDetails.release == DIAGONAL)
    {
        totalBlockSumEqualsZero_Diagonal();
    }
}


void SharedConstraint::totalBlockSumEqualsZero_All()
{
    int limit =  clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            IloExpr expr_01(env);
            
            for (int i = k; i<networkSize; i++)
            {
                
                for (int j = l; j<i; j++)
                {
                    expr_01 += (1 - relationMatrix[i][j]) * y[i][j][k][l];
                }
                
                for (int j = max(i+1,l); j<networkSize; j++)
                {
                    expr_01 += (1 - relationMatrix[i][j]) * y[j][i][l][k];
                }
            }
            IloConstraint constraint = (expr_01 == tbsZero[k][l]);
            string name = "tbsZero" + SSTR(k) + SSTR(l);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
            LOG(name);
        }
    }
    
    
}
void SharedConstraint::totalBlockSumEqualsZero_OffDiagonal()
{
    int limit =  clusterUpperBound-1;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            
            if (k!=l) {
                IloExpr expr_01(env);
                
                for (int i = k; i<networkSize; i++)
                {
                    
                    for (int j = l; j<i; j++)
                    {
                        expr_01 += (1 - relationMatrix[i][j]) * y[i][j][k][l];
                    }
                    
                    for (int j = max(i+1,l); j<networkSize; j++)
                    {
                        expr_01 += (1 - relationMatrix[i][j]) * y[j][i][l][k];
                    }
                }
                IloConstraint constraint = (expr_01 == tbsZero[k][l]);
                string name = "tbsZero" + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                expr_01.end();
                LOG(name);
            }
            
        }
    }
    
    
}
void SharedConstraint::totalBlockSumEqualsZero_Diagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        
        for (int i = k; i<networkSize; i++)
        {
            for (int j = k; j<i; j++)
            {
                expr_01 += (1 - relationMatrix[i][j]) * y[i][j][k][k];
            }
            
            for (int j = max(i+1,k); j<networkSize; j++)
            {
                expr_01 += (1 - relationMatrix[i][j]) * y[j][i][k][k];
            }
        }
        
        
        FunctionRelease releaseSharedVariable = DataManager::getDataManager()->releaseCompleteBlock;
        
        if (releaseSharedVariable == DIAGONAL)
        {
            IloConstraint constraint = (expr_01 == tbsZero[k][0]);
            string name = "tbsOne" + SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
            LOG(name);
        }
        if (releaseSharedVariable != DIAGONAL)
        {
            IloConstraint constraint = (expr_01 == tbsZero[k][k]);
            string name = "tbsZero" + SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
            LOG(name);
        }
        
        
    }
}



/*********************************************************/

/*sumOverF*/

/*********************************************************/

void SharedConstraint::sumOverF()

{
    IloExpr expr_02(env);
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
//      if(itsSymmetricGraph && !DataManager::getDataManager()->areThereNonSymmetricPropertie())
        if(itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int i = 0; i<fPSize; i++)
            {
                FunctionRelease release = DataManager::getDataManager()->functionMapping[i].release;

//                bool itsSymmetricProperty = DataManager::getDataManager()->functionMapping[i].symmetricProperty;
//                bool areThereNonSymmetricPropertie = DataManager::getDataManager()->areThereNonSymmetricPropertie();
//                if(itsSymmetricProperty && !areThereNonSymmetricPropertie && itsSymmetricGraph)
                
                if(itsSymmetricGraph)
                {
                    sumOverFSymmetric(release, expr_02, i, k, l);
                }
                else
                {
                    sumOverFNotSymmetric(release, expr_02, i, k, l);
                }
            }
        }
    }
    
    typeObjectiveFunction = ALL_FUNCTIONS;
    setObjectiveFunction(expr_02);
}

void SharedConstraint::sumOverFNotSymmetric(FunctionRelease release, IloExpr expr_02, int i, int k, int l)
{
    if(release == ALL)
    {
        expr_02 += f[i][k][l] * p[i][k][l];
    }
    if(release == DIAGONAL)
    {
        if(k==l)
            expr_02 += f[i][k][0] * p[i][k][0];
    }
    
    if(release == OFF_DIAGONAL)
    {
        if(k!=l)
            expr_02 += f[i][k][l] * p[i][k][l];
    }
}



void SharedConstraint::sumOverFSymmetric(FunctionRelease release, IloExpr expr_02, int i, int k, int l)
{
    if(release == ALL)
        
    {
        if (l<k)
            expr_02 += f[i][k][l] * p[i][k][l];
        expr_02 += f[i][k][l] * p[i][k][l];
    }
    if(release == DIAGONAL)
    {
        if(k==l)
            expr_02 += f[i][k][0] * p[i][k][0];
    }
    if(release == OFF_DIAGONAL)
    {
        if(k!=l)
            expr_02 += 2 * f[i][k][l] * p[i][k][l];
    }
}

/*********************************************************/
/*linesError*/
/*********************************************************/

void SharedConstraint::linesError()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        linesErrorAll();
    }
    if (fDetails.release == OFF_DIAGONAL)
    {
        linesErrorOffDiagonal();
    }
    if (fDetails.release == DIAGONAL)
    {
        linesErrorDiagonal();
    }
}

void SharedConstraint::linesErrorAll()
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
                
                
//                expr_01+=(1-emptyCluster[k]);
                
                
                for (int j = l; j<i; j++)
                {
                    expr_01 += (1 - relationMatrix[i][j]) * y[i][j][k][l];
                    
                }
                
                for (int j = max(i+1,l); j<networkSize; j++)
                {
                    
                    expr_01 += (1 - relationMatrix[i][j]) * y[j][i][l][k];
                }
                
                IloConstraint constraint = (expr_01 == lineError[i][k][l]);
                string name = "lineError" + SSTR(i) + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                LOG(name);
                expr_01.end();
                
                
            }
        }
    }
}

void SharedConstraint::linesErrorOffDiagonal()
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
                    IloExpr expr_01(env);
//                    expr_01+=(1-emptyCluster[k]);
                    
                    for (int j = l; j<i; j++)
                    {
                        expr_01 += (1 - relationMatrix[i][j]) * y[i][j][k][l];
                    }
                    
                    for (int j = max(i+1,l); j<networkSize; j++)
                    {
                        expr_01 += (1 - relationMatrix[i][j]) * y[j][i][l][k];
                    }
                    
                    IloConstraint constraint = (expr_01 == lineError[i][k][l]);
                    string name = "lineError" + SSTR(k) + SSTR(l);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                    LOG(name);
                    expr_01.end();
                }
            }
        }
    }
}

void SharedConstraint::linesErrorDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int i = k; i<networkSize; i++)
        {
            IloExpr expr_01(env);
            
            for (int j = k; j<i; j++)
            {
                expr_01 += (1 - relationMatrix[i][j]) * y[i][j][k][k];
            }
            
            for (int j = max(i+1,k); j<networkSize; j++)
            {
                expr_01 += (1 - relationMatrix[i][j]) * y[j][i][k][k];
            }
            
            IloConstraint constraint = (expr_01 == lineError[i][k][k]);
            string name = "lineError" + SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
            LOG(name);
            expr_01.end();
        }
    }
}
/*********************************************************/
/*columnsError*/
/*********************************************************/

void SharedConstraint::columnsError()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        columnsErrorAll();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        columnsErrorOffDiagonal();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        columnsErrorDiagonal();
    }
    
}

void SharedConstraint::columnsErrorAll()
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
                
                for (int i = k; i<j; i++)
                {
                    expr_01 += (1 - relationMatrix[i][j]) * y[j][i][l][k] ;
                }
                
                for (int i = max(j+1,k); i<networkSize; i++)
                {
                    expr_01 += (1 - relationMatrix[i][j]) * y[i][j][k][l];
                }
                
                IloConstraint constraint = (expr_01 == columnError[j][k][l] ) ;
                
                string name = "columnsErrorAll" + SSTR(j) + SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                LOG(name);
                expr_01.end();
            }
        }
    }
}

void SharedConstraint::columnsErrorOffDiagonal()
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
                if (k!=l)
                {
                    IloExpr expr_01(env);
                    
                    for (int i = k; i<j; i++)
                    {
                        expr_01 += (1 - relationMatrix[i][j]) * y[j][i][l][k];
                    }
                    
                    for (int i = max(j+1,k); i<networkSize; i++)
                    {
                        expr_01 += (1 - relationMatrix[i][j]) * y[i][j][k][l];
                    }
                    
                    IloConstraint constraint = (expr_01 == columnError[j][k][l]);
                    
                    string name = "columnsErrorAll" + SSTR(j) + SSTR(k) + SSTR(l);
                    constraint.setName(name.c_str());
                    model.add(constraint);
                    LOG(name);
                    expr_01.end();
                }
                
            }
        }
    }
}

void SharedConstraint::columnsErrorDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int j = k; j<networkSize; j++)
        {
            IloExpr expr_01(env);
            
            for (int i = k; i<j; i++)
            {
                expr_01 += (1 - relationMatrix[i][j]) * y[j][i][k][k];
            }
            
            
            for (int i = max(j+1,k); i<networkSize; i++)
            {
                expr_01 += (1 - relationMatrix[i][j]) * y[i][j][k][k];
            }
            
            IloConstraint constraint = (expr_01 == columnError[j][k][k]);
            
            string name = "columnsErrorAll" + SSTR(j) + SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
            LOG(name);
            expr_01.end();
        }
    }
}

/*********************************************************/
/*rowRegularError*/
/*********************************************************/

void SharedConstraint::rowRegularError()
{
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();

    
    if (fDetails.release == ALL)
    {
        rowRegularErrorAll();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        rowRegularErrorDiagonal();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        rowRegularErrorOffDiagonal();
    }
}


void SharedConstraint::rowRegularErrorAll()
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
                
                
                
                for (int j = l; j<i; j++)
                {
                    expr_01 += relationMatrix[i][j] * y[i][j][k][l];
                }
                
                for (int j = max(i+1,l); j<networkSize; j++)
                {
                    expr_01 += relationMatrix[i][j] * y[j][i][l][k];
                }
                
                expr_01 += rowError[i][k][l];

                if ( k==l )
                {
                    expr_01+= relationMatrix[i][i]*x[i][k];
                }
                
                IloConstraint constraint = (expr_01 >=  x[i][k] - 1*( emptyCluster[k] + emptyCluster[l]));
//                 -1 + expr_01 - (emptyCluster[l] + emptyCluster[k]) +  (x[j][l]-1)

               // IloConstraint constraint = (expr_01 >= x[i][k] + emptyCluster[k] );
                string name = "rowRegularError" +  SSTR(i) + SSTR(k) + SSTR(l);
                
                constraint.setName(name.c_str());
                model.add(constraint);
                LOG(name);
                expr_01.end();
            }
        }
    }
}

void SharedConstraint::rowRegularErrorDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
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
            
            FunctionRelease releaseSharedVariable = DataManager::getDataManager()->releaseRegularBlock;
            
            if (releaseSharedVariable == DIAGONAL)
                expr_01 += rowError[i][k][0] + relationMatrix[i][i]*x[i][k];
            else
                expr_01 += rowError[i][k][k] + relationMatrix[i][i]*x[i][k];
            
            IloConstraint constraint = (expr_01 >= x[i][k]  - 1 * ( emptyCluster[k] + emptyCluster[k]));
            string name = "RowRegularError" +  SSTR(i) + SSTR(k) + SSTR(k);
            
            constraint.setName(name.c_str());
            model.add(constraint);
            LOG(name);
            expr_01.end();
        }
    }
}

void SharedConstraint::rowRegularErrorOffDiagonal()
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
                    IloExpr expr_01(env);
                    
                    for (int j = l; j<i; j++)
                    {
                        expr_01 += relationMatrix[i][j] * y[i][j][k][l];
                    }
                    
                    for (int j = max(i+1,l); j<networkSize; j++)
                    {
                        expr_01 += relationMatrix[i][j] * y[j][i][l][k];
                    }
                    
                    expr_01 += rowError[i][k][l];
                    
                    IloConstraint constraint = (expr_01 >= x[i][k] - 1 * ( emptyCluster[k] + emptyCluster[l]));
                    string name = "RowRegularError" +  SSTR(i) + SSTR(k) + SSTR(l);
                    
                    constraint.setName(name.c_str());
                    model.add(constraint);
                    LOG(name);
                    expr_01.end();
                }
            }
        }
    }
}

/*********************************************************/
/*colRegularError*/
/*********************************************************/

void SharedConstraint::colRegularError()
{
    
    FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
    
    if (fDetails.release == ALL)
    {
        colRegularErrorAll();
    }
    
    if (fDetails.release == DIAGONAL)
    {
        colRegularErrorDiagonal();
    }
    
    if (fDetails.release == OFF_DIAGONAL)
    {
        colRegularErrorOffDiagonal();
    }
}

void SharedConstraint::colRegularErrorAll()
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
                
                for (int i = k; i<j; i++)
                {
                    expr_01 += relationMatrix[i][j] * y[j][i][l][k];
                }
                
                for (int i = max(j+1,k); i<networkSize; i++)
                {
                    expr_01 += relationMatrix[i][j] * y[i][j][k][l];
                }

                expr_01 += colError[j][k][l];
                
                if ( k==l )
                {
                    expr_01+= relationMatrix[j][j] * x[j][l];
                }
               


                IloConstraint constraint = (expr_01 >= x[j][l]  - 1 * ( emptyCluster[k] + emptyCluster[l]));
                
                string name = "colRegularError" + SSTR(j) +SSTR(k) + SSTR(l);
                constraint.setName(name.c_str());
                model.add(constraint);
                LOG(name);
                expr_01.end();
            }
        }
    }
}


void SharedConstraint::colRegularErrorDiagonal()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int j = k; j<networkSize; j++)
        {
            IloExpr expr_01(env);
            
            
            for (int i = k; i<j; i++)
            {
                expr_01 += relationMatrix[i][j] * y[j][i][k][k];
            }
            
            for (int i = max(j+1,k); i<networkSize; i++)
            {
                expr_01 += relationMatrix[i][j] * y[i][j][k][k];
            }
            
            FunctionDetails fDetails = DataManager::getDataManager()->getCurrentfDetails();
            FunctionRelease releaseSharedVariable = DataManager::getDataManager()->releaseRegularBlock;
            
            if (releaseSharedVariable == DIAGONAL)
                expr_01 += colError[j][k][0] + relationMatrix[j][j]*x[j][k];
            else
                expr_01 += colError[j][k][k] + relationMatrix[j][j]*x[j][k];
            
            IloConstraint constraint = (expr_01 >= x[j][k]  - 1 * ( emptyCluster[k] + emptyCluster[k]));
            string name = "colRegularError" + SSTR(j) +SSTR(k) + SSTR(k);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
            LOG(name);
        }
    }
}


void SharedConstraint::colRegularErrorOffDiagonal()
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
                    IloExpr expr_01(env);
                    
                    for (int i = k; i<j; i++)
                    {
                        expr_01 += relationMatrix[i][j] * y[j][i][l][k];
                    }
                    
                    for (int i = max(j+1,k); i<networkSize; i++)
                    {
                        expr_01 += relationMatrix[i][j] * y[i][j][k][l];
                    }
                    
                    expr_01 += colError[j][k][l];
                    
                    if ( k==l )
                    {
                        expr_01+= relationMatrix[j][j] * x[j][l];
                    }
                    
                    IloConstraint constraint = (expr_01 >= x[j][l] - 1 * ( emptyCluster[k] + emptyCluster[l]));
                    
                    string name = "colRegularError" + SSTR(j) +SSTR(k) + SSTR(l);
                    
                    constraint.setName(name.c_str());
                    model.add(constraint);
                    expr_01.end();
                    LOG(name);
                }
            }
        }
    }
}

/*********************************************************/
/*sumEmptyCluster*/
/*********************************************************/

void SharedConstraint::sumEmptyCluster()
{
    

    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        
        for (int i = k; i<networkSize; i++)
        {
            expr_01 += x[i][k];
            
            IloConstraint constraint = (1-emptyCluster[k] >= x[i][k]);
            string name_01 = "sumEmptyCluster_BiggerX" + SSTR(i) + SSTR(k);
            constraint.setName(name_01.c_str());
            model.add(constraint);
            
            
        }
        
        IloConstraint constraint_02 = (1-emptyCluster[k] <= expr_01);
        string name = "sumEmptyCluster" + SSTR(k);
        constraint_02.setName(name.c_str());
        model.add(constraint_02);
        expr_01.end();
        LOG(name);
    }
    
    for (int k = 0; k<clusterUpperBound-1; k++)
    {
        IloRange orderedCluster(env, emptyCluster[k]-emptyCluster[k+1],0);
        string name = "orderedCluster" + SSTR(k);
        orderedCluster.setName(name.c_str());
        model.add(orderedCluster);
    }
}

/*********************************************************/
/*blockSize*/
/*********************************************************/

void SharedConstraint::blockSize()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l<clusterUpperBound; l++)
        {
            IloExpr expr_01(env);
            for (int i = 0; i<networkSize; i++)
            {
                for (int j = 0; j<networkSize; j++)
                {
                    expr_01 += y[i][j][k][l];
                }
            }
            IloConstraint constraint = (expr_01 == bSize[k][l]);
            string name = "bSize" + SSTR(k) + SSTR(l);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
            LOG(name);
        }
    }
}

/*********************************************************/
/*clusterHasAtLeastOneNode*/
/*********************************************************/

void SharedConstraint::clusterHasAtLeastOneNode()
{
    for (int k = 0; k<clusterUpperBound; k++)
    {
        IloExpr expr_01(env);
        for (int i = k; i<networkSize; i++)
        {
            expr_01 += x[i][k];
        }
        string varName = "clusterHasAtLeastOneNode" + SSTR(k);
        IloRange constraint(env, 1, expr_01);
        constraint.setName(varName.c_str());
        model.add(constraint);
        expr_01.end();
    }
}

/*********************************************************/
/*nodeBelongsOnlyOneCluster*/
/*********************************************************/

void SharedConstraint::nodeBelongsOnlyOneCluster()
{
    for (int i = 0; i<networkSize; i++)
    {
        IloExpr expr_01(env);
        for (int k = 0; k<=min(i, clusterUpperBound-1); k++)
        {
            expr_01 += x[i][k];
        }
        string varName = "nodeBelongsOnlyOneCluster" + SSTR(i);
        IloConstraint constraint = (expr_01  == 1);
        constraint.setName(varName.c_str());
        model.add(constraint);
        expr_01.end();
    }
}


