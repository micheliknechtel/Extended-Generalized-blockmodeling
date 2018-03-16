////
//  VNSHeuristic.cpp
//  GBlockModeling - current
//
//  Created by Micheli Knechtel on 11/12/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "VNSHeuristic.hpp"
#include <cmath>
#include "Definitions.h"

#include <stdlib.h>
#include "PrintManager.hpp"
#include "PartitionErrorOtimized.hpp"
#include "DataEvaluetor.hpp"

void VNSHeuristic::runVNSHeuristic()
{
    if(DataManager::getDataManager()->datacheck)
        DataEvaluetor().prepareData();
    
    
    DataControler *dataControler = new DataControler();

    // <predefined stuff
//    dataControler->loadPartitian();
//    dataControler->setMinGlobalError(p->calcErrorForAllRelations(dataControler));
//    dataControler->initAllImageMatrix();
//    dataControler->updateDataStructure();
//    DataManager::getDataManager()->xSolution = dataControler;
//    return ;
    // predefined stuff>
    
    dataControler->buildPartitian(DataManager::getDataManager()->networkSize);
    chooseBestPartitian(dataControler);
    PrintManager().printTime(startTime);
    dataControler->updateDataStructure();
    
    while(bImprove && (executionTime>currentTime) && numRootPartitions>partitionNumber)
    {
        try
        {
            move(dataControler);
            swap(dataControler);
            PrintManager().newLine();
        }
        catch (...)
        {
            bImprove = false;
            dataControler->updateDataStructure();
        }
        
        partitionNumber++;
        
        if (bImprove && numRootPartitions>partitionNumber)
        {
            
            chooseBestPartitian(dataControler);
            dataControler->updateDataStructure();
            PrintManager().printTime(startTime);
        }
    }
    
    if(DataManager::getDataManager()->datacheck)
        DataEvaluetor().processingData(dataControler);


    PrintManager().solution(dataControler, startTime);
  
    DataManager::getDataManager()->xSolution = dataControler;
}

void VNSHeuristic::chooseBestPartitian(DataControler *d)
{
    DataControler *dAux = new DataControler();
    int bestPartitionNumber = 0;
    int currentError;
    int error = networkSize * networkSize *2;
    int index = 0;

    while (bImprove && index< clusterSize.size())
    {
        try
        {
            if (clusterSize[index]== 1|| clusterSize[index]== networkSize)
            {
                clusterSize.erase(clusterSize.begin()+index);
                continue;
            }

            dAux->buildPartitian(clusterSize[index]);
            dAux->setMinGlobalError(p->calcErrorForAllRelations(dAux));
            
            currentError = dAux->getMinGlobalError();
            if(currentError<=error)
            {
                d->loadPartitionFromAnotherDataControler(dAux);
                bestPartitionNumber = index;
                error = dAux->getMinGlobalError();
                
            }
            if(currentError==0)
                 throw 1;
                
            index++;
        }
        catch (...)
        {
            bImprove = false;
            bestPartitionNumber = index;
        }
    }
    if (clusterSize.size()==0)
    {
        bImprove = false;
        return;
    }
    clusterSize.erase(clusterSize.begin() + bestPartitionNumber);
    PrintManager().choosenPartition(partitionNumber, d->getMinGlobalError(), (int) d->getInitialPartition().size());
}

void VNSHeuristic::move(DataControler *d)
{
    
    d->loadExecutionOrder();
    
    for(int node = 0; node <networkSize; node++)
    {
        d->setNode(node);
        movePositions(d);
        d->updateDataStructure();
        
        if (optimizedCode)
            p->calcErrorForAllRelations(d);
    }
    PrintManager().moveHeader(partitionNumber, d);
    PrintManager().printTime(startTime);
}

void VNSHeuristic::swap(DataControler *d)
{
    d->loadExecutionOrder();
    swapPositions(d);
    d->updateDataStructure();
    PrintManager().swapHeader(partitionNumber, d);
    PrintManager().printTime(startTime);
}

