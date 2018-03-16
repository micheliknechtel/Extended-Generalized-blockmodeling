//
//  PartitionErrorOtimized.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/03/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "PartitionErrorOtimized.hpp"
#include "PrintManager.hpp"
#include "DataControler.hpp"

int PartitionErrorOtimized::calcErrorForAllRelations(DataControler *d)
{
    vector<vector<vector<ptrFunc>>> idealBlockSetupMatrix = d->idealBlockSetupMatrix;
    map<int,vector<int>>partition = d->getInitialPartition();
    map<pair<int,int>, MatchingError> imageMatrix;
    int minBlockError = 0, partitionError = 0;
    
    d->initializeAllFunctionsImageMatrix();
    
    for (int cluster_k = 0; cluster_k<partition.size(); cluster_k++)
    {
        for (int cluster_l = 0; cluster_l<partition.size(); cluster_l++)
        {
            MatchingError bestBlockFitness;
            minBlockError = (int)(partition.at(cluster_k).size() * partition.at(cluster_l).size()) * 2 + 1 ;
            int size = (int) idealBlockSetupMatrix.at(cluster_k).at(cluster_l).size();
            
            for (int m = 0; m <size; m++)
            {
                MatchingError block;
                block.idealBlockMatching = idealBlockSetupMatrix.at(cluster_k).at(cluster_l)[m];
                block.blockError = (BlockError().*block.idealBlockMatching)(cluster_k, cluster_l, partition);
                
                if ( block.blockError == 0)
                {
                    minBlockError = 0;
                    bestBlockFitness.blockError = block.blockError;
                    bestBlockFitness.idealBlockMatching = block.idealBlockMatching;
                    
                    string str =  d->typeToFunction(block.idealBlockMatching);
                    int index = d->functionIndex.at(str);
                    d->allFunctionsImageMatrix.at(index).insert(pair<pair<int,int>, MatchingError> (pair<int,int>(cluster_k, cluster_l), block));
                    
                    break;
                }
                if ( block.blockError < minBlockError)
                {
                    minBlockError =  block.blockError;
                    bestBlockFitness.blockError = block.blockError;
                    bestBlockFitness.idealBlockMatching = block.idealBlockMatching;
                }
                
                string str =  d->typeToFunction(block.idealBlockMatching);
                int index = d->functionIndex.at(str);
                d->allFunctionsImageMatrix.at(index).insert(pair<pair<int,int>, MatchingError> (pair<int,int>(cluster_k, cluster_l), block));
            }
            
            imageMatrix.insert(pair<pair<int,int>, MatchingError> (pair<int,int>(cluster_k, cluster_l), bestBlockFitness));
            partitionError += minBlockError;
            minBlockError = 0;
        }
    }
    
    d->setImageMatrix(imageMatrix);
    
    PrintManager().errorHeader(partitionError);
    PrintManager().printPartition(partition);
    PrintManager().printFitness(partition,imageMatrix,d);
    PrintManager().printMatrixBlock(partition);
    
    return partitionError;
}

void PartitionErrorOtimized::allFunctionsError(DataControler *d)
{
    vector<vector<vector<ptrFunc>>> idealBlockSetupMatrix = d->idealBlockSetupMatrix;
    map<int,vector<int>>partition = d->currentPartition;
    
    d->initializeAllFunctionsImageMatrix();
    
    for (int cluster_k = 0; cluster_k<partition.size(); cluster_k++)
    {
        for (int cluster_l = 0; cluster_l<partition.size(); cluster_l++)
        {
            int size = (int) idealBlockSetupMatrix.at(cluster_k).at(cluster_l).size();
            
            for (int m = 0; m <size; m++)
            {
                MatchingError block;
                block.idealBlockMatching = idealBlockSetupMatrix.at(cluster_k).at(cluster_l)[m];
                block.blockError = (BlockError().*block.idealBlockMatching)(cluster_k, cluster_l, partition);
                
                string str =  d->typeToFunction(block.idealBlockMatching);
                int index = d->functionIndex.at(str);
                d->allFunctionsImageMatrix.at(index).insert(pair<pair<int,int>, MatchingError> (pair<int,int>(cluster_k, cluster_l), block));
            }
        }
    }
}

