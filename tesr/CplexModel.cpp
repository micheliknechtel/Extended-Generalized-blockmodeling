;//
//  CplexModel.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 16/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "CplexModel.hpp"
#include "ObjectiveFunctions.hpp"
#include "DataManager.hpp"
#include "DataControler.hpp"
#include <time.h>
#include "Definitions.h"
#include "PrintManager.hpp"
ILOHEURISTICCALLBACK4(callBack,
                      IloNumVarArray2, x,
                      IloNumVarArray2, startVarX,
                      IloNumMatrix, startValX,
                      bool, injected)
//ILOHEURISTICCALLBACK4(callBack,
//                      IloBoolVarArray2, x,
//                      IloBoolVarArray2, startVarX,
//                      IloBoolArray2, startValX,
//                      bool, injected)
{
    if (!injected)
    {
        injected = true;
        int size = (int) startVarX.getSize();
        
        IloArray<IntegerFeasibilityArray> feasX(getEnv(), size);
        for (int i = 0; i <size; i++)
        {
            feasX[i] = IntegerFeasibilityArray(getEnv());
        }
        
        for (IloInt i = 0; i <size; i++)
        {
            getFeasibilities(feasX[i], startVarX[i]);
        }
        
        cout<<endl;
        
        for (int i = 0; i < startVarX.getSize(); ++i)
        {
            int y = (int) startVarX[i].getSize();
            
            for (int j = 0; j < y; j++)
            {
                IntegerFeasibilityArray& f = feasX[i];
                
                if (f[j] != ImpliedFeasible)
                {
                    cout<<"startValX["<<i<<"]["<<j<<"] = "<< startValX[i][j]<<" "<<endl;
                    setBounds(startVarX[i][j], startValX[i][j], startValX[i][j]);
                }
            }
        }
        cout<<endl;
        
        
        if (solve())
        {
            cerr << "Injecting solution with objective " << getObjValue() << endl;
            
            IloNumMatrix valsX(getEnv(),x.getSize());
            for(int i=0; i <valsX.getSize(); i++)
            {
                valsX[i] = IloNumArray(getEnv());
            }
            
            for (IloInt i = 0; i < valsX.getSize(); i++)
            {
                getValues(valsX[i], x[i]);
                cout<<"valsX["<<i<<"] = "<<valsX[i] <<endl;
                
            }
            
            IloNumVarArray z(getEnv());
            IloNumArray  y(getEnv());
            
            for (IloInt i = 0; i < valsX.getSize(); i++)
            {
                z.add(x[i]);
                y.add(valsX[i]);
                
            }
            setSolution(z, y, 0);
            valsX.end();
            
        }
        else
            cerr << "solve() failed!" << endl;
    }
}

void CplexModel::solveCplexModel()
{
    IloEnv env;
    
    try
    {
        IloModel model(env);
        IloCplex cplex(model);
        IloTimer timer(env);
        
        setParam(cplex);
        
        const IloNum startTime = cplex.getCplexTime();
        
        Constraints *constraints = new Constraints(env,model);
        constraints->addConstraints();
        
        ObjectiveFunctions *objectivefunctions = new ObjectiveFunctions(env, model);
        objectivefunctions->setObjectiveFunctionMin(constraints->getObjectiveFuncion());
        
        cplex.exportModel(DataManager::getDataManager()->getModelLocation().c_str());
        
//        setMIPstart(constraints, env, cplex);
        
        if(!cplex.solve())
        {
            env.error() << "Failed to optimize LP" << endl;
            throw(-1);
        }
        
        const IloNum endTime = cplex.getCplexTime();
        
        cout<<endl;
        cout<<"Solution status                  = " << cplex.getStatus() << endl;
        cout<<"Minimal Objective Function Value = " << cplex.getObjValue() << endl;
        cout<<"Gap                              = " << cplex.getMIPRelativeGap()<<endl;
        cout<<"Nodes                            = " << cplex.getNnodes()<<endl;
        cout<<"Its symmetric graph              = " << (DataManager::getDataManager()->graph->itsSymmetricGraph == true ? "true": "false") << endl;
        cout<<"Elapsed wall clock time          = " << endTime - startTime << " seconds" << endl;
        cout<<"EmptyCluster setup as            = " << (DataManager::getDataManager()->emptyCluster == true ? "true": "false")<<endl;
        cout<<"Relation Matrix                  = " << DataManager::getDataManager()->fileRelationMatrix <<endl;
        cout<<"Additional Constraint            = " << (DataManager::getDataManager()->getAdditionalConstraint() == true ? "on": "off")<<endl;
        
        constraints->getMatrixBlock(cplex);
        constraints->get_AllFunctions(cplex);
        constraints->get_x(cplex);
        
    }
    catch (IloException& e)
    {
        cerr << "Error: " << e << endl;
    }
    catch (...)
    {
        cerr << "Unknown exception caught" << endl;
    }
    env.end();
}

