//
//  DataControler.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "DataControler.hpp"
#include "DataManager.hpp"
#include "Sequence.hpp"
#include "PartitionError.hpp"
#include "PartitionErrorOtimized.hpp"
#include "PartitionErrorFactory.hpp"
#include "PrintManager.hpp"


DataControler::DataControler()
{
    heuristicStrategy = DataManager::getDataManager()->getHeuristicStrategy();
    networkSize = DataManager::getDataManager()->networkSize;
    idealBlockSetupMatrix = loadIdealBlocks();
    desviation = networkSize * networkSize * 2;
    minGlobalError = networkSize * networkSize * 2;
}

void DataControler::buildPartitian(int clusterSize)
{
    initialPartition.clear();
    bestPartition.clear();
    initialNodeToCluster.clear();
    bestNodeToCluster.clear();
    
    int ub ;
    int lb  = 0;
    if (clusterSize == 0)
        clusterSize = networkSize;
    if (clusterSize == 1)
        ub = networkSize;
    else
        ub = rand() % (networkSize/clusterSize) + 1;
    
    vector<int> randomVector = Sequence().random();
    
    for (int clusterIndex = 0; clusterIndex<clusterSize; clusterIndex++)
    {
        vector<int> nodes;
        for (int node = lb; node<ub; node++)
        {
            nodes.push_back(randomVector[node]) ;
            initialNodeToCluster.insert(pair<int, int>(randomVector[node],clusterIndex));
        }
        lb = ub;
        if (clusterIndex == clusterSize-1)
        {
            ub = networkSize;
            initialPartition.insert(pair<int, vector<int>>(clusterIndex,nodes));
            
        }
        else
        {
            int a = (networkSize - ub );
            int b =(clusterSize - (clusterIndex +1));
            ub += a/ b;
            initialPartition.insert(pair<int, vector<int>>(clusterIndex,nodes));
        }
    }
    bestPartition = initialPartition;
    bestNodeToCluster = initialNodeToCluster;
}

void  DataControler::loadPartitian()
{
    string str = DataManager::getDataManager()->directoriePath +  DataManager::getDataManager()->predefinedPartition;
    const char * fin  = str.c_str();
    int clusterIndex = 0;    vector<int> v;
    ifstream file(fin);
    
    initialPartition.clear();
    bestPartition.clear();
    
    initialNodeToCluster.clear();
    bestNodeToCluster.clear();
    
    while (!(file.eof() || file.fail()))
    {
        string buffer;
        file>>buffer;
        
        size_t found = buffer.find('C');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find('=');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find('{');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find(',');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find('}');
        if (found!=std::string::npos)
        {
            initialPartition.insert(pair<int, vector<int>>(clusterIndex,v));
            vector<int> vAux;
            v = vAux;
            clusterIndex++;
            continue;
        }
        
        int node = atoi(buffer.c_str());
        v.push_back(node);
        
        initialNodeToCluster.insert(pair<int, int>(node,clusterIndex));
        bestNodeToCluster.insert(pair<int, int>(node,clusterIndex));
    }
    bestPartition = initialPartition;
    bestNodeToCluster = initialNodeToCluster;
}

