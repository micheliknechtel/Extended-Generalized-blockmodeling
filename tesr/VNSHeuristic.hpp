//
//  VNSHeuristic.hpp
//  GBlockModeling - current
//
//  Created by Micheli Knechtel on 11/12/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

// igor.machado@gmail.com
// vncoelho@gmail.com

#ifndef VNSHeuristic_hpp
#define VNSHeuristic_hpp

#include <stdio.h>
#include "Definitions.h"
#include <map>
#include <vector>
#include "DataControler.hpp"
#include "PartitionErrorFactory.hpp"
#include "DataManager.hpp"
#include "Sequence.hpp"

class VNSHeuristic
{
    int clusterLowerBound = DataManager::getDataManager()->clusterLowerBound;
    int clusterUpperBound = DataManager::getDataManager()->clusterUpperBound;
    int networkSize       = DataManager::getDataManager()->networkSize;
    int numRootPartitions = DataManager::getDataManager()->numRootPartitions;
    int ** relationMatrix = DataManager::getDataManager()->relationMatrix;
    bool optimizedCode    = DataManager::getDataManager()->optimizedCode;
    HeuristicStrategy heuristicStrategy = DataManager::getDataManager()->heuristicStrategy;
    executionSequence sequence;
    PartitionErrorBase *p = PartitionErrorFactory::getPartitionErrorFactory()->newErrorObject(optimizedCode);
    vector<int> clusterSize = DataManager::getDataManager()->sequence == SEQUENTIAL ? Sequence().sequential():Sequence().random();
    double executionTime = DataManager::getDataManager()->executionTime;
    double currentTime = 0;
    int partitionNumber = 0;
    time_t startTime = time(&startTime);
    bool bImprove  = true;
public:
    void chooseBestPartitian(DataControler *d);
    void runVNSHeuristic();
    int chooseClusterSize();
    void move(DataControler *d);
    void swap(DataControler *dataControler);
    void movePositions(DataControler *d);
    void swapPositions(DataControler *d);
    void updateError(int currentError, DataControler *d);
    };
    
    
#endif /* VNSHeuristic_hpp */