void CplexModel::setMIPstart(Constraints *constraints, IloEnv env, IloCplex cplex)
{
    bool injection = false;
    bool m  = false;
    
    int clusterUpperBound = DataManager::getDataManager()->clusterUpperBound;
    int networkSize       = DataManager::getDataManager()->networkSize;
    
    IloNumVarArray2 varX(env, networkSize);
    IloNumMatrix    valX(env, networkSize);
    
    for(int i=0; i <networkSize; i++)
        varX[i] = IloNumVarArray(env);
    
    for(int i=0; i <networkSize; i++)
        valX[i] = IloNumArray(env, networkSize, 0, 1);
    
    //
    //    IloBoolArray2    valX(env, networkSize);
    //    IloBoolVarArray2 varX(env, networkSize);
    //
    //
    //    for(int i=0; i <networkSize; i++)
    //        varX[i] = IloBoolVarArray(env);
    //
    //    for(int i=0; i <networkSize; i++)
    //        valX[i] = IloBoolArray(env, networkSize);
    
    for(int i=0; i <networkSize; i++)
    {
        for(int j=0; j<=min(i,clusterUpperBound-1); j++)
        {
            varX[i].add(constraints->x[i][j]);
            valX[i].add(0);
        }
    }
    
    
    map<int, vector<int>> mapAux;
    map<int, vector<int>>::iterator it = DataManager::getDataManager()->xSolution->solution.begin();
    
    for (;it!=DataManager::getDataManager()->xSolution->solution.end(); it++)
    {
        std::sort (it->second.begin(), it->second.end());
        for (int i = 0; i<it->second.size(); i++)
        {
            if(it->second.at(i)==i)
            {
                mapAux.insert(make_pair(i, it->second));
                break;
            }
            if(it->second.at(i)>=i)
            {
                mapAux.insert(make_pair(it->second.at(i), it->second));
                break;
            }
        }
    }
    
    PrintManager().printPartition(mapAux);
    
    valX[0][0] = true;
    valX[1][1] = true;
    valX[2][1] = true;
    valX[3][1] = true;
    valX[4][1] = true;
    valX[5][1] = true;
    
    valX[0][0] = 1;
    valX[1][0] = 0;
    valX[1][1] = 1;
    valX[2][0] = 0;
    valX[2][1] = 1;
    valX[2][2] = 0;
    valX[3][0] = 0;
    valX[3][1] = 1;
    valX[3][2] = 0;
    valX[3][3] = 0;
    valX[4][0] = 0;
    valX[4][1] = 1;
    valX[4][2] = 0;
    valX[4][3] = 0;
    valX[5][0] = 0;
    valX[5][1] = 1;
    valX[5][2] = 0;
    valX[5][3] = 0;
    
    cplex.use(callBack(env, constraints->x, varX, valX, injection));
}

void CplexModel::setParam(IloCplex cplex)
{
    cplex.setParam(IloCplex::PreLinear, 0);
    cplex.setParam(IloCplex::Param::Preprocessing::Aggregator, 0);
    cplex.setParam(IloCplex::Param::Preprocessing::Presolve, 0);
    cplex.setParam(IloCplex::TiLim, 7200);
    cplex.setParam(IloCplex::Threads, 1);
    cplex.setParam(IloCplex::HeurFreq, -1);
    cplex.setParam(IloCplex::Cliques, -1);
    cplex.setParam(IloCplex::Covers, -1);
    cplex.setParam(IloCplex::DisjCuts, -1);
    cplex.setParam(IloCplex::FlowCovers, -1);
    cplex.setParam(IloCplex::FlowPaths, -1);
    cplex.setParam(IloCplex::FracCuts, -1);
    cplex.setParam(IloCplex::GUBCovers, -1);
    cplex.setParam(IloCplex::ImplBd, -1);
    cplex.setParam(IloCplex::MIRCuts, -1);
    cplex.setParam(IloCplex::ZeroHalfCuts, -1);
    cplex.setParam(IloCplex::MCFCuts, -1);
    cplex.setParam(IloCplex::Param::MIP::Cuts::LiftProj, -1);
}