void  DataControler::loadPartitians()
{
    string str = DataManager::getDataManager()->directoriePath +  DataManager::getDataManager()->partitionCheck_01;
    
    const char * fin  = str.c_str();
    int clusterIndex = 0;    vector<int> v;
    ifstream file(fin);
    idealBlockSetupMatrix = loadIdealBlocks();
    
    initialPartition.clear();
    bestPartition.clear();
    
    initialNodeToCluster.clear();
    bestNodeToCluster.clear();
    
    
    PartitionErrorBase *partionErrorBase = PartitionErrorFactory::getPartitionErrorFactory()->newErrorObject(false);
    
    while (!(file.eof() || file.fail()))
    {
        string buffer;
        file>>buffer;
        
        size_t found = (unsigned) buffer.find("----------------------------------------------------");
        if (found!=std::string::npos)
        {
            map<pair<int,int>, MatchingError> imageMatrix;
            imageMatrix.clear();
            partionErrorBase->calcErrorForAllRelations(this);
            initialPartition.clear();
            initialNodeToCluster.clear();
            clusterIndex = 0;
            continue;
        }
        found = buffer.find("TOTAL");
        if (found!=std::string::npos)
        {
            file>>buffer;
            file>>buffer;
            file>>buffer;
            continue;
        }
        
        found = buffer.find('C');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find('=');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find('{');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find(',');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find('}');
        if (found!=std::string::npos)
        {
            initialPartition.insert(pair<int, vector<int>>(clusterIndex,v));
            vector<int> vAux;
            v = vAux;
            clusterIndex++;
            continue;
        }
        
        int node = atoi(buffer.c_str());
        v.push_back(node);
        
        initialNodeToCluster.insert(pair<int, int>(node,clusterIndex));
    }
    map<pair<int,int>, MatchingError> imageMatrix;
    partionErrorBase->calcErrorForAllRelations(this);
    exit(1);
}


void DataControler::initializeAllFunctionsImageMatrix()
{
    vector<map<pair<int,int>,MatchingError>> allFunctionsImageMatrix;
    vector<FunctionType> diagonalRelease, offDiagonalRelease;
    
    DataManager::getDataManager()->getMatrixRelease(diagonalRelease, offDiagonalRelease);
    
    int size = (int) diagonalRelease.size() + (int) offDiagonalRelease.size();
    
    this->allFunctionsImageMatrix = allFunctionsImageMatrix;
    
    for (int m = 0; m <size; m++)
    {
        map<pair<int,int>, MatchingError> c;
        this->allFunctionsImageMatrix.push_back(c);
    }
}

void DataControler::buildingFunctionIndexStructure()
{
    vector<FunctionType> diagonalRelease, offDiagonalRelease;
    DataManager::getDataManager()->getMatrixRelease(diagonalRelease, offDiagonalRelease);
    
    // Está mal feito como a minha cara... Favor arrumar :-P
    for (int i= 0 ; i<diagonalRelease.size(); i++)
    {
        string str = fTypeMapping[diagonalRelease[i]];
        
        if(str.compare("NBWD")==0 ||  str.compare("NBDO")==0 )
            str = "NBDZ";
        
        if(str.compare("CBWD")==0 ||  str.compare("CBDZ")==0 )
            str = "CBDO";
        
        if(str.compare("CDWD")==0 ||  str.compare("CDDO")==0 ||  str.compare("CDDZ")==0 )
            str = "CDDO";
        
        if(str.compare("RDWD")==0 ||  str.compare("RDDO")==0 ||  str.compare("RDDZ")==0 )
            str = "RDDO";
        
        if(str.compare("RB")==0)
            str = "RB";
        
        if(str.compare("CF")==0)
            str = "CF";
        
        if(str.compare("RF")==0)
            str = "RF";
        
        if(str.compare("RRB")==0)
            str = "RRB";
        
        if(str.compare("CRB")==0)
            str = "CRB";
        
        functionIndex.insert(pair<string,int>(str, i));
    }
    
    for (int i= 0 ; i<offDiagonalRelease.size(); i++)
    {
        string str = fTypeMapping[offDiagonalRelease[i]];
        
        if(str.compare("NBWD")==0 ||  str.compare("NBDO")==0 )
            str = "NBDZ";
        
        if(str.compare("CBWD")==0 ||  str.compare("CBDZ")==0 )
            str = "CBDO";
        
        if(str.compare("CDWD")==0 ||  str.compare("CDDO")==0 ||  str.compare("CDDZ")==0 )
            str = "CDDO";
        
        if(str.compare("RDWD")==0 ||  str.compare("RDDO")==0 ||  str.compare("RDDZ")==0 )
            str = "RDDO";
        
        if(str.compare("RB")==0)
            str = "RB";
        
        if(str.compare("RB")==0)
            str = "RB";
        
        if(str.compare("CF")==0)
            str = "CF";
        
        if(str.compare("RF")==0)
            str = "RF";
        
        if(str.compare("RRB")==0)
            str = "RRB";
        
        if(str.compare("CRB")==0)
            str = "CRB";
        
        functionIndex.insert(pair<string,int>( str, i + (int) diagonalRelease.size()));
    }
}

