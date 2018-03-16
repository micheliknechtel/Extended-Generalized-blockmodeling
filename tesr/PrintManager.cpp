//
//  PrintManager.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "PrintManager.hpp"

using namespace std;

void PrintManager::printPartition(map<int,vector<int>> partition)
{
    if(logLevel)
    {
        for (map<int,vector<int>> ::iterator it = partition.begin();it!= partition.end(); it++)
        {
            cout<<"C"<<it->first<<" = { ";
            for (int i = 0; i<it->second.size(); i++)
            {
                if(i==it->second.size()-1)
                    cout<<it->second.at(i);
                else
                    cout<<it->second.at(i)<<" , ";
            }
            cout<<" }"<<endl;
        }
    }
}

void PrintManager::printMatrixBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    for (int i = 0; i < C1.size(); i++)
    {
        for (int j = 0; j < C2.size(); j++)
            cout << relationMatrix[C1[i]][C2[j]]<<" ";
        cout<<endl;
    }
    
}

void PrintManager::printBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    string strC1 = "\nC" + SSTRL(cluster_k) + " = { ";
    string strC2 = "C" + SSTRL(cluster_l) + " = { ";
    for (int i = 0; i < C1.size(); i++)
    {
        if (i!=C1.size()-1)
            strC1+= SSTRL(C1[i]) + " , ";
        else
            strC1+= SSTRL(C1[i]);
    }
    strC1+="}";
    for (int j = 0; j < C2.size(); j++)
    {
        if (j!=C2.size()-1)
            strC2+= SSTRL(C2[j]) + " , ";
        else
            strC2+= SSTRL(C2[j]);
    }
    strC2+="}";
    cout<<strC1<<endl;
    cout<<strC2<<endl<<endl;
    
}

void PrintManager::printMatrixBlock(map<int,vector<int>>partition)
{
    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"PARTITION MATRIX "<<endl;
        cout<<"----------------------------------------------------"<<endl;
        
        for (int i = 0; i<partition.size(); i++)
        {
            vector<int> line = partition.at(i);
            if (line.size()!=0)
                cout<<endl;
            else
                line.push_back(-9);
            for (int j = 0 ; j<line.size(); j++)
            {
                if (line[j]==-9) {
                    cout<<setw(2)<<"E"<<"| ";
                }
                else
                    cout<<setw(2)<<line.at(j)<<"| ";
                for (int l = 0; l<partition.size(); l++)
                {
                    vector<int> column = partition.at(l);
                    if (column.size()==0) {
                        cout<<" E ";
                    }
                    for (int k = 0 ; k<column.size(); k++)
                    {
                        if (line[j]==-9)
                            cout<<"__";
                        else
                            cout<<relationMatrix[line[j]][column[k]]<<"+";
                    }
                    if (column.size()!=0)
                        cout<<" ";
                }
                if (line.size()!=0)
                    cout<<endl;
            }
        }
    }
}

void PrintManager::printFitness(map<int,vector<int>>partition, map<pair<int,int>, MatchingError> imageMatrix, DataControler *d)
{
    
    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"DEVIATION MEASURE & IMAGE MATRIX "<<endl;
        cout<<"----------------------------------------------------"<<endl;
        for (int cluster_k = 0; cluster_k<partition.size(); cluster_k++)
        {
            for (int cluster_l = 0; cluster_l<partition.size(); cluster_l++)
            {
                cout<<setw(3)<<imageMatrix.at(make_pair(cluster_k, cluster_l)).blockError<<"+ ";
            }
            cout<<"\t|\t";
            for (int cluster_l = 0; cluster_l<partition.size(); cluster_l++)
            {
                cout<<d->typeToFunction(imageMatrix.at(make_pair(cluster_k, cluster_l)).idealBlockMatching)<<" ";
            }
            cout<<endl;
        }
    }
}

void PrintManager::errorHeader(int error)
{
    if(logLevel)
    {
        cout<<endl<<"----------------------------------------------------"<<endl<<endl;
        cout<<"TOTAL ERROR == "<<error<<endl<<endl;
    }
}


void PrintManager::printMove(int cluster, int node)
{
    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"move node "<<node<<" to cluster "<< cluster<<endl;
    }
}
void PrintManager::printSwap(int clusterA, int nodeA,int clusterB, int nodeB)
{
    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Swap:"<<endl;
        cout<<"\t node["<<nodeA<<"] -> cluster["<< clusterB<<"]"<<endl;
        cout<<"\t node["<<nodeB<<"] -> cluster["<< clusterA<<"]";
    }
}

void PrintManager::swapHeader(int partitionNumber, DataControler *d)
{
    // if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<partitionNumber<<") Swap"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Error            = "<<d->getMinGlobalError()<<endl;
        cout<<"ClusterSize      = "<<d->initialPartition.size()<<endl;
    }
}

void PrintManager::moveHeader(int partitionNumber, DataControler *d )
{
    // if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<partitionNumber<<") Move"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Error            = "<<d->getMinGlobalError()<<endl;
        cout<<"ClusterSize      = "<<d->initialPartition.size()<<endl;
    }
}

