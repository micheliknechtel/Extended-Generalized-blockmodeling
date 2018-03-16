//
//  DataManager.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "DataManager.hpp"
#include <cstring>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include "rapidxml.hpp"

using namespace rapidxml;

DataManager* DataManager::dataManager = NULL;

DataManager* DataManager::getDataManager()
{
    if(!dataManager)
    {
        dataManager = new DataManager;
    }
    return dataManager;
}

void DataManager::readRelationMatrixTwo()
{
    string str = directoriePath + fileRelationMatrix;
    const char * fin  = str.c_str();
    ifstream file(fin);
    
    
    int l, m;
    file>>networkSize;
    
    relationMatrix =  new int*[networkSize];
    
    for ( int i = 0; i < networkSize; i++ )
    {
        relationMatrix[i] =  new int[networkSize];
        
        for ( int j = 0; j < networkSize; j++ )
        {
            relationMatrix[i][j] = 0;
        }
    }
    
    while(1)
    {
        if(file.eof())
        {
            break;
        }
        file>>l>>m;
        relationMatrix[l-1][m-1] = 1;
    }
}


void DataManager::readRelationMatrixLabeling()
{
    string str = directoriePath + fileRelationMatrix;
    const char * fin  = str.c_str();
    ifstream file(fin);
    map<int, int> labelNode;
    
    int l, m;
    file>>networkSize;
    
    relationMatrix =  new int*[networkSize];

    for ( int i = 0; i < networkSize; i++ )
    {
        relationMatrix[i] =  new int[networkSize];
        
        for ( int j = 0; j < networkSize; j++ )
        {
            relationMatrix[i][j] = 0;
        }
    }

    int index = -1;
    
    while(1)
    {
        if(file.eof())
        {
            break;
        }
        file>>l>>m;
        
        
        if(labelNode.find(l)== labelNode.end())
        {
           index++;
           labelNode.insert(pair<int, int>(l,index));
        }

        if(labelNode.find(m)== labelNode.end())
        {
            index++;
            labelNode.insert(pair<int, int>(m,index));

        }
        
        relationMatrix[labelNode.at(l)][labelNode.at(m)] = 1;
    }
}

void DataManager::readRelationMatrixOne()
{
    string str = DataManager::getDataManager()->directoriePath + DataManager::getDataManager()->fileRelationMatrix;
    const char * fin  = str.c_str();
    
    ifstream file(fin);
    file>>networkSize;
    relationMatrix =  new int*[networkSize];
    
    for ( int i = 0; i < networkSize; i++ )
    {
        relationMatrix[i] =  new int[networkSize];
        
        for ( int j = 0; j < networkSize; j++ )
        {
            file>>relationMatrix[i][j];
        }
    }
    cout<<endl;
}