vector<vector<vector<ptrFunc>>> DataControler::loadIdealBlocks()
{
    vector<ptrFunc>idealBlockSetupDiagonalVector;
    vector<ptrFunc>idealBlockSetupOffDiagonalVector;
    vector<FunctionType> diagonalRelease, offDiagonalRelease;
    
    DataManager::getDataManager()->getMatrixRelease(diagonalRelease, offDiagonalRelease);
    
    for (int i = 0 ; i<diagonalRelease.size(); i++)
        matchingFunctionType(idealBlockSetupDiagonalVector, diagonalRelease[i]);
    
    for (int i = 0 ; i<offDiagonalRelease.size(); i++)
        matchingFunctionType(idealBlockSetupOffDiagonalVector, offDiagonalRelease[i]);
    
    vector<vector<vector<ptrFunc>>> idealBlockSetupMatrix;
    for (int cluster_k = 0; cluster_k<networkSize; cluster_k++)
    {
        vector<vector<ptrFunc>>idealBlockSetupArray;
        for (int cluster_l = 0; cluster_l<networkSize; cluster_l++)
        {
            if (cluster_k == cluster_l)
            {
                vector<ptrFunc>idealBlockSetupVector;
                
                for (int i = 0; i<idealBlockSetupDiagonalVector.size(); i++)
                    idealBlockSetupVector.push_back(idealBlockSetupDiagonalVector[i]);
                
                idealBlockSetupArray.push_back(idealBlockSetupVector);
            }
            else
            {
                vector<ptrFunc>idealBlockSetupVector;
                
                for (int i = 0; i<idealBlockSetupOffDiagonalVector.size(); i++)
                    idealBlockSetupVector.push_back(idealBlockSetupOffDiagonalVector[i]);
                
                idealBlockSetupArray.push_back(idealBlockSetupVector);
            }
        }
        
        idealBlockSetupMatrix.push_back(idealBlockSetupArray);
    }
    buildingFunctionIndexStructure();
    return idealBlockSetupMatrix;
}

void DataControler::matchingFunctionType(vector<ptrFunc>& idealBlockSetupVector, FunctionType type)
{
    if (type == NBDO || type == NBDZ ||  type== NBWD)
        idealBlockSetupVector.push_back(&BlockError::nullBlock);
    
    if (type == CBDO || type == CBDZ ||  type == CBWD)
        idealBlockSetupVector.push_back(&BlockError::completeBlock);
    
    if (type == RRB)
        idealBlockSetupVector.push_back(&BlockError::rowRegular);
    
    if (type == CRB)
        idealBlockSetupVector.push_back(&BlockError::colRegular);
    
    if (type == RB)
        idealBlockSetupVector.push_back(&BlockError::regularBlock);
    
    if (type ==  RDWD || type == RDDO ||  type == RDDZ)
        idealBlockSetupVector.push_back(&BlockError::rowDominant);
    
    if (type ==  CDWD || type == CDDO ||  type == CDDZ)
        idealBlockSetupVector.push_back(&BlockError::colDominant);
    
    if (type ==  CF )
        idealBlockSetupVector.push_back(&BlockError::colFunctional);
    
    if (type ==  RF )
        idealBlockSetupVector.push_back(&BlockError::rowFunctional);
}

