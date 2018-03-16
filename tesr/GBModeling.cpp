#include "DataManager.hpp"
#include "CplexModel.hpp"
#include "Parameters.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "VNSHeuristic.hpp"

int main (int argc, char **argv)
{
    Parameters * parameters = new Parameters();
    //parameters->loadingFromCommandLine(argc, argv);
    parameters->predefinedParameters();

    
//    if(DataManager::getDataManager()->heuristic)
//    {
//        VNSHeuristic *vnsHeuristic = new VNSHeuristic();
//        vnsHeuristic->runVNSHeuristic();
//    }

    if(DataManager::getDataManager()->model)
    {
        CplexModel * cplexModel = new CplexModel();
        cplexModel->solveCplexModel();
    }
}