void DataManager::readRelationMatrixFromXML()
{
    string str = directoriePath + fileRelationMatrix;
    const char * fin  = str.c_str();

    xml_document<> doc;
    xml_node<> * root_node;
    
    ifstream theFile(fin);
    
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    
    doc.parse<0>(&buffer[0]);
    
    root_node =  doc.first_node();
    
    xml_node<> * graph_node;
    xml_node<> * vertice_node;
    xml_node<> * edge_node;
    
    int nodeNumber = -1;
    
    for (graph_node = root_node->first_node("graph"); graph_node; graph_node = graph_node->next_sibling())
    {
        for(vertice_node = graph_node->first_node("node"); vertice_node!= graph_node->first_node("edge"); vertice_node = vertice_node->next_sibling())
        {
            string verticeLabel = vertice_node->first_node("data")->value();
            string verticeID = vertice_node->first_attribute("id")->value();

            nodeID2Name.insert(pair<string,string>(verticeID,verticeLabel));

            
        }
        
        for(edge_node = graph_node->first_node("edge"); edge_node; edge_node = edge_node->next_sibling())
        {
            string source = edge_node->first_attribute("source")->value();
            string target = edge_node->first_attribute("target")->value();
            
            if (nodeID2Name.at(source).length()>verticeLabelMaxSize)
                verticeLabelMaxSize = (int) nodeID2Name.at(source).length();
            
            if (nodeID2Name.at(target).length()>verticeLabelMaxSize)
                verticeLabelMaxSize = (int) nodeID2Name.at(target).length();

            if(ID2Index.find(source)== ID2Index.end())
            {
                nodeNumber++;
                ID2Index.insert(pair<string,int>(source, nodeNumber));
                index2ID.insert(pair<int,string>(nodeNumber,source));
            }
            
            if(ID2Index.find(target)== ID2Index.end())
            {
                nodeNumber++;
                ID2Index.insert(pair<string,int>(target, nodeNumber));
                index2ID.insert(pair<int,string>(nodeNumber,target));
                
            }
            edge.insert(pair<pair<int,int>, double>(pair<int,int>(ID2Index.at(source),ID2Index.at(target)), atof(edge_node->first_node("data")->value())));
        }
    }
    
    networkSize = (int) index2ID.size();
    relationMatrix =  new int*[networkSize];
    
    for ( int i = 0; i < networkSize; i++ )
    {
        relationMatrix[i] =  new int[networkSize];
        
        for ( int j = 0; j < networkSize; j++ )
            relationMatrix[i][j] = 0;
    }
    
    for (map<pair<int,int>, double> ::iterator it = edge.begin();it!= edge.end(); it++)
        relationMatrix[it->first.first][it->first.second] = 1;
    
}

void DataManager::printRelationMatrix()
{
    
    int totalOne=0;
    int sumOneLine =0;
    int sumOneColumn=0;
    int totalOneDiagonal = 0;
    
    for ( int i = 0; i < networkSize; i++ )
    {
        for ( int j = 0; j < networkSize; j++ )
        {
            if (relationMatrix[i][j]==1)
            {
                sumOneLine++;
                totalOne++;
            }
            
            if (relationMatrix[j][i]==1)
            {
                sumOneColumn++;
            }
            
            if (relationMatrix[i][j]==1 && i==j)
            {
                totalOneDiagonal++;
            }
            cout<<" "<<relationMatrix[i][j];
        }
        
        cout<<" | line = ";
        cout.fill( ' ' );
        cout.width( 5 );
        cout << sumOneLine;
        cout<<" | colum = ";
        cout.fill( ' ' );
        cout.width( 5 );
        cout << sumOneColumn;
        cout<<endl;
        sumOneLine = 0;
        sumOneColumn = 0;
    }
    cout<<endl;
    cout<<"Number of one's in diagonal   = ["<<totalOneDiagonal<<"]"<<endl;
    cout<<"Number of one's in the matrix = ["<<totalOne<<"]"<<endl;
    cout<<"Matrix size                   = ["<<networkSize<<"]"<<endl;
    cout<<endl;
}

void DataManager::createGraph()
{
    if (preProcessingMode)
        graph = (new Preprocessing(networkSize,relationMatrix))->processingData();
    else
        graph = new Graph (false, false);
}

void DataManager::readFunctionTable()
{
    string str = directoriePath + fileFunctionTable;
    const char * fin  = str.c_str();
    ifstream file(fin);
    
    for ( int i  = 0; !file.eof(); i++ )
    {
        string name, release;
        
        file>>name>>release;
        
        if (name.compare("")==0 && release.compare("")==0)
        {
            continue;
        }
        
        FunctionDetails fDetails = FDetails(name, release);
        functionMapping.push_back(fDetails);
        functionSize = i+1;
        
        if (!symmetricProperty)
        {
            symmetricProperty = isItNonSymmetricPropertie(name);
        }
        
        if (name.compare("ALL_FUNCTIONS") == 0)
        {
            functionMapping.clear();
            
            for (itFunctionType)
            {
                if (it != ALL_FUNCTIONS)
                {
                    FunctionDetails fDetails = FDetails(fTypeMapping[it], release);
                    functionMapping.push_back(fDetails);
                }
            }
            
            FunctionDetails fDetails = FDetails(fTypeMapping[ALL_FUNCTIONS], release);
            functionMapping.push_back(fDetails);
            functionSize = 17;
            break;
        }
    }
}

