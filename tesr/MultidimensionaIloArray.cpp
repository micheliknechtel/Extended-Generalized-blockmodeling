//
//  MultidimensionaIloArray.cpp
//
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "MultidimensionaIloArray.hpp"
#include "DataManager.hpp"



IloBoolVarArray2 MultidimensionaIloArray::IloBoolArray2_x_without_artificial_symmetry(const IloEnv env, int n, int clusterUpperBound, string varName) //(OK)
{
    IloBoolVarArray2 x(env, n);
    
    for(int i=0; i <n; i++)
    {
        x[i] = IloBoolVarArray(env, min(i,clusterUpperBound-1)+1);
        
        for(int j=0; j<=min(i,clusterUpperBound-1); j++)
        {
            string name = varName.c_str() + SSTR(i) + SSTR(j);
            x[i][j].setName(name.c_str());
            LOG(name);
        }
    }
    return x;
}


IloNumVarArray2 MultidimensionaIloArray::IloNumVarArray2_x_without_artificial_symmetry(const IloEnv env, int n, int clusterUpperBound, string varName) //(OK)
{
    IloNumVarArray2 x(env, n);
    
    for(int i=0; i <n; i++)
    {
        int sum = min(i,clusterUpperBound-1)+1;
        x[i] = IloNumVarArray(env, sum, 0, 1);
        
        for(int j=0; j<=min(i,clusterUpperBound-1); j++)
        {
            string name = varName.c_str() + SSTR(i) + SSTR(j);
            x[i][j].setName(name.c_str());
            LOG(name);
        }
    }
    return x;
}

IloNumVarArray3 MultidimensionaIloArray::IloNumArray3_F(const IloEnv env, int lb, int ub, string varName) //(OK)
{
    IloNumVarArray3 x(env, DataManager::getDataManager()->functionSize);
    int limit = DataManager::getDataManager()->clusterUpperBound-1;
    
    for(int b=0; b <DataManager::getDataManager()->functionSize; b++)
    {
        FunctionRelease release = DataManager::getDataManager()->functionMapping[b].release;
        
        x[b] = IloNumVarArray2(env, DataManager::getDataManager()->clusterUpperBound);
        
        for(int k=0; k <DataManager::getDataManager()->clusterUpperBound; k++)
        {
            if (release == DIAGONAL)
            {
                x[b][k] = IloNumVarArray(env, 1, lb, ub );
                string name  = varName.c_str() + SSTR(b) + SSTR(k) + SSTR(k);
                x[b][k][0].setName(name.c_str());
                LOG(name);
            }
            else
            {
                //                bool areThereNonSymmetricPropertie = DataManager::getDataManager()->areThereNonSymmetricPropertie();
                //                if (DataManager::getDataManager()->graph->itsSymmetricGraph && !areThereNonSymmetricPropertie)
                
                if (DataManager::getDataManager()->graph->itsSymmetricGraph)
                    limit = k;
                
                x[b][k] = IloNumVarArray(env, limit+1, lb, ub );
                
                for(int l=0; l <=limit; l++)
                {
                    string name  = varName.c_str() + SSTR(b) + SSTR(k) + SSTR(l);
                    x[b][k][l].setName(name.c_str());
                    LOG(name);
                }
            }
        }
    }
    return x;
}

IloNumVarArray3 MultidimensionaIloArray::IloNumArray3_W(const IloEnv env, int lb, int ub, string varName) //(OK)
{
    IloNumVarArray3 x(env, DataManager::getDataManager()->functionSize);
    int limit = DataManager::getDataManager()->clusterUpperBound-1;
    
    for(int b=0; b <DataManager::getDataManager()->functionSize; b++)
    {
        FunctionRelease release = DataManager::getDataManager()->functionMapping[b].release;
        
        x[b] = IloNumVarArray2(env, DataManager::getDataManager()->clusterUpperBound);
        
        for(int k=0; k <DataManager::getDataManager()->clusterUpperBound; k++)
        {
            if (release == DIAGONAL)
            {
                x[b][k] = IloNumVarArray(env, 1, lb, ub, ILOINT );
                string name  = varName.c_str() + SSTR(b) + SSTR(k) + SSTR(k);
                x[b][k][0].setName(name.c_str());
                LOG(name);
            }
            else
            {
                //                bool areThereNonSymmetricPropertie = DataManager::getDataManager()->areThereNonSymmetricPropertie();
                //                if (DataManager::getDataManager()->graph->itsSymmetricGraph && !areThereNonSymmetricPropertie)
                
                if (DataManager::getDataManager()->graph->itsSymmetricGraph)
                    limit = k;
                
                x[b][k] = IloNumVarArray(env, limit+1, lb, ub , ILOINT);
                
                for(int l=0; l <=limit; l++)
                {
                    string name  = varName.c_str() + SSTR(b) + SSTR(k) + SSTR(l);
                    x[b][k][l].setName(name.c_str());
                    LOG(name);
                }
            }
        }
    }
    return x;
}