void PrintManager::printTime( time_t startTime)
{
    time_t endTime = time(&endTime);
    double currentTime = difftime(endTime, startTime );
    cout<<"ElapsedTime      = "<<currentTime<<" (in seconds)"<<endl;
    
}

void PrintManager::newPartition(int partitionNumber, int error, int clusterSize)
{
    //    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"New Partition "<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Error            = "<<error<<endl;
        cout<<"ClusterSize      = "<<clusterSize<<endl;
    }
}
void PrintManager::choosenPartition(int partitionNumber, int error, int clusterSize)
{
    //    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<partitionNumber<<") Choosen Partition "<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Error            = "<<error<<endl;
        cout<<"ClusterSize      = "<<clusterSize<<endl;

    }
}

void PrintManager::newLine()
{
    cout<<endl<<endl;
}

void PrintManager::solution(DataControler *d, time_t time)
{
    logLevel = true;
    cout<<endl<<"----------------------------------------------------"<<endl;
    cout<<"FOUND SOLUTION"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"DestiatonMesuare = "<<d->desviation<<endl;
    printTime(time);
    cout<<"----------------------------------------------------"<<endl;
    cout<<"PARTITION         "<<endl;
    cout<<"----------------------------------------------------"<<endl;
    printPartition(d->solution);
    printFitness(d->solution, d->bestfitnness, d);
    printMatrixBlock(d->solution);
    cout<<"----------------------------------------------------"<<endl<<endl;
    
}

void PrintManager::sharedParameters()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Shared parameters:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Directory path            \t"<<DataManager::getDataManager()->directoriePath<<endl;
    cout<<"Relation matrix file name \t"<<DataManager::getDataManager()->fileRelationMatrix<<endl;
    cout<<"Ideal blocks file name    \t"<<DataManager::getDataManager()->fileFunctionTable<<endl;
    cout<<"Matrix type               \t"<<DataManager::getDataManager()->getMatrixDataType()<<endl;
    cout<<"Cluster upper bound       \t"<<DataManager::getDataManager()->clusterUpperBound<<endl;
    cout<<"Heuristic                 \t"<<(DataManager::getDataManager()->heuristic == true ? "ON": "OFF")<<endl;
    cout<<"Model                     \t"<<(DataManager::getDataManager()->model == true ? "ON": "OFF")<<endl;
}


void PrintManager::inputData()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Input data:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    DataManager::getDataManager()->printFunctionTable();
    
    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        DataManager::getDataManager()->printRelationMatrix();
    }
}
void PrintManager::modelParameters()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Model parameters:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"ModelName                 \t"<<DataManager::getDataManager()->modelName<<endl;
    cout<<"Pre-processing mode       \t"<<(DataManager::getDataManager()->emptyCluster == true ? "ENABLE": "DISABLE")<<endl;
    cout<<"EmptyCluster              \t"<<(DataManager::getDataManager()->emptyCluster == true ? "ON": "OFF")<<endl;
    cout<<"Additional Constraint     \t"<<(DataManager::getDataManager()->emptyCluster == true ? "YES": "NOT")<<endl;
    cout<<"Graph                     \t"<<(DataManager::getDataManager()->graph->itsSymmetricGraph == true ? "SYMMETRICAL": "DIRECTIONAL") << endl;
    
}

void PrintManager::heuristicParameters()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Heuristic parameters:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Execution order           \t"<<(DataManager::getDataManager()->sequence == RANDOM ? "RANDOM":"SEQUENTIAL")<<endl;
    cout<<"Execution time (seconds)  \t"<<DataManager::getDataManager()->executionTime<<endl;
    cout<<"Log                       \t"<<(DataManager::getDataManager()->logLevel == false ? "OFF" : "ON")<<endl;
    cout<<"Code optimized            \t"<<(DataManager::getDataManager()->optimizedCode == false ? "LEVEL_01" : "LEVEL_02")<<endl;
    cout<<"Strategy                  \t"<<DataManager::getDataManager()->getHeuristicStrategyTexte()<<endl;
    cout<<"Number of root partitions \t"<<DataManager::getDataManager()->numRootPartitions<<endl;
    cout<<"Data validation           \t"<<(DataManager::getDataManager()->datacheck == false ? "OFF" : "ON")<<endl;
    cout<<"PredefinedPartition       \t"<<DataManager::getDataManager()->predefinedPartition<<endl;
    cout<<"PartitionCheck_01         \t"<<DataManager::getDataManager()->partitionCheck_01<<endl;
    cout<<"PartitionCheck_02         \t"<<DataManager::getDataManager()->partitionCheck_02<<endl;
}

void PrintManager::report()
{
    sharedParameters();
    cout<<endl<<endl;
    
    if(DataManager::getDataManager()->heuristic)
    {
        heuristicParameters();
        cout<<endl<<endl;
    }
    
    if(DataManager::getDataManager()->model)
    {
        modelParameters();
        cout<<endl<<endl;
    }
    
    inputData();
}
