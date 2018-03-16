//
//  PartitionErrorBase.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/03/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef PartitionErrorBase_hpp
#define PartitionErrorBase_hpp

#include <stdio.h>

#include <map>
#include <vector>
#include "Definitions.h"
#include "DataControler.hpp"
#include "BlockError.hpp"
#include "DataControler.hpp"

class PartitionErrorBase {
    public:
    virtual int calcErrorForAllRelations(DataControler *d) { return 0; };
    virtual int calcErrorOnlyAfectedRelations(DataControler *d) { return 0; };
    virtual int calcErrorNewCluster(DataControler *d){ return calcErrorOnlyAfectedRelations(d); };
    virtual void updateError(int currentError, DataControler *d){};
};

#endif /* PartitionErrorBase_hpp */