IloNumArray3 MultidimensionaIloArray::IloNumArray3_Penalties(const IloEnv env) //(OK)
{
    IloNumArray3 x(env, DataManager::getDataManager()->functionSize);
    
    
    int limit = DataManager::getDataManager()->clusterUpperBound-1;
    
    for(int k=0; k <DataManager::getDataManager()->functionSize; k++)
    {
        FunctionRelease release = DataManager::getDataManager()->functionMapping[k].release;
        
        
        
        x[k] = IloNumArray2(env, DataManager::getDataManager()->clusterUpperBound);
        
        for(int l=0; l<DataManager::getDataManager()->clusterUpperBound; l++)
        {
            //            if (DataManager::getDataManager()->graph->itsSymmetricGraph && !DataManager::getDataManager()->areThereNonSymmetricPropertie())
            
            if (DataManager::getDataManager()->graph->itsSymmetricGraph)
                limit = l;
            
            if (release == DIAGONAL)
            {
                x[k][l] = IloNumArray(env, 1);
            }
            else
            {
                x[k][l] = IloNumArray(env, limit+1);
            }
        }
    }
    return x;
}

IloNumVarArray4 MultidimensionaIloArray::IloNumArray4_y_without_artificial_symmetry(const IloEnv env, int n, int clusterUpperBound, string varName) //(OK)
{
    IloNumVarArray4 x(env, n);
    
    for(int i=0; i <n; i++)
    {
        x[i] = IloNumVarArray3(env,i);
        
        for(int j=0; j<i; j++)
        {
            x[i][j] = IloNumVarArray2(env, (min(i,clusterUpperBound-1)+1));
            
            for(int k=0; k <= min(i,clusterUpperBound-1); k++)
            {
                x[i][j][k] = IloNumVarArray(env, min(j,clusterUpperBound-1)+1,0,1);
                
                for(int l=0; l <=min(j,clusterUpperBound-1); l++)
                {
                    string name  = varName + SSTR(i) + SSTR(j) + SSTR(k) + SSTR(l);
                    x[i][j][k][l].setName(name.c_str());
                    LOG(name);
                }
            }
        }
    }
    
    return x;
}

IloNumVarArray3 MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(const IloEnv env, int n, int lb, int ub, string varName,  FunctionRelease release) //(OK)
{
    IloNumVarArray3 x(env, n);
    int limit = n-1;
    
    for(int i=0; i <n; i++)
    {
        x[i] = IloNumVarArray2(env,n);
        
        for(int j=0; j <n; j++)
        {
            
            if (release == DIAGONAL)
            {
                x[i][j] = IloNumVarArray(env, 1, lb, ub );
                string name  = varName.c_str() + SSTR(i) + SSTR(j) + SSTR(j);
                x[i][j][0].setName(name.c_str());
                LOG(name);
                
            }
            else
            {
                x[i][j] = IloNumVarArray(env, limit+1, lb, ub );
                
                for(int k=0; k <=limit; k++)
                {
                    string name  = varName.c_str() + SSTR(i) + SSTR(j) + SSTR(k);
                    x[i][j][k].setName(name.c_str());
                    LOG(name);
                }
            }
        }
    }
    return x;
}

IloNumVarArray2 MultidimensionaIloArray::IloNumArray2_tbs_c_h(const IloEnv env, int n, int lb, int ub, string varName, FunctionRelease release) //(OK)
{
    int limit = n-1;
    IloNumVarArray2 x(env, n);
    
    for(int k=0; k <n; k++)
    {
        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
            limit = k;
        
        if (release == DIAGONAL)
        {
            x[k] = IloNumVarArray( env, 1, lb, ub, ILOINT);
            string name = varName.c_str() + SSTR(k) + SSTR(k);
            x[k][0].setName(name.c_str());
            LOG(name);
            
        }
        else
        {
            x[k] = IloNumVarArray( env, limit+1, lb, ub, ILOINT);
            
            for(int l=0; l<=limit; l++)
            {
                string name = varName.c_str() + SSTR(k) + SSTR(l);
                x[k][l].setName(name.c_str());
                LOG(name);
            }
        }
    }
    return x;
}