string DataControler::typeToFunction(ptrFunc idealBlock)
{
    if (idealBlock == &BlockError::nullBlock)
        return  "NBDZ";
    
    if (idealBlock == &BlockError::completeBlock)
        return "CBDO";
    
    if (idealBlock == &BlockError::rowRegular)
        return  "RRB";
    
    if (idealBlock == &BlockError::colRegular)
        return  "CRB";
    
    if (idealBlock == &BlockError::regularBlock)
        return  "RB";
    
    if (idealBlock == &BlockError::rowDominant)
        return "RDDO";
    
    if (idealBlock == &BlockError::colDominant)
        return "CDDO";
    
    if ( idealBlock == &BlockError::colFunctional)
        return "CF";
    
    if (idealBlock ==  &BlockError::rowFunctional)
        return "RF";
    
    return "";
}

void DataControler::initAllImageMatrix()
{
    imageMatrixSeed = bestImageMatrix = this->imageMatrix;
}

void DataControler::loadExecutionOrder()
{
    executionOrder = (DataManager::getDataManager()->sequence == RANDOM) ? Sequence().random() : Sequence().sequential();
};

map<int,vector<int>> DataControler::getInitialPartition()
{
    return initialPartition;
}

map<int,vector<int>> DataControler::getBestPartition()
{
    return bestPartition;
}

void DataControler::setBestPartition(map<int,vector<int>> bestPartition)
{
    this->bestPartition = bestPartition;
}

void DataControler::setBestNodeToCluster( map<int,int> bestNodeToCluster)
{
    this->bestNodeToCluster = bestNodeToCluster;
}

void DataControler::setNode(int node)
{
    this->node = executionOrder[node];
}

int DataControler::getNode()
{
    return node;
}


vector<int> DataControler::getExecutionOrder()
{
    return executionOrder;
}

int DataControler::getMinGlobalError()
{
    return minGlobalError;
}

map<int,int> DataControler::getInitialNodeToCluster()
{
    return initialNodeToCluster;
}

map<int,int> DataControler::getBestNodeToCluster()
{
    return bestNodeToCluster;
}

vector<map<int,vector<int>>> DataControler::getSolutions()
{
    return solutions;
}

vector<map<int,vector<int>>> DataControler::getSeeds()
{
    return seeds;
}

vector<int> DataControler::getDesviationMeasure()
{
    return desviationMeasure;
}

void DataControler::setMinGlobalError(int minGlobalError)
{
    this->minGlobalError = minGlobalError;
}

void DataControler::setImageMatrix(map<pair<int,int>, MatchingError> imageMatrix)
{
    this->imageMatrix = imageMatrix;
}

void DataControler::setAfectedRelations(int clusterSource, int clusterTarget)
{
    this->clusterSource = clusterSource;
    this->clusterTarget = clusterTarget;
}

void DataControler::imageMatrixRemove(int cluster_k, int cluster_l)
{
    map<pair<int,int>, MatchingError>::iterator it = imageMatrix.find(make_pair(cluster_k, cluster_l));
    if(it != imageMatrix.end())
        imageMatrix.erase(it);
}

void DataControler::imageMatrixInsert(pair<int,int> key, MatchingError value)
{
    imageMatrix.insert(pair<pair<int,int>, MatchingError> (key, value));
}


void DataControler::loadCurrentPartition()
{
    //currentPartition = initialPartition;
    //nodeToCluster =
}

void DataControler::loadCurrentStructures()
{
    currentPartition = initialPartition;
    nodeToCluster = initialNodeToCluster;
}

map<pair<int,int>, MatchingError>  DataControler::getImageMatrix()
{
    return imageMatrix;
}

bool DataControler::checkUpErrorTarget(int cluster_k, int cluster_l)
{
    return false;
}

bool DataControler::checkUpErrorSource(int cluster_k, int cluster_l)
{
    int sizeIM = (int) imageMatrix.size();
    int sizeIP = (int)currentPartition.size();
    
    if (sizeIM /sizeIP != sizeIP) return false;
    
    if ( cluster_k == clusterSource  || cluster_l == clusterTarget) return false;
    if ( cluster_k == clusterTarget  || cluster_l == clusterSource) return false;
    
    if (initialPartition.at(cluster_l).size()==0) return false;
    
    string strA = typeToFunction(imageMatrixSeed.at(make_pair(cluster_k, cluster_l)).idealBlockMatching);
    
    if (strA.compare("NBDZ")== 0 && imageMatrixSeed.at(make_pair(cluster_k,cluster_l)).blockError == 0)
        return true;
    
    if (strA.compare("CBDO")== 0 && imageMatrixSeed.at(make_pair(cluster_k,cluster_l)).blockError == 0)
        return true;
    
    return false;
    
}

