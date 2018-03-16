//
//  SetParameters.cpp
//  GBlockModeling - current
//
//  Created by Micheli Knechtel on 02/09/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Parameters.hpp"
#include "PrintManager.hpp"

void Parameters::loadingFromCommandLine(int argc, char **argv)
{
    for (int i = 0; i<argc; i++)
    {
        string strAux = argv[i];
        
        loadSharedInput(strAux, argv, i);
        loadHeuristicInput(strAux, argv, i);
        loadModelInput(strAux, argv, i);
    }
    
    checkSharedInput();
    
    if (heuristic)
        checkHeuristicInput();
    
    if (model)
        checkModelInput();
    
    if (model || heuristic)
        DataManager::getDataManager()->loadingData();
    else
    {
        cout << "Nothing to do: -model and -heuristic OFF or not specified..."<<endl;
        exit(1);
    }
    PrintManager().report();
}

void Parameters::loadSharedInput(string strAux, char **argv, int i)
{
    if (strAux.compare("-directory")==0)
        directory = argv[++i];
    
    if (strAux.compare("-relationMatrix")==0)
        relationMatrix = argv[++i];
    
    if (strAux.compare("-idealBlock")==0)
        idealBlock = argv[++i];
    
    if (strAux.compare("-matrixDataType") == 0)
    {
        string aux =string(argv[++i]);
        if (aux.compare("EDGES")== 0)
            matrixDataType = EDGES;
        
        if (aux.compare("BINARY")== 0)
            matrixDataType = BINARY;
        
        if (aux.compare("XML")== 0)
            matrixDataType = XML;
    }
    
    if (strAux.compare("-clusterUpperBound") == 0)
        clusterUpperBound = atoi(argv[++i]);
    
    if (strAux.compare("-heuristic")==0)
        heuristic = string(argv[++i]).compare("TRUE")== 0 ? true: false;
    
    if (strAux.compare("-model")==0)
        model = string(argv[++i]).compare("TRUE")== 0 ? true: false;
}

void Parameters::loadHeuristicInput(string strAux, char **argv, int i)
{
    if (strAux.compare("-executionOrder")==0)
        sequence = string(argv[++i]).compare("SEQUENTIAL")== 0 ? SEQUENTIAL: RANDOM;
    
    if (strAux.compare("-executionTime")==0)
        executionTime = atof(argv[++i]);
    
    if (strAux.compare("-log")==0)
        log = string(argv[++i]).compare("TRUE")== 0 ? true: false;
    
    if (strAux.compare("-optimizedCode")==0)
        optimizedCode = string(argv[++i]).compare("TRUE")== 0 ? true: false;
    
    if (strAux.compare("-strategy")==0)
        strategy = string(argv[++i]).compare("BEST_SOLUTION")== 0 ? BEST_SOLUTION: FIRST_EQUAL_OR_BEST_SOLUTION;
    
    if (strAux.compare("-numRootPartitions")==0)
        numRootPartitions = atoi(argv[++i]);
    
    if (strAux.compare("-datacheck")==0)
        datacheck = string(argv[++i]).compare("TRUE")== 0 ? true: false;
    
    if (strAux.compare("-predefinedPartition")==0)
        predefinedPartition = argv[++i];
    
    if (strAux.compare("-partitionCheck_01")==0)
        partitionCheck_01 = argv[++i];
    
    if (strAux.compare("-partitionCheck_02")==0)
        partitionCheck_02 = argv[++i];
}

void Parameters::loadModelInput(string strAux, char **argv, int i)
{
    if (strAux.compare("-modelName")==0)
        modelName = argv[++i];
    
    if (strAux.compare("-preProcessingMode") == 0)
        preProcessingMode = string(argv[++i]).compare("TRUE")== 0 ? true: false;
    
    if (strAux.compare("-emtyCluster") == 0)
        emptyCluster = string(argv[++i]).compare("TRUE")== 0 ? true: false;
    
    if (strAux.compare("-AdditionalConstraint") == 0)
        AdditionalConstraint = string(argv[++i]).compare("TRUE")== 0 ? true: false;
}

