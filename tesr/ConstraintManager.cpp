//
//  ConstraintManager.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 16/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "ConstraintManager.hpp"


ConstraintManager* ConstraintManager::ctrManager = NULL;

ConstraintManager* ConstraintManager::getConstraintManager()
{
    if(!ctrManager)
    {
        ctrManager = new ConstraintManager;
    }
    return ctrManager;
}


ConstraintManager::ConstraintManager()
{
    loadingStructure();
}

void ConstraintManager::loadingStructure()
{
    // loading constraints..
    for (itConstraintsEnum)
    {
        correlation c;
        c.isAlreadyAdded = false;
        c.type = (constraintsEnum)it;
        
        constraintManager[constraintIndentier[it]] = c;
    }
    
    // adding group constraints...
    for (itFunctionType)
    {
        functionConstraintMap[fTypeMapping[it]] = getSet((FunctionType)it);
    }
    
}

vector<string> ConstraintManager::getSet(FunctionType type)
{
    vector<string> v;
    
    if ( type == NBDO)
    {
        vector<string> v(ARRAY_NBDO, ARRAY_NBDO + ARRAY_NBDO_SIZE);
        return v;
    }
    if ( type == NBDZ)
    {
        vector<string> v(ARRAY_NBDZ, ARRAY_NBDZ + ARRAY_NBDZ_SIZE);
        return v;
    }
    if ( type == NBWD)
    {
        vector<string> v(ARRAY_NBWD, ARRAY_NBWD + ARRAY_NBWD_SIZE);
        return v;
    }
    if ( type == CBDO)
    {
        vector<string> v(ARRAY_CBDO, ARRAY_CBDO + ARRAY_CBDO_SIZE);
        return v;
    }
    if ( type == CBDZ)
    {
        vector<string> v(ARRAY_CBDZ, ARRAY_CBDZ + ARRAY_CBDZ_SIZE);
        return v;
    }
    if ( type == CBWD)
    {
        vector<string> v(ARRAY_CBWD, ARRAY_CBWD + ARRAY_CBWD_SIZE);
        return v;
    }
    if ( type == RRB)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_RRB_SYM, ARRAY_RRB_SYM + ARRAY_RRB_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_RRB, ARRAY_RRB + ARRAY_RRB_SIZE);
            return v;
//        }
    }
    if ( type == CRB)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_CRB_SYM, ARRAY_CRB_SYM + ARRAY_CRB_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_CRB, ARRAY_CRB + ARRAY_CRB_SIZE);
            return v;
//        }
    }
    if ( type == RDWD)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_RDWD_SYM, ARRAY_RDWD_SYM + ARRAY_RDWD_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_RDWD, ARRAY_RDWD + ARRAY_RDWD_SIZE);
            return v;
//        }
    }
    if ( type == RDDO)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_RDDO_SYM, ARRAY_RDDO_SYM + ARRAY_RDDO_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_RDDO, ARRAY_RDDO + ARRAY_RDDO_SIZE);
            return v;
//        }
    }
    if ( type == RDDZ)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_RDDZ_SYM, ARRAY_RDDZ_SYM + ARRAY_RDDZ_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_RDDZ, ARRAY_RDDZ + ARRAY_RDDZ_SIZE);
            return v;
//        }
    }
    if ( type == CDWD)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_CDWD_SYM, ARRAY_CDWD_SYM + ARRAY_CDWD_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_CDWD, ARRAY_CDWD + ARRAY_CDWD_SIZE);
            return v;
//        }
    }
    if ( type == CDDO)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_CDDO_SYM, ARRAY_CDDO_SYM + ARRAY_CDDO_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_CDDO, ARRAY_CDDO + ARRAY_CDDO_SIZE);
            return v;
//        }
    }
    if ( type == CDDZ)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_CDDZ_SYM, ARRAY_CDDZ_SYM + ARRAY_CDDZ_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_CDDZ, ARRAY_CDDZ + ARRAY_CDDZ_SIZE);
            return v;
//        }
    }
    
    if ( type == RB)
    {
        vector<string> v(ARRAY_RB, ARRAY_RB + ARRAY_RB_SIZE);
        return v;
    }
    
    if ( type == CF)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_CF_SYM, ARRAY_CF_SYM + ARRAY_CF_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_CF, ARRAY_CF + ARRAY_CF_SIZE);
            return v;
//        }
    }
    
    if ( type == RF)
    {
//        if (DataManager::getDataManager()->graph->itsSymmetricGraph)
//        {
//            vector<string> v(ARRAY_RF_SYM, ARRAY_RF_SYM + ARRAY_RF_SYM_SIZE);
//            return v;
//        }
//        else
//        {
            vector<string> v(ARRAY_RF, ARRAY_RF + ARRAY_RF_SIZE);
            return v;
//        }
    }
    
    if ( type == ALL_FUNCTIONS)
    {
        vector<string> v(ARRAY_ALL_FUNCTIONS, ARRAY_ALL_FUNCTIONS + ARRAY_ALL_FUNCTIONS_SIZE);
        return v;
    }
    
    return v;
}

void ConstraintManager::addFunctionConstraints(FunctionType type, Constraints *c)
{
    vector<string> v = functionConstraintMap[fTypeMapping[type]];
    FunctionRelease release =  DataManager::getDataManager()->getCurrentfDetails().release;
    
    
    
    for (int i = 0; i<v.size(); i++)
    {
        if (constraintManager[v[i]].isAlreadyAdded == false)
        {
            constraintManager[v[i]].isAlreadyAdded = true;
            constraintManager[v[i]].release = release;
            
            constraintsEnum w = constraintManager[v[i]].type;
            
            (*c.*allFunctions[w])();
        }
        else if (constraintManager[v[i]].isAlreadyAdded == true && constraintManager[v[i]].release!=release && v[i].compare("SHARED_CONSTRAINT")!=0)
        {
            if (constraintManager[v[i]].release == ALL || v[i].compare("SUM_EMPTY_CLUSTER")==0)
            {
                continue;
            }
            else
            {
                constraintManager[v[i]].release = ALL;
                constraintsEnum w = constraintManager[v[i]].type;
                (*c.*allFunctions[w])();
            }
        }
    }
}


