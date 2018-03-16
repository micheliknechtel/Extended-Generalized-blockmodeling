//
//  DataManager.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef DataManager_hpp
#define DataManager_hpp
#include <iostream>
#include <fstream>
#include "Definitions.h"
#include <stdio.h>
#include <map>
#include "Graph.hpp"
#include "Preprocessing.hpp"
#include <vector>
#include "DataControler.hpp"

class DataManager
{
    static DataManager *dataManager;
public:

    static DataManager* getDataManager();
    int clusterUpperBound;
    int currentfDetails = -1;
    int networkSize;
    int functionSize;
    int clusterLowerBound;
    int verticeLabelMaxSize = 0;
    int ** relationMatrix;
    
    double executionTime;
    bool datacheck = false;
    bool emptyCluster = false;
    bool logLevel = false;
    bool heuristic = false;
    bool model = false;
    bool symmetricProperty = false;
    bool addAdditionalConstraint = false;
    bool preProcessingMode = true;
    void setAdditionalConstraint(bool addAdditionalConstraint);
    MatrixDataType matrixDataType;
    DataControler *xSolution;
    
    map<string,string> nodeID2Name;
    map<string,int> ID2Index;
    map<int,string> index2ID;
    map<pair<int,int>, double> edge;
    
    FunctionRelease releaseNullBlock;
    FunctionRelease releaseCompleteBlock;
    FunctionRelease releaseColumnDominantBlock;
    FunctionRelease releaseRowDominantBlock;
    FunctionRelease releaseRegularBlock;
    FunctionRelease releaseFunctionalBlock;
   
    Graph *graph;
    void readRelationMatrixFromXML();
    void createGraph();
    void readFunctionTable();
    void loadingData();
    
    bool getAdditionalConstraint();
    
    void setCurrentfDetailsSharedVariable(FunctionRelease release);
    string upperCase(string str);
    FunctionDetails getCurrentfDetails();    
    vector<FunctionDetails> functionMapping;
    FunctionDetails FDetails(string name, string release);
    FunctionType getType(string name);
    FunctionDetails getfDetails(FunctionType type);
   
    void setCurrentfDetails(int index);
    void printFunctionTable();
    void readRelationMatrixTwo();
    void readRelationMatrixOne();
    void printRelationMatrix();
    void readRelationMatrixLabeling();
    
    void setfileFunctionTable(string fileFunctionTable);
    void setFileRelationMatrix(string fileRelationMatrix);
    void setDirectorie(string directoriePath);
    void setFileModelName(string modelName);
    void setMatrixDataType(MatrixDataType type);
    string getModelLocation();
    bool isTypeAdded(FunctionType type);

    string modelName = "model_01";
    string directoriePath;
    string predefinedPartition;
    string partitionCheck_01;
    string partitionCheck_02;
    string fileRelationMatrix;
    string fileFunctionTable;

    bool areThereBlockWithDiagonalVariationZero();
    bool areThereBlockWithDiagonalVariationOne();
    bool isItNonSymmetricPropertie(string name);
    bool areThereNonSymmetricPropertie();
    
    void enablePreprocessing(bool preProcessingMode);
    void getMatrixRelease(vector<FunctionType> &diagonalRelease, vector<FunctionType> &offDiagonalRelease);
    FunctionRelease getBlockRelease(FunctionType type_01, FunctionType type_02 = UNDEFINED, FunctionType type_03 = UNDEFINED);
    string getMatrixDataType();
    void adjustingFunctionProperties();
    bool optimizedCode;
    HeuristicStrategy heuristicStrategy;
    executionSequence sequence;
    int numRootPartitions;
    HeuristicStrategy getHeuristicStrategy();
    string getHeuristicStrategyTexte();
};

#endif /* DataManager_hpp */
