//
//  BlockError.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "BlockError.hpp"
#include "DataManager.hpp"

BlockError::BlockError()
{
    relationMatrix = DataManager::getDataManager()->relationMatrix;
}

int BlockError::rowFunctional(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    vector<int> rowFunctionalLineError;
    int errorRowFunctional = 0;
    
    for (int i = 0; i < C1.size(); i++)
    {
        rowFunctionalLineError.push_back(0);
        
        for (int j = 0; j < C2.size(); j++)
        {
            rowFunctionalLineError.at(i)+= relationMatrix[C1[i]][C2[j]];
            if (rowFunctionalLineError.at(i) > 1) // Não sei se vale a pena colocar !!!!
                break;
        }
        if (rowFunctionalLineError.at(i) > 1 || rowFunctionalLineError.at(i) == 0)
        {
            errorRowFunctional +=1;
        }
    }
    return errorRowFunctional;
}


int BlockError::colFunctional(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    vector<int> colFunctionalLineError;
    
    int errorColFunctional = 0;
    
    for (int j = 0; j < C2.size(); j++)
    {
        colFunctionalLineError.push_back(0);
        for (int i = 0; i < C1.size(); i++)
        {
            colFunctionalLineError.at(j)+= relationMatrix[C1[i]][C2[j]];
        }
        if (colFunctionalLineError.at(j) > 1 || colFunctionalLineError.at(j) == 0)
        {
            errorColFunctional +=1;
        }
    }
    return errorColFunctional;
}


int BlockError::regularBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{/*
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    vector<int> rowRegularLineError;
    
    int errorRowRegular = 0;
    
    for (int i = 0; i < C1.size(); i++)
    {
        rowRegularLineError.push_back(0);
        
        for (int j = 0; j < C2.size(); j++)
            rowRegularLineError.at(i)+= relationMatrix[C1[i]][C2[j]];
        
        if ( rowRegularLineError.at(i) == 0)
            errorRowRegular +=1;
    }
     errorRowRegular;
    

    vector<int> colRegularLineError;
    int errorColRegular = 0;
    for (int j = 0; j < C2.size(); j++)
    {
        colRegularLineError.push_back(0);
        
        for (int i = 0; i < C1.size(); i++)
            colRegularLineError.at(j)+= relationMatrix[C1[i]][C2[j]];
        
        if ( colRegularLineError.at(j) == 0)
            errorColRegular +=1;
    }
     errorColRegular;

    int errorRegularBlock=errorRowRegular+errorColRegular;*/
    
    int errorRegularBlock = rowRegular(cluster_k, cluster_l, partition);
    errorRegularBlock += colRegular(cluster_k, cluster_l, partition);
    
    return errorRegularBlock;
}

int BlockError::completeBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    int sum = 0;
    
    for (int i = 0; i < C1.size(); i++)
        for (int j = 0; j < C2.size(); j++)
            sum += 1-relationMatrix[C1[i]][C2[j]];
    return sum;
}

int BlockError::nullBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    int sum = 0;
    
    for (int i = 0; i < C1.size(); i++)
        for (int j = 0; j < C2.size(); j++)
            sum += relationMatrix[C1[i]][C2[j]];
    return sum;
}

int BlockError::colDominant(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    vector<int> columError;
    
    int errorColDominant = (int) (C1.size() * C2.size());
    
    for (int j = 0; j < C2.size(); j++)
    {
        columError.push_back(0);
        for (int i = 0; i < C1.size(); i++)
        {
            columError.at(j)+= 1-relationMatrix[C1[i]][C2[j]];
        }
        if(columError.at(j)==0)
        {
            errorColDominant = 0;
            return errorColDominant;
        }
        if (columError.at(j)<errorColDominant)
            errorColDominant = columError.at(j);
    }
    return errorColDominant;
}

int BlockError::rowDominant(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    vector<int> lineError;
    int errorRowDominant = (int) (C1.size() * C2.size());
    for (int i = 0; i < C1.size(); i++)
    {
        lineError.push_back(0);
        for (int j = 0; j < C2.size(); j++)
            lineError.at(i) += 1-relationMatrix[C1[i]][C2[j]];
        if (lineError.at(i) ==0)
        {
            errorRowDominant = 0;
            return errorRowDominant;
        }
        if (lineError.at(i)<errorRowDominant)
            errorRowDominant = lineError.at(i);
    }
    return errorRowDominant;
}

int BlockError::rowRegular(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    vector<int> rowRegularLineError;
    
    int errorRowRegular = 0;
    
    for (int i = 0; i < C1.size(); i++)
    {
        rowRegularLineError.push_back(0);
        
        for (int j = 0; j < C2.size(); j++)
            rowRegularLineError.at(i)+= relationMatrix[C1[i]][C2[j]];
        
        if ( rowRegularLineError.at(i) == 0 && C2.size()!=0)
            errorRowRegular +=1;
    }
    return errorRowRegular;
}

int BlockError::colRegular(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    vector<int> colRegularLineError;
    int errorColRegular = 0;
    for (int j = 0; j < C2.size(); j++)
    {
        colRegularLineError.push_back(0);
        
        for (int i = 0; i < C1.size(); i++)
            colRegularLineError.at(j)+= relationMatrix[C1[i]][C2[j]];
        
        if ( colRegularLineError.at(j) == 0 && C1.size()!=0)
            errorColRegular +=1;
    }
    return errorColRegular;
}


