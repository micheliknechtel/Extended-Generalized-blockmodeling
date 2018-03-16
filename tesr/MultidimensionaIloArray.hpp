//
//  MultidimensionaIloArray.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.

#include "Definitions.h"
#include "DataManager.hpp"

#ifndef MultidimensionaIloArray_hpp
#define MultidimensionaIloArray_hpp


class MultidimensionaIloArray
{

public:

    // General Allocation  - INTEGER VARIABLES
    
    static IloNumVarArray2 IloNumArray2_tbs_c_h(const IloEnv env, int n, int lb, int ub, string varName, FunctionRelease release);
    static IloNumVarArray3 IloNumVarArray3_ColError_RowError(const IloEnv env, int n, int lb, int ub, string varName, FunctionRelease release);
    
    // Considering or not Simmetry (k,l) for Allocation Methods - F and W VARIABLES

    static IloNumVarArray3 IloNumArray3_F(const IloEnv env, int lb, int ub, string varName);
    static IloNumVarArray3 IloNumArray3_W(const IloEnv env, int lb, int ub, string varName);

    // General Allocation Methods - (O, L, H) VARIABLES

    static IloNumVarArray3 IloNumArray3_lineError_columnError(const IloEnv env, int lb, int ub, string varName);
    
    
        static IloNumVarArray3 IloNumArray3_Z_B(const IloEnv env, int lb, int ub, string varName);
    
    static IloNumVarArray3 IloNumArray3_O_A(const IloEnv env, int lb, int ub, string varName);
    
//    static IloIntVarArray3 IloArray3_O(const IloEnv env, int lb, int ub, string varName);

    // Customized Allocation  - REMOVING ARTIFICIAL SIMMETRY
   static  IloBoolArray2 x_without_artificial_symmetry(const IloEnv env, int n, int clusterUpperBound, string varName); //(OK)

    static IloBoolVarArray2 IloBoolArray2_x_without_artificial_symmetry(const IloEnv env, int n, int clusterUpperBound, string varName);
    static IloNumVarArray4 IloNumArray4_y_without_artificial_symmetry(const IloEnv env, int n,  int clusterUpperBound, string varName);

    // Customized Allocation  - PENALTIES MATRIX
    static IloNumArray3 IloNumArray3_Penalties(const IloEnv env);
    
    
    static IloNumVarArray2 IloNumVarArray2_x_without_artificial_symmetry(const IloEnv env, int n, int clusterUpperBound, string varName);

    static IloNumArray3 IloNumArray3_ValF(const IloEnv env, int lb, int ub, string varName) ;

};


#endif /* MultidimensionaIloArray_hpp */