IloNumVarArray3 MultidimensionaIloArray::IloNumArray3_lineError_columnError(const IloEnv env, int lb, int ub, string varName)
{
    IloNumVarArray3 x(env, DataManager::getDataManager()->networkSize);
    int limit = DataManager::getDataManager()->clusterUpperBound-1;
    
    
    for(int b=0; b <DataManager::getDataManager()->networkSize; b++)
    {
        x[b] = IloNumVarArray2(env, DataManager::getDataManager()->clusterUpperBound);
        
        for(int k=0; k <DataManager::getDataManager()->clusterUpperBound; k++)
        {
            if (DataManager::getDataManager()->graph->itsSymmetricGraph)
                limit = k;
            
            x[b][k] = IloNumVarArray(env, limit+1, lb, ub);
            
            for(int l=0; l<=limit; l++)
            {
                string name  = varName.c_str() + SSTR(b) + SSTR(k) + SSTR(l);
                x[b][k][l].setName(name.c_str());
                LOG(name);
            }
        }
    }
    return x;
}

IloNumVarArray3 MultidimensionaIloArray::IloNumArray3_Z_B(const IloEnv env, int lb, int ub, string varName)
{
    IloNumVarArray3 x(env, DataManager::getDataManager()->networkSize);
    int limit = DataManager::getDataManager()->clusterUpperBound-1;
    
    
    for(int b=0; b <DataManager::getDataManager()->networkSize; b++)
    {
        x[b] = IloNumVarArray2(env, DataManager::getDataManager()->clusterUpperBound);
        
        for(int k=0; k <DataManager::getDataManager()->clusterUpperBound; k++)
        {
            if (DataManager::getDataManager()->graph->itsSymmetricGraph)
                limit = k;
            
            x[b][k] = IloNumVarArray(env, limit+1, lb, ub, ILOINT);
            
            for(int l=0; l<=limit; l++)
            {
                string name  = varName.c_str() + SSTR(b) + SSTR(k) + SSTR(l);
                x[b][k][l].setName(name.c_str());
                LOG(name);
            }
        }
    }
    return x;
}

IloNumVarArray3 MultidimensionaIloArray::IloNumArray3_O_A(const IloEnv env, int lb, int ub, string varName)
{
    IloNumVarArray3 x(env, DataManager::getDataManager()->networkSize);
    int limit = DataManager::getDataManager()->clusterUpperBound-1;
    
    
    for(int b=0; b <DataManager::getDataManager()->networkSize; b++)
    {
        x[b] = IloNumVarArray2(env, DataManager::getDataManager()->clusterUpperBound);
        
        for(int k=0; k <DataManager::getDataManager()->clusterUpperBound; k++)
        {
            if (DataManager::getDataManager()->graph->itsSymmetricGraph)
                limit = k;
            
            x[b][k] = IloNumVarArray(env, limit+1, lb, ub);
            
            for(int l=0; l<=limit; l++)
            {
                string name  = varName.c_str() + SSTR(b) + SSTR(k) + SSTR(l);
                x[b][k][l].setName(name.c_str());
                LOG(name);
            }
        }
    }
    return x;
}

IloNumArray3 MultidimensionaIloArray::IloNumArray3_ValF(const IloEnv env, int lb, int ub, string varName)
{
    IloNumArray3 x(env, DataManager::getDataManager()->functionSize);
    int limit = DataManager::getDataManager()->clusterUpperBound-1;
    
    for(int b=0; b <DataManager::getDataManager()->functionSize; b++)
    {
        FunctionRelease release = DataManager::getDataManager()->functionMapping[b].release;
        x[b] = IloNumArray2(env, DataManager::getDataManager()->clusterUpperBound);
        
        for(int k=0; k <DataManager::getDataManager()->clusterUpperBound; k++)
        {
            if (release == DIAGONAL)
            {
                x[b][k] = IloNumArray(env, 1, lb, ub );
            }
            else
            {
                if (DataManager::getDataManager()->graph->itsSymmetricGraph)
                    limit = k;
                
                x[b][k] = IloNumArray(env, limit+1, lb, ub );
            }
        }
    }
    return x;
}
