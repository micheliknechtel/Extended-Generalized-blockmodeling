//
//  DataEvaluetor.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 27/03/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "DataEvaluetor.hpp"
#include "DataManager.hpp"
void DataEvaluetor::prepareData()
{
    string str = DataManager::getDataManager()->directoriePath +"../"+ DataManager::getDataManager()->partitionCheck_01;
    freopen(str.c_str(),"w", stdout);
}

void DataEvaluetor::processingData(DataControler *d)
{
    string str = DataManager::getDataManager()->directoriePath +"../"+ DataManager::getDataManager()->partitionCheck_02;
    freopen(str.c_str(),"w", stdout);
    d->loadPartitians();
}
