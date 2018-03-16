//
//  PartitionError.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef PartitionError_hpp
#define PartitionError_hpp
#include "PartitionErrorBase.hpp"

class PartitionError : public PartitionErrorBase{

public:
    int calcErrorForAllRelations(DataControler *d);
    int calcErrorOnlyAfectedRelations(DataControler *d);
    void allFunctionsError(DataControler *d, int cluster_k, int cluster_l);
    void error(DataControler *d, int cluster_k, int cluster_l);
    void updateError(int currentError, DataControler *d);
};
#endif /* PartitionError_hpp */
