//
//  PartitionErrorOtimized.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/03/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef PartitionErrorOtimized_hpp
#define PartitionErrorOtimized_hpp

#include <stdio.h>
#include "PartitionErrorBase.hpp"

class PartitionErrorOtimized:public PartitionErrorBase{
public:
    int calcErrorForAllRelations(DataControler *d);
    int calcErrorOnlyAfectedRelations(DataControler *d);
    int calcErrorNewCluster(DataControler *d);

   
    void allFunctionsError(DataControler *d);
    void updateError(int currentError, DataControler *d);
   
    void insertNode(DataControler *d, int cluster_l);
    void removeNode(DataControler *d, int cluster_l);
    void addNode(DataControler *d, int cluster_l);
   
    void errorRemove(DataControler *d, int cluster_k, int cluster_l, map<int,vector<int>> currentPartition);
    void errorInsert(DataControler *d, int cluster_k, int cluster_l, map<int,vector<int>> currentPartition);
    
    int updateAllFunctions(DataControler *d, map<int,vector<int>>partition);

};
#endif /* PartitionErrorOtimized_hpp */