void PartitionErrorOtimized::removeNode(DataControler *d, int cluster_l)
{
    int  clusterSource = d->clusterSource;
    map<int,vector<int>> partition;
    
    if(cluster_l == clusterSource)
    {
        partition.insert(make_pair(clusterSource ,  d->currentPartition.at(cluster_l)));
        if (!d->checkUpErrorSource(clusterSource, cluster_l))
            errorRemove(d, d->clusterSource, cluster_l, partition);
    }
    else
    {
        partition.insert(make_pair(cluster_l,  d->currentPartition.at(cluster_l)));
        partition.insert(make_pair(clusterSource, d->currentPartition.at(clusterSource)));
        
        if (!d->checkUpErrorSource(clusterSource, cluster_l))
            errorRemove(d, d->clusterSource, cluster_l, partition);
        
        if (!d->checkUpErrorSource(clusterSource, cluster_l))
            errorRemove(d, cluster_l, clusterSource, partition);
    }
}

void PartitionErrorOtimized::addNode(DataControler *d, int cluster_l)
{
    int  clusterTarget = d->clusterTarget;
    map<int,vector<int>> partition;
    
    if(cluster_l == clusterTarget)
    {
        partition.insert(make_pair(clusterTarget ,  d->currentPartition.at(cluster_l)));
        errorRemove(d, d->clusterTarget, cluster_l, partition);
    }
    else
    {
        partition.insert(make_pair(cluster_l, d->currentPartition.at(cluster_l)));
        partition.insert(make_pair(clusterTarget, d->currentPartition.at(clusterTarget)));
        
        if (!d->checkUpErrorSource(clusterTarget, cluster_l))
            errorRemove(d, clusterTarget, cluster_l, partition);
        
        if (!d->checkUpErrorSource(cluster_l, clusterTarget))
            errorRemove(d, cluster_l, clusterTarget, partition);
    }
}


void PartitionErrorOtimized::insertNode(DataControler *d, int cluster_l)
{
    int  clusterTarget = d->clusterTarget;
    
    map<int,vector<int>> insertPartition;
    
    vector<int> node;
    node.push_back(d->getNode());
    
    
    if(cluster_l != clusterTarget)
    {
        insertPartition.insert(make_pair(cluster_l, d->currentPartition.at(cluster_l)));
        insertPartition.insert(make_pair(clusterTarget, node));
        
        if (!d->checkUpErrorTarget(clusterTarget, cluster_l))
            errorInsert(d, clusterTarget, cluster_l, insertPartition);
        
        if (!d->checkUpErrorTarget(cluster_l, clusterTarget))
            errorInsert(d, cluster_l,  clusterTarget, insertPartition);
    }
    else
    {
        insertPartition.insert(make_pair(clusterTarget, d->currentPartition.at(clusterTarget)));
        if (!d->checkUpErrorTarget(clusterTarget, cluster_l))
            errorRemove(d, clusterTarget, cluster_l, insertPartition);
    }
}

int PartitionErrorOtimized::calcErrorOnlyAfectedRelations(DataControler *d)
{
    d->setImageMatrix(d->imageMatrixSeed);
    int partitionError = 0;
    
    for (int cluster_l = 0; cluster_l<d->currentPartition.size(); cluster_l++)
    {
        removeNode(d, cluster_l);
        if (d->clusterSource != cluster_l)
            insertNode(d, cluster_l);
        
    }
    
    map<pair<int,int>, MatchingError> imageMatrix = d->getImageMatrix();

    for (map<pair<int,int>, MatchingError>::iterator it = imageMatrix.begin(); it!=imageMatrix.end(); it++)
    {
        if( (d->currentPartition.at(it->first.first).size()*  d->currentPartition.at(it->first.second).size()) ==0)
            continue;
        partitionError += it->second.blockError;
    }
    
    PrintManager().errorHeader(partitionError);
    PrintManager().printPartition(d->currentPartition);
    PrintManager().printMatrixBlock(d->currentPartition);
    PrintManager().printFitness(d->currentPartition,imageMatrix, d);
    return partitionError;
}