void VNSHeuristic::swapPositions(DataControler *d)
{
    d->loadCurrentStructures();
    
    for (int clusterIndexA = 0; clusterIndexA<d->currentPartition.size()-1; clusterIndexA++)
    {
        for (int clusterIndexB = clusterIndexA+1; clusterIndexB<d->currentPartition.size(); clusterIndexB++)
        {
            for (int l = 0; l<d->currentPartition.at(clusterIndexA).size(); l++)
            {
                
                int nodeA = d->currentPartition.at(clusterIndexA).at(l);
                d->deleteNode(d->currentPartition, clusterIndexA, nodeA);
                d->addNodeToCluster(clusterIndexB, nodeA);
                
                for (int k = 0; k< d->currentPartition.at(clusterIndexB).size()-1; k++)
                {
                    int nodeB = d->currentPartition.at(clusterIndexB).at(k);
                    d->deleteNode(d->currentPartition, clusterIndexB, nodeB);
                    d->addNodeToCluster(clusterIndexA, nodeB);
                    d->setAfectedRelations(clusterIndexA, clusterIndexB);
                    PrintManager().printSwap(clusterIndexA, nodeA, clusterIndexB, nodeB);
                    updateError(p->calcErrorNewCluster(d), d);
                    d->deleteNode(d->currentPartition, clusterIndexA, nodeB);
                    d->addNodeToCluster(clusterIndexB, nodeB, k);
                }
                
                d->deleteNode(d->currentPartition, clusterIndexB, nodeA);
                d->addNodeToCluster(clusterIndexA, nodeA,  l);
            }
        }
    }
}

void VNSHeuristic::movePositions(DataControler *d)
{
    int clusterSource = d->getClusterSourceNode();
    d->loadCurrentStructures();
    d->deleteNode(d->currentPartition, clusterSource, d->getNode());
    
    for (int clusterTarget = 0; clusterTarget<d->currentPartition.size(); clusterTarget++)
    {
        if (clusterTarget != clusterSource)
        {
            PrintManager().printMove(clusterTarget, d->getNode());
            d->setAfectedRelations(clusterSource, clusterTarget);
            d->addNodeToCluster(clusterTarget, d->getNode());
            updateError(p->calcErrorOnlyAfectedRelations(d), d);
            d->deleteNode(d->currentPartition, clusterTarget, d->getNode());
        }
    }
    if ((d->currentPartition.at(clusterSource).size()>1 || d->currentPartition.at(clusterSource).size()==1) && d->currentPartition.size()<networkSize-1)
    {
        PrintManager().printMove((int)d->currentPartition.size(), d->getNode());
        d->addNewCluster();
        d->setAfectedRelations(clusterSource, (int)d->currentPartition.size()-1);
        
        if (optimizedCode)
            updateError(p->calcErrorNewCluster(d), d);
        else
            updateError(p->calcErrorOnlyAfectedRelations(d), d);
    }
}


void VNSHeuristic::updateError(int currentError, DataControler *d)
{
    if(heuristicStrategy == FIRST_EQUAL_OR_BEST_SOLUTION)
    {
        if(currentError == d->getMinGlobalError() || currentError < d->getMinGlobalError())
        {
            d->setBestNodeToCluster(d->nodeToCluster);
            d->setBestPartition(d->currentPartition);
            d->bestImageMatrix = d->getImageMatrix();
            d->setMinGlobalError(currentError);
        }
    }
    else if(currentError < d->getMinGlobalError())
    {
        d->setMinGlobalError(currentError);
        d->setBestNodeToCluster(d->nodeToCluster);
        d->setBestPartition(d->currentPartition);
        d->bestImageMatrix =  d->getImageMatrix();
    }
    
    if(currentError == 0)
        throw 1;
}

int VNSHeuristic::chooseClusterSize()
{
    return (networkSize - clusterLowerBound) > ( networkSize - clusterUpperBound)?clusterLowerBound:clusterUpperBound;
};



