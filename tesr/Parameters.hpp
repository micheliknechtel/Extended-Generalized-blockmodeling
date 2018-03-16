//
//  SetParameters.hpp
//  GBlockModeling - current
//
//  Created by Micheli Knechtel on 02/09/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef SetParameters_hpp
#define SetParameters_hpp

#include <stdio.h>
#include "DataManager.hpp"
class Parameters {
    
    string directory;
    string relationMatrix;
    string idealBlock;
    bool model = false;
    bool heuristic = false;
    MatrixDataType matrixDataType = UNKNOW;
    int clusterUpperBound = -1;
    
    executionSequence sequence;
    double executionTime = 0;
    bool log = false;
    bool optimizedCode = false;
    HeuristicStrategy  strategy;
    int numRootPartitions = -1;
    bool datacheck;
    string predefinedPartition;
    string partitionCheck_01;
    string partitionCheck_02;
    
    string  modelName;
    bool emptyCluster = false;
    bool preProcessingMode = true;
    bool AdditionalConstraint = false;
    
public:
    void loadingFromCommandLine(int argc, char **argv);
    void predefinedParameters();
    void loadSharedInput(string strAux, char **argv, int i);
    void loadHeuristicInput(string strAux, char **argv, int i);
    void loadModelInput(string strAux, char **argv, int i);
    void checkSharedInput();
    void checkHeuristicInput();
    void checkModelInput();
};

#endif /* SetParameters_hpp */
