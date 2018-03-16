//
//  PartitionError.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "PartitionError.hpp"
#include "PrintManager.hpp"
#include "DataControler.hpp"

int PartitionError::calcErrorForAllRelations(DataControler *d)
{
    vector<vector<vector<ptrFunc>>> idealBlockSetupMatrix = d->idealBlockSetupMatrix;
    map<int,vector<int>>partition = d->getInitialPartition();
    map<pair<int,int>, MatchingError> imageMatrix;
    int minBlockError = 0, partitionError = 0;
    
    for (int cluster_k = 0; cluster_k<partition.size(); cluster_k++)
    {
        for (int cluster_l = 0; cluster_l<partition.size(); cluster_l++)
        {
            MatchingError bestBlockFitness;
            minBlockError = (int)(partition.at(cluster_k).size() * partition.at(cluster_l).size())*2+1 ;
            int size = (int) idealBlockSetupMatrix.at(cluster_k).at(cluster_l).size();

            for (int m = 0; m <size; m++)
            {
                MatchingError block;
                block.idealBlockMatching = idealBlockSetupMatrix.at(cluster_k).at(cluster_l).at(m);
                block.blockError = (BlockError().*block.idealBlockMatching)(cluster_k, cluster_l, partition);
               
                if ( block.blockError == 0)
                {
                    minBlockError = 0;
                    bestBlockFitness.blockError = block.blockError;
                    bestBlockFitness.idealBlockMatching = block.idealBlockMatching;
                    break;
                }
                if ( block.blockError < minBlockError)
                {
                    minBlockError =  block.blockError;
                    bestBlockFitness.blockError = block.blockError;
                    bestBlockFitness.idealBlockMatching = block.idealBlockMatching;
                }
            }
            imageMatrix.insert(pair<pair<int,int>, MatchingError> (pair<int,int>(cluster_k, cluster_l), bestBlockFitness));
            partitionError += minBlockError;
            minBlockError = 0;
        }
    }
    d->setImageMatrix(imageMatrix);
    PrintManager().errorHeader(partitionError);
    PrintManager().printPartition(partition);
//    PrintManager().printFitness(partition, d->getImageMatrix(), d);
//    PrintManager().printMatrixBlock(partition);
    return partitionError;
}


void PartitionError::error(DataControler *d, int cluster_k, int cluster_l)
{
    MatchingError bestBlockFitness;
    
    int minBlockError = (int)(d->currentPartition.at(cluster_k).size() * d->currentPartition.at(cluster_l).size()) * 2 +1 ;
    int size = (int) d->idealBlockSetupMatrix.at(cluster_k).at(cluster_l).size();
    
    for (int m = 0; m <size; m++)
    {
        MatchingError block;
        block.idealBlockMatching = d->idealBlockSetupMatrix.at(cluster_k).at(cluster_l).at(m);
        block.blockError = (BlockError().*block.idealBlockMatching)(cluster_k, cluster_l, d->currentPartition);
        
        if ( block.blockError == 0)
        {
            minBlockError = 0;
            bestBlockFitness.blockError = block.blockError;
            bestBlockFitness.idealBlockMatching = block.idealBlockMatching;
            break;
        }
        if ( block.blockError < minBlockError)
        {
            minBlockError =  block.blockError;
            bestBlockFitness.blockError = block.blockError;
            bestBlockFitness.idealBlockMatching = block.idealBlockMatching;
        }

    }
    d->imageMatrixRemove(cluster_k, cluster_l);
    d->imageMatrixInsert(pair<int,int>(cluster_k, cluster_l), bestBlockFitness);
}

int PartitionError::calcErrorOnlyAfectedRelations(DataControler *d)
{
    d->setImageMatrix(d->imageMatrixSeed);
    
    int partitionError = 0;
    
    for (int cluster_l = 0; cluster_l<d->currentPartition.size(); cluster_l++)
    {
        error(d, d->clusterSource, cluster_l);
        error(d, cluster_l, d->clusterSource);
        
        error(d, d->clusterTarget, cluster_l);
        error(d, cluster_l, d->clusterTarget);
    }
    
    map<pair<int,int>, MatchingError> imageMatrix = d->getImageMatrix();
    for (map<pair<int,int>, MatchingError>::iterator it = imageMatrix.begin(); it!=imageMatrix.end(); it++)
    {
        partitionError += it->second.blockError;
    }
    PrintManager().errorHeader(partitionError);
    PrintManager().printPartition(d->currentPartition);
//    PrintManager().printFitness(d->currentPartition,imageMatrix, d);
//    PrintManager().printMatrixBlock(d->currentPartition);
    
    return partitionError;
}

void PartitionError::updateError(int currentError, DataControler *d)
{    
    if (currentError < d->getMinGlobalError())
    {
        d->setMinGlobalError(currentError);
        d->setBestNodeToCluster(d->nodeToCluster);
        d->setBestPartition(d->currentPartition);
        d->bestImageMatrix =  d->getImageMatrix();
    }
    
    if(d->heuristicStrategy == FIRST_EQUAL_OR_BEST_SOLUTION)
        if ( currentError == d->getMinGlobalError())
        {
            d->setMinGlobalError(currentError);
            d->setBestNodeToCluster(d->getInitialNodeToCluster());
            d->setBestPartition(d->currentPartition);
            d->bestImageMatrix = d->getImageMatrix();
        }
    
    if(currentError == 0)
        throw 1;
}