int PartitionErrorOtimized::calcErrorNewCluster(DataControler *d)
{
    d->setImageMatrix(d->imageMatrixSeed);
    int partitionError = 0;
    
    for (int cluster_l = 0; cluster_l<d->currentPartition.size(); cluster_l++)
    {
        removeNode(d, cluster_l);
        addNode(d, cluster_l);
    }
    
    map<pair<int,int>, MatchingError> imageMatrix = d->getImageMatrix();
    for (map<pair<int,int>, MatchingError>::iterator it = imageMatrix.begin(); it!=imageMatrix.end(); it++)
    {
        partitionError += it->second.blockError;
    }
    
    PrintManager().errorHeader(partitionError);
    PrintManager().printPartition(d->currentPartition);
    PrintManager().printMatrixBlock(d->currentPartition);
    PrintManager().printFitness(d->currentPartition,imageMatrix,d);
    
    return partitionError;
}

void PartitionErrorOtimized::errorInsert(DataControler *d, int cluster_k, int cluster_l, map<int,vector<int>> currentPartition)
{
    int sizeIM = (int)d->getImageMatrix().size();
    int sizeIP = (int)d->currentPartition.size();
    
    MatchingError bestBlockFitness;
    
    if (sizeIM /sizeIP == sizeIP)
        bestBlockFitness =  d->getImageMatrix().at(pair<int,int>(cluster_k, cluster_l));
    
    int minBlockError = (int)(d->currentPartition.at(cluster_k).size() * d->currentPartition.at(cluster_l).size())  * 2 + 1 ;
    int size = (int) d->idealBlockSetupMatrix.at(cluster_k).at(cluster_l).size();
    
    for (int m = 0; m <size; m++)
    {
        MatchingError block;
        block.idealBlockMatching = d->idealBlockSetupMatrix.at(cluster_k).at(cluster_l)[m];
        
        string str =  d->typeToFunction(block.idealBlockMatching);
        int index = d->functionIndex.at(str);
        
        
        if (str.compare("RB")==0)
        {
            block.blockError = (BlockError().*block.idealBlockMatching)(cluster_k, cluster_l, d->currentPartition);
        }
        else
         block.blockError = (BlockError().*block.idealBlockMatching)(cluster_k, cluster_l, currentPartition);
        
    
        
        if (sizeIM /sizeIP == sizeIP && str.compare("RB")!=0)
        {
            block.blockError+=(d->allFunctionsImageMatrix.at(index)).at(pair<int, int>(cluster_k, cluster_l)).blockError;
        }
        
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


void PartitionErrorOtimized::errorRemove(DataControler *d, int cluster_k, int cluster_l, map<int,vector<int>> currentPartition)
{
    int sizeIM = (int)d->getImageMatrix().size();
    int sizeIP = (int)d->currentPartition.size();
    
    MatchingError bestBlockFitness;
    
    if (sizeIM /sizeIP == sizeIP)
        bestBlockFitness =  d->getImageMatrix().at(pair<int,int>(cluster_k, cluster_l));
    
    int minBlockError = (int)(currentPartition.at(cluster_k).size() * currentPartition.at(cluster_l).size()) * 2 + 1 ;
    int size = (int) d->idealBlockSetupMatrix.at(cluster_k).at(cluster_l).size();
    
    for (int m = 0; m <size; m++)
    {
        MatchingError block;
        block.idealBlockMatching = d->idealBlockSetupMatrix.at(cluster_k).at(cluster_l)[m];
        block.blockError = (BlockError().*block.idealBlockMatching)(cluster_k, cluster_l, currentPartition);
        
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

void PartitionErrorOtimized::updateError(int currentError, DataControler *d)
{
    if (currentError < d->getMinGlobalError())
    {
        d->setMinGlobalError(currentError);
        d->setBestNodeToCluster(d->nodeToCluster);
        d->setBestPartition(d->currentPartition);
        d->bestImageMatrix =  d->getImageMatrix();
        allFunctionsError(d);
    }
    
    if(d->heuristicStrategy == FIRST_EQUAL_OR_BEST_SOLUTION)
        if ( currentError == d->getMinGlobalError())
        {
            d->setMinGlobalError(currentError);
            d->setBestNodeToCluster(d->getInitialNodeToCluster());
            d->setBestPartition(d->currentPartition);
            d->bestImageMatrix = d->getImageMatrix();
            allFunctionsError(d);
        }
    
    if(currentError == 0)
        throw 1;
}
