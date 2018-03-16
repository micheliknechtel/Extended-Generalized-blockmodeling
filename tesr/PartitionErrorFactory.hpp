//
//  PartitionErrorFactory.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/03/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef PartitionErrorFactory_hpp
#define PartitionErrorFactory_hpp

#include <stdio.h>
#include "PartitionErrorBase.hpp"

class PartitionErrorFactory {
    static PartitionErrorFactory *partitionErrorFactory;
public:
    static PartitionErrorFactory* getPartitionErrorFactory();
    PartitionErrorBase* newErrorObject(bool optimizedCode);
};

#endif /* PartitionErrorFactory_hpp */