void DataManager::printFunctionTable()
{
    
    
    cout<<"IdealBlocks Set-up: "<<endl<<endl;
    
    
    for ( int i = 0; i < functionMapping.size(); i++ )
    {
        if (functionMapping[i].name.size()==2)
        {
            cout<<functionMapping[i].name;
            cout.fill( ' ' );
            cout.width(3);
            cout<<" "<<fReleaseMapping[functionMapping[i].release]<<endl;
            
        }
        
        else if (functionMapping[i].name.size()==3)
        {
            cout<<functionMapping[i].name;
            cout.fill( ' ' );
            cout.width(2);
            cout<<" "<<fReleaseMapping[functionMapping[i].release]<<endl;
        }
        else
        {
            cout<<functionMapping[i].name<<" "<<fReleaseMapping[functionMapping[i].release]<<endl;
        }
    }
    cout<<endl;
    
}

FunctionDetails DataManager::FDetails(string name, string release)
{
    release =  upperCase(release);
    FunctionRelease funcRelease = (strcmp(release.c_str(), "ALL")==0) ? ALL:(strcmp(release.c_str(), "OFF_DIAGONAL")==0)? OFF_DIAGONAL : DIAGONAL;
    FunctionDetails fDetails;
    fDetails.name = name;
    fDetails.release = funcRelease;
    fDetails.type = getType(name);
    fDetails.symmetricProperty = !isItNonSymmetricPropertie(name);
    return fDetails;
}

FunctionType DataManager::getType(string name)
{
    if ((strcmp(name.c_str(), fTypeMapping[NBDO])==0))
        return NBDO;
    else if ((strcmp(name.c_str(), fTypeMapping[NBDZ])==0))
        return NBDZ;
    else if ((strcmp(name.c_str(), fTypeMapping[NBWD])==0))
        return NBWD;
    else if ((strcmp(name.c_str(), fTypeMapping[CBDO])==0))
        return CBDO;
    else if ((strcmp(name.c_str(), fTypeMapping[CBDZ])==0))
        return CBDZ;
    else if ((strcmp(name.c_str(), fTypeMapping[CBWD])==0))
        return CBWD;
    else if ((strcmp(name.c_str(), fTypeMapping[ALL_FUNCTIONS])==0))
        return ALL_FUNCTIONS;
    else if ((strcmp(name.c_str(), fTypeMapping[RRB])==0))
        return RRB;
    else if ((strcmp(name.c_str(), fTypeMapping[CRB])==0))
        return CRB;
    else if ((strcmp(name.c_str(), fTypeMapping[RB])==0))
        return RB;
    else if ((strcmp(name.c_str(), fTypeMapping[RDWD])==0))
        return RDWD;
    else if ((strcmp(name.c_str(), fTypeMapping[RDDO])==0))
        return RDDO;
    else if ((strcmp(name.c_str(), fTypeMapping[RDDZ])==0))
        return RDDZ;
    else if ((strcmp(name.c_str(), fTypeMapping[CDWD])==0))
        return CDWD;
    else if ((strcmp(name.c_str(), fTypeMapping[CDDO])==0))
        return CDDO;
    else if ((strcmp(name.c_str(), fTypeMapping[CDDZ])==0))
        return CDDZ;
    else if ((strcmp(name.c_str(), fTypeMapping[CF])==0))
        return CF;
    else if ((strcmp(name.c_str(), fTypeMapping[RF])==0))
        return RF;
    else
        throw -1;// type does not exist!
}