void DataControler::addNewCluster()
{
    vector<int> nodes;
    currentPartition.insert(pair<int, vector<int>>((int)currentPartition.size(), nodes));
    currentPartition.at((int) currentPartition.size()-1).push_back(node);
    nodeToCluster.at(node) = (int) currentPartition.size()-1;
}

void DataControler::addNodeToCluster(int cluster, int node)
{
    // nao esta generico, mexer nisso... para ajustar com swap
    currentPartition.at(cluster).push_back(node);
    nodeToCluster.at(node) = cluster;
    
}

void DataControler::addNodeToCluster(int cluster, int node, int position)
{
    currentPartition.at(cluster).insert(currentPartition.at(cluster).begin()+position, node);
    nodeToCluster.at(node) = cluster;
    
}

int DataControler::getClusterSourceNode()
{
    return initialNodeToCluster.at(node);
}

void DataControler::updateDataStructure()
{
    if (heuristicStrategy == BEST_SOLUTION || heuristicStrategy == FIRST_EQUAL_OR_BEST_SOLUTION)
    {
        initialPartition  = bestPartition;
        initialNodeToCluster = bestNodeToCluster;
        imageMatrixSeed   = bestImageMatrix;
        
        if (minGlobalError<desviation)
        {
            nodeSolution = bestNodeToCluster;
            solution = bestPartition;
            bestfitnness = bestImageMatrix;
            desviation = minGlobalError;
        }
        
        /* 
         solutions.push_back(bestPartition);
         seeds.push_back(initialPartition);
         desviationMeasure.push_back(minGlobalError);
         fitnness.push_back(bestImageMatrix);
         */
    }
}

void DataControler::loadPartitionFromAnotherDataControler(DataControler *dataControlerAux)
{
    initialPartition     = dataControlerAux->initialPartition;
    initialNodeToCluster =  dataControlerAux->initialNodeToCluster;
    
    bestPartition = dataControlerAux->bestPartition;
    bestNodeToCluster = dataControlerAux->bestNodeToCluster;
    
    imageMatrixSeed = bestImageMatrix = dataControlerAux->getImageMatrix();
    minGlobalError = dataControlerAux->getMinGlobalError();
    
    allFunctionsImageMatrix = dataControlerAux->allFunctionsImageMatrix;
    
    if (dataControlerAux->getMinGlobalError()==0)
        throw -1;
}

void DataControler::loadPartitionFromAnotherDataControler2(DataControler *dataControlerAux)
{
    initialPartition     = dataControlerAux->initialPartition;
    initialNodeToCluster =  dataControlerAux->initialNodeToCluster;
    
    bestPartition = dataControlerAux->bestPartition;
    bestNodeToCluster = dataControlerAux->bestNodeToCluster;
    
    imageMatrixSeed = bestImageMatrix = dataControlerAux->getImageMatrix();
    minGlobalError = dataControlerAux->getMinGlobalError();
    
    allFunctionsImageMatrix = dataControlerAux->allFunctionsImageMatrix;
    
    if (minGlobalError<desviation)
    {
        solution = bestPartition;
        bestfitnness = bestImageMatrix;
        desviation = minGlobalError;
    }
    
    if (dataControlerAux->getMinGlobalError()==0)
        throw -1;
}

void DataControler::deleteNode( map<int,vector<int>> &partition, int clusterIndex, int node)
{
    auto v = find(partition.at(clusterIndex).begin(),  partition.at(clusterIndex).end(), node);
    if(v !=  partition.at(clusterIndex).end())
        partition.at(clusterIndex).erase(v);
}