void Parameters::checkSharedInput()
{
    
    if (directory.compare("")==0)
    {
        cout << "Error: -directory not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->setDirectorie(directory);
    
    if (relationMatrix.compare("")==0)
    {
        cout << "Error: -relationMatrix not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->setFileRelationMatrix(relationMatrix);
    
    if (idealBlock.compare("")==0)
    {
        cout << "Error: -idealBlock not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->setfileFunctionTable(idealBlock);
    
    if (matrixDataType == UNKNOW)
    {
        cout << "Error: -matrixDataType not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->setMatrixDataType(matrixDataType);
    
    if (clusterUpperBound == -1)
    {
        cout << "Error: -clusterUpperBound not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->clusterUpperBound = clusterUpperBound;
    
    DataManager::getDataManager()->heuristic = heuristic;
    DataManager::getDataManager()->model = model;
}

void Parameters::checkHeuristicInput()
{
    DataManager::getDataManager()->sequence = sequence;
    
    if(executionTime == 0)
    {
        cout << "Error: -executionTime not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->executionTime = executionTime;
    
    DataManager::getDataManager()->logLevel = log;
    DataManager::getDataManager()->optimizedCode = optimizedCode;
    DataManager::getDataManager()->heuristicStrategy = strategy;
    
    if(numRootPartitions == 0)
    {
        cout << "Error: -numRootPartitions not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->numRootPartitions = numRootPartitions;
    
    if(datacheck)
    {
        DataManager::getDataManager()->logLevel = false;
    }
    
    DataManager::getDataManager()->datacheck = datacheck;
    
    
    if (predefinedPartition.compare("")==0)
    {
        cout << "Error: -predefinedPartition not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->predefinedPartition = predefinedPartition;
    
    if (partitionCheck_01.compare("")==0)
    {
        cout << "Error: -partitionCheck_01 not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->partitionCheck_01 = partitionCheck_01;
    
    if (partitionCheck_02.compare("")==0)
    {
        cout << "Error: -partitionCheck_02 not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->partitionCheck_02 = partitionCheck_02;
}


void Parameters::checkModelInput()
{
    if (modelName.compare("")==0)
    {
        cout << "Error: -modelName not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->setFileModelName(modelName);
    
    DataManager::getDataManager()->emptyCluster = emptyCluster;
    DataManager::getDataManager()->enablePreprocessing(preProcessingMode);
    DataManager::getDataManager()->setAdditionalConstraint(AdditionalConstraint);
}


void Parameters::predefinedParameters()
{
    DataManager::getDataManager()->setDirectorie("/Users/micheliknechtel/Documents/xCode/GGBlockModeling/tesr/");
    DataManager::getDataManager()->setFileRelationMatrix("networks/binary/NW_RD_02");
    DataManager::getDataManager()->setMatrixDataType(BINARY);
    
//    DataManager::getDataManager()->setDirectorie("/Users/micheliknechtel/Documents/xCode/GGBlockModeling/tesr/");
//    DataManager::getDataManager()->setFileRelationMatrix("networks/label/survey_numeric_before_edge_list.txt");
//    DataManager::getDataManager()->setMatrixDataType(LABEL);
    
    DataManager::getDataManager()->setfileFunctionTable("idealBlock/FM_06");
  
    DataManager::getDataManager()->heuristic = true;
    DataManager::getDataManager()->model = true;
    
    DataManager::getDataManager()->predefinedPartition = "predefinedPartions/predefinedPartition_01";
    DataManager::getDataManager()->partitionCheck_01 = "partitionCheck_01";
    DataManager::getDataManager()->partitionCheck_02 = "partitionCheck_02";
    
    DataManager::getDataManager()->loadingData();
    DataManager::getDataManager()->executionTime = 3600;
    DataManager::getDataManager()->sequence = RANDOM;
    DataManager::getDataManager()->logLevel = true;
    DataManager::getDataManager()->optimizedCode = false;
    DataManager::getDataManager()->datacheck = false;
    DataManager::getDataManager()->heuristicStrategy = FIRST_EQUAL_OR_BEST_SOLUTION;
    DataManager::getDataManager()->numRootPartitions = DataManager::getDataManager()->networkSize;
    DataManager::getDataManager()->emptyCluster = false;
    DataManager::getDataManager()->clusterUpperBound = 6;
    PrintManager().report();
}

// wc -l *.cpp *.hpp
