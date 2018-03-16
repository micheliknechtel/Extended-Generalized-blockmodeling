//
//  PrintManager.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef PrintManager_hpp
#define PrintManager_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include "DataManager.hpp"
#include "DataControler.hpp"
using namespace std;

class PrintManager {
    bool logLevel =  DataManager::getDataManager()->logLevel;
    int **relationMatrix = DataManager::getDataManager()->relationMatrix;
public:
    void printSwap(int clusterA, int nodeA,int clusterB, int nodeB);

    void printBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    void printPartition(map<int,vector<int>>partition);
    void printMatrixBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    void printMatrixBlock(map<int,vector<int>>partition);
    void printMatrixBlockEnd(map<int,vector<int>>partition);
    void printMove(int cluster, int node);
    void printFitness(map<int,vector<int>>partition, map<pair<int,int>, MatchingError> imageMatrix, DataControler *d);
    void swapHeader( int partitionNumber,DataControler *d);
    void moveHeader( int partitionNumber, DataControler *d);
    void errorHeader(int error);
    void newPartition(int partitionNumber, int error, int clusterSize);
    void solution(DataControler *d, time_t time);
    void sharedParameters();
    void heuristicParameters();
    void modelParameters();
    void newLine();
    void inputData();
    void report();
    void choosenPartition(int partitionNumber, int error, int clusterSize);
    void printTime( time_t currentTime);
};

#endif /* PrintManager_hpp */
