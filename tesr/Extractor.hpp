//
//  Extractor.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 28/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Extractor_hpp
#define Extractor_hpp

#include <stdio.h>
#include "Definitions.h"
#include "Constraints.hpp"

class Extractor: public Constraints {
    
public:
    void getMatrixBlock(IloCplex cplex);
    void getGroup(IloCplex cplex);
    
    void get_tbsOne(IloCplex cplex);
    void get_tbsZero(IloCplex cplex);
    
    void get_bSize(IloCplex cplex);
    
    void get_dsZero(IloCplex cplex);
    void get_dsOne(IloCplex cplex);
    
    void get_y(IloCplex cplex);
    void get_x(IloCplex cplex);
    void get_w(IloCplex cplex);
    void get_f(IloCplex cplex);
    
    void getRelationMatrix();
    void printGroup();
    void buildMatrix();
    void get_rowError(IloCplex cplex);
    void get_colError(IloCplex cplex);
    
    void get_omega(IloCplex cplex);

    
    bool isEmptyGroup(int k, map<string,clusterGroup>::iterator it);
    
    void get_NullBlockDiagonalOne(IloCplex cplex);
    void get_NullBlockWithoutDiagonal(IloCplex cplex);
    void get_NullBlockDiagonalZero(IloCplex cplex);
    
    
    void get_AllFunctionsMapping(IloCplex cplex);

    void get_CompleteBlockWithoutDiagonal(IloCplex cplex);
    void get_CompleteBlockDiagonalOne(IloCplex cplex);
    void get_CompleteBlockDiagonalZero(IloCplex cplex);
    
    void get_AllFunctions(IloCplex cplex);
    void get_linesError(IloCplex cplex);
    
    
    void get_emptyCluster(IloCplex cplex);
    void get_columnError(IloCplex cplex);

    void get_z(IloCplex cplex);
    void get_o(IloCplex cplex);
    void get_h(IloCplex cplex);

};
#endif /* Extractor_hpp */
