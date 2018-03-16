//
//  PartitionErrorFactory.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/03/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "PartitionErrorFactory.hpp"
#include "PartitionErrorBase.hpp"
#include "PartitionErrorOtimized.hpp"
#include "PartitionError.hpp"
#include "DataManager.hpp"

PartitionErrorFactory* PartitionErrorFactory::partitionErrorFactory = NULL;

PartitionErrorFactory* PartitionErrorFactory::getPartitionErrorFactory()
{
    if(!partitionErrorFactory)
    {
        partitionErrorFactory = new PartitionErrorFactory;
    }
    return partitionErrorFactory;
}

PartitionErrorBase* PartitionErrorFactory::newErrorObject(bool optimizedCode)
{
    if(optimizedCode)
        return new PartitionErrorOtimized;
    else
        return new PartitionError;
    return NULL;
}
