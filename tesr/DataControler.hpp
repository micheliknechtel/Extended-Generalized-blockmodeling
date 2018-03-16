//
//  DataControler.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef DataControler_hpp
#define DataControler_hpp

#include <stdio.h>
#include "Definitions.h"
#include <map>
#include <vector>
#include "BlockError.hpp"
#include <algorithm>
typedef int (BlockError::*ptrFunc)(int,int,map<int,vector<int>>);

struct MatchingError
{
    ptrFunc idealBlockMatching;
    int blockError;
};

class DataControler
{
    
    vector<map<int,vector<int>>> seeds;
    vector<map<int,vector<int>>> solutions;
    vector<map<pair<int,int>,MatchingError>> fitnness;
    vector<int> executionOrder;
    vector<int> desviationMeasure;
    
    map<pair<int,int>, MatchingError> imageMatrix;
    map<int,vector<int>> bestPartition;
    map<int,int> bestNodeToCluster;
    
    int minGlobalError;
    int networkSize;
    int node;
public:
    map<int,int> initialNodeToCluster;
    map<int,int> nodeSolution;
    int desviation;
    map<int,vector<int>> solution;
    map<pair<int,int>, MatchingError> bestfitnness ;
    void loadPartitionFromAnotherDataControler(DataControler *dataControlerAux);
    void loadPartitionFromAnotherDataControler2(DataControler *dataControlerAux);
    map<string, int>functionIndex;
    map<int,vector<int>> initialPartition;
    map<int,int> nodeToCluster;
    map<int,vector<int>> currentPartition;
    map<pair<int,int>, MatchingError> bestImageMatrix;
    map<pair<int,int>, MatchingError> imageMatrixSeed;
   
    vector<map<pair<int,int>,MatchingError>> allFunctionsImageMatrix;
    vector<vector<vector<ptrFunc>>>idealBlockSetupMatrix;
    
    HeuristicStrategy heuristicStrategy;

    int clusterSource;
    int clusterTarget;
    
    DataControler();
    
    string typeToFunction(ptrFunc idealBlock);
    int getNode();
    int getMinGlobalError();
    int getClusterSourceNode();
    
    void setAfectedRelations(int clusterSource, int clusterTarget);
    void buildPartitian(int clusterSize);
    void loadPartitian();
    void loadPartitians();
    void setBestNodeToCluster(map<int,int> bestNodeToCluster);
    void matchingFunctionType(vector<ptrFunc>& idealBlockSetupVector, FunctionType type);
    void initAllImageMatrix();
    void loadExecutionOrder();
    void setMinGlobalError(int minGlobalError);
    void setNode(int node);
    void setImageMatrix(map<pair<int,int>, MatchingError> imageMatrix);
    void updateDataStructure();
    void setBestPartition(map<int,vector<int>> bestPartition);
    void imageMatrixRemove(int cluster_k, int cluster_l);
    void loadCurrentPartition();
    void loadCurrentStructures();
    void imageMatrixInsert(pair<int,int> key, MatchingError value);
    void addNodeToCluster(int cluster, int node);
    void deleteNode( map<int,vector<int>> &partition, int clusterIndex, int node);
    void addNewCluster();
    void addNodeToCluster(int cluster, int node, int position);
    void initializeAllFunctionsImageMatrix();
    void buildingFunctionIndexStructure();
    
    vector<int> getExecutionOrder();
    vector<int> getDesviationMeasure();
    vector<vector<vector<ptrFunc>>> loadIdealBlocks();
    vector<map<int,vector<int>>> getSeeds();
    vector<map<int,vector<int>>> getSolutions();

    map<int,vector<int>> getInitialPartition();
    map<int,vector<int>> getBestPartition();
    map<int,int> getInitialNodeToCluster();
    map<int,int> getBestNodeToCluster();
    map<pair<int,int>, MatchingError> getImageMatrix();
    
    bool checkUpErrorSource(int cluster_k, int cluster_l);
    bool checkUpErrorTarget(int cluster_k, int cluster_l);

};


#endif /* DataControler_hpp */