FunctionDetails DataManager::getfDetails(FunctionType type)
{
    
    for ( int i = 0; i < functionMapping.size(); i++ )
    {
        if(functionMapping[i].type == type)
            return functionMapping[i];
    }
    throw -1; // type was not added !!!
}

bool DataManager::isTypeAdded(FunctionType type)
{
    
    for ( int i = 0; i < functionMapping.size(); i++ )
    {
        if(functionMapping[i].type == type)
            return true;
    }
    return false;
}



FunctionDetails DataManager::getCurrentfDetails()
{
    return functionMapping[currentfDetails];
}

void DataManager::setCurrentfDetails(int index)
{
    currentfDetails = index;
}

string DataManager::upperCase(string str)
{
    int i=0;
    while (str[i])
    {
        str[i]= (toupper(str[i]));
        i++;
    }
    return str;
}



void DataManager::loadingData()
{
    if(matrixDataType == BINARY)
        readRelationMatrixOne();
    else if(matrixDataType == EDGES)
        readRelationMatrixTwo();
    else if(matrixDataType == XML)
        readRelationMatrixFromXML();
    else if(matrixDataType == LABEL)
        readRelationMatrixLabeling();
    else
    {
        cout<<"Matrix format undefined !!! ";
        exit(1);
    }
    
    DataManager::getDataManager()->clusterUpperBound = networkSize;

    createGraph();
    readFunctionTable();
    adjustingFunctionProperties();
}

void DataManager::adjustingFunctionProperties()
{
    releaseNullBlock = DataManager::getDataManager()->getDataManager()->getBlockRelease(NBDO,NBDZ,NBWD);
    releaseCompleteBlock = DataManager::getDataManager()->getDataManager()->getBlockRelease(CBDZ,CBDO,CBWD);
    releaseColumnDominantBlock = DataManager::getDataManager()->getDataManager()->getBlockRelease(CDWD,CDDO,CDDZ);
    releaseRowDominantBlock = DataManager::getDataManager()->getDataManager()->getBlockRelease(RDWD,RDDO,RDDZ);
    releaseRegularBlock = DataManager::getDataManager()->getDataManager()->getBlockRelease(RB, RRB, CRB);
    releaseFunctionalBlock = DataManager::getDataManager()->getDataManager()->getBlockRelease(CF, RF);
}

void DataManager::setFileRelationMatrix(string fileRelationMatrix)
{
    this->fileRelationMatrix = fileRelationMatrix;
}

void DataManager::setDirectorie(string directoriePath)
{
    this->directoriePath = directoriePath;
}

void DataManager::setfileFunctionTable(string fileFunctionTable)
{
    this->fileFunctionTable = fileFunctionTable;
}

void DataManager::setFileModelName(string modelName)
{
    this->modelName = modelName;
}

string DataManager::getModelLocation()
{
    string modelLocation = directoriePath + modelName + ".lp";
    return modelLocation;
}


FunctionRelease DataManager::getBlockRelease(FunctionType type_01, FunctionType type_02, FunctionType type_03)
{
    FunctionRelease release_01 = NOT_SPECIFIED, release_02 = NOT_SPECIFIED, release_03 = NOT_SPECIFIED;
    
    if (type_01!=UNDEFINED && isTypeAdded(type_01))
    {
        release_01 = getfDetails(type_01).release;
    }
    
    if (type_02!=UNDEFINED && isTypeAdded(type_02))
    {
        release_02 = getfDetails(type_02).release;
    }
    
    if (type_03!=UNDEFINED &&  isTypeAdded(type_03))
    {
        release_03 = getfDetails(type_03).release;
    }
    
    if(release_01 == ALL || release_02 == ALL || release_03 == ALL)
        return ALL;
    
    if(release_01 == OFF_DIAGONAL || release_02 == OFF_DIAGONAL || release_03 == OFF_DIAGONAL)
        return OFF_DIAGONAL;
    
    if(release_01 == DIAGONAL || release_02 == DIAGONAL || release_03 == DIAGONAL)
        return DIAGONAL;
    
    return NOT_SPECIFIED;
}

// Esta ruim essa implementação, usar mesma logica que isItNonSymmetricPropertie
// e areThereNonSymmetricPropertie, preencher variavel na hora da leitura e nao percorer vetor loucamente.
bool DataManager::areThereBlockWithDiagonalVariationZero()
{
    if (isTypeAdded(NBDZ))
    {
        return true;
    }
    if (isTypeAdded(CBDZ))
    {
        return true;
    }
    if (isTypeAdded(RDDZ))
    {
        return true;
    }
    if (isTypeAdded(CDDZ))
    {
        return true;
    }
    
    return false;
}


// Esta ruim essa implementação, usar mesma logica que isItNonSymmetricPropertie
// e areThereNonSymmetricPropertie, preencher variavel na hora da leitura e nao percorer vetor loucamente.

bool DataManager::areThereBlockWithDiagonalVariationOne()
{
    if (isTypeAdded(NBDO))
    {
        return true;
    }
    if (isTypeAdded(CBDO))
    {
        return true;
    }
    if (isTypeAdded(RDDO))
    {
        return true;
    }
    if (isTypeAdded(CDDO))
    {
        return true;
    }
    if (isTypeAdded(CF))
    {
        return true;
    }
    if (isTypeAdded(RF))
    {
        return true;
    }
    return false;
}

bool DataManager::areThereNonSymmetricPropertie()
{
    return symmetricProperty;
}

bool DataManager::isItNonSymmetricPropertie(string name)
{
    if ("RRB" == name)
        return true;
    if ("CRB" == name)
        return true;
    if ("RDWD" == name)
        return true;
    if ("RDDZ" == name)
        return true;
    if ("RDDO" == name)
        return true;
    if ("CDWD" == name)
        return true;
    if ("CDDO" == name)
        return true;
    if ("CDDZ" == name)
        return true;
    if ("CF" == name)
        return true;
    if ("RF" == name)
        return true;
    
    return false;
}

void DataManager::getMatrixRelease(vector<FunctionType> &diagonalRelease, vector<FunctionType>&offDiagonalRelease)
{
    
    for (int i = 0 ; i<functionMapping.size(); i++)
    {
        if (functionMapping[i].release == DIAGONAL || functionMapping[i].release == ALL)
            diagonalRelease.push_back(functionMapping[i].type);
        
        if (functionMapping[i].release == OFF_DIAGONAL || functionMapping[i].release == ALL)
            offDiagonalRelease.push_back(functionMapping[i].type);
    }
}

void DataManager::setMatrixDataType(MatrixDataType type)
{
    matrixDataType = type;
}

bool DataManager::getAdditionalConstraint()
{
    return addAdditionalConstraint;
}

void DataManager::setAdditionalConstraint(bool addAdditionalConstraint )
{
    this->addAdditionalConstraint = addAdditionalConstraint;
}

void DataManager::enablePreprocessing(bool preProcessingMode)
{
    this->preProcessingMode = preProcessingMode;
}

HeuristicStrategy DataManager::getHeuristicStrategy()
{
    return  heuristicStrategy;
}

string DataManager::getMatrixDataType()
{
    if (matrixDataType == BINARY)
        return "BINARY";
    else if (matrixDataType == XML)
        return"XML";
    else if(matrixDataType == LABEL)
          return"LABEL";
    else
        return "EDGES";
}
string DataManager::getHeuristicStrategyTexte()
{
    return (DataManager::getDataManager()->DataManager::getDataManager()->heuristicStrategy==FIRST_EQUAL_OR_BEST_SOLUTION ? "FIRST_EQUAL_OR_BEST_SOLUTION":"BEST_SOLUTION");
}
