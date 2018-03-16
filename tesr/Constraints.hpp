//
//  Constraints.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 19/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//



#include "Definitions.h"
#include "MultidimensionaIloArray.hpp"
#include <stdio.h>
#include "DataManager.hpp"
#include "Extractor.hpp"
#include "SharedConstraint.hpp"
#include "LinearConstraint.hpp"
#include "NullBlock.hpp"
#include "CompleteBlock.hpp"
#include "RowRegular.hpp"
#include "ColRegular.hpp"
#include "RegularBlock.hpp"
#include "ConstraintManager.hpp"
#include "ColumnFunctional.hpp"
#include "RowFunctional.hpp"


#include <map>


#ifndef Constraints_hpp
#define Constraints_hpp



class Constraints
{
    
protected:
    IloEnv env;
    IloModel model;
    int clusterUpperBound;
    int functionSize;
    int networkSize;
    int fPSize;
    bool itsSymmetricGraph = DataManager::getDataManager()->graph->itsSymmetricGraph;
    int ** relationMatrix;
    FunctionType typeObjectiveFunction;
    void allocatingVariablesCompleteBlock();
    void allocatingVariablesNullBlock();
    void allocatingVariablesColumnDominantBlock();
    void allocatingVariablesRowDominantBlock();
    void allocatingVariablesRegularBlocks();
    void allocatingDiagonalVariables();
    void allocatingVariablesColumnFunctionalBlock();
    void allocatingVariablesRowFunctionalBlock();
public:
    int clusterLowerBound = 0;
    IloNumVarArray emptyCluster;
    IloNumVarArray3 f;
    IloNumVarArray4 y;
    IloNumVarArray3 w;
    
    IloNumVarArray2 dsOne;
    IloNumVarArray2 dsZero;
    
    IloNumVarArray2 tbsOne;
    IloNumVarArray2 tbsZero;
    
    IloNumVarArray2 bSize;
    IloNumArray3 p;
    
    IloNumVarArray3 o;
    IloNumVarArray3 a;
    
    IloNumVarArray2 h;
    IloNumVarArray2 c;
    
    IloNumVarArray3 columnError;
    IloNumVarArray3 lineError;
    
    IloNumVarArray3 rowError;
    IloNumVarArray3 colError;
    
    IloNumVarArray3 omega;
    IloNumVarArray3 alfa;
    
    IloNumVarArray3 z;
    IloNumVarArray3 b;
    
//    IloBoolVarArray2 x;
    IloNumVarArray2 x;
    
    void diagonalSumEqualsOne();
    void diagonalSumEqualsZero();

    void totalBlockSumEqualsZero();
    void totalBlockSumEqualsOne();
    
    void nullBlockDiagonalEqualsOne();
    void nullBlockDiagonalEqualsZero();
    void nullBlockWithoutDiagonal();
    
    void rowRegular();
    void rowRegularError();
    
    void colRegular();
    void colRegularError();
    
    void completeBlockDiagonalOne();
    void completeBlockDiagonalZero();
    void completeBlockWithoutDiagonal();
    void sumOverF();
    
    void linearizing();
    void clusterHasAtLeastOneNode();
    void nodeBelongsOnlyOneCluster();
    
    void get_emptyCluster(IloCplex cplex);
    
    void setTypeObjectiveFunction(FunctionType type);
    void setObjectiveFunction(IloExpr  expr);
    
    void getMatrixBlock(IloCplex cplex);
    
    void get_tbsOne(IloCplex cplex);
    void get_tbsZero(IloCplex cplex);
    
    void get_y(IloCplex cplex);
    void get_x(IloCplex cplex);
    void get_w(IloCplex cplex);
    void get_f(IloCplex cplex);
    void get_linesError(IloCplex cplex);
    
    void sumEmptyCluster();
    void get_dsZero(IloCplex cplex);
    void get_dsOne(IloCplex cplex);
    void get_bSize(IloCplex cplex);
    
    void getRelationMatrix();
    
    void getGroup(IloCplex cplex);
    int get_fPosition(FunctionType type);
    void addFunction(FunctionDetails type);
    
    IloExpr getObjectiveFuncion();
    void w_sum();
    void blockSize();
    void get_fIndex(int index);
    void get_MapingFunctions();
    map<string,clusterGroup> group;
    
    Constraints(IloEnv env, IloModel model);
    
    void get_NullBlockDiagonalZero(IloCplex cplex);
    void get_NullBlockDiagonalOne(IloCplex cplex);
    void get_NullBlockWithoutDiagonal(IloCplex cplex);
    
    void get_CompleteBlockWithoutDiagonal(IloCplex cplex);
    void get_CompleteBlockDiagonalOne(IloCplex cplex);
    void get_CompleteBlockDiagonalZero(IloCplex cplex);
    
    void get_AllFunctions(IloCplex cplex);
    void get_rowError(IloCplex cplex);
    void get_colError(IloCplex cplex);
    
    void regularBlock();
    
    void rowDominantWithoutDiagonal();
    void rowDominantDiagonalZero();
    void rowDominantDiagonalOne();
    
    void colDominantWithoutDiagonal();
    void colDominantDiagonalOne();
    void colDominantDiagonalZero();
    
    void z_sum();
    void z_smaller_x();
    
    void linesError();
    void blockDimensions();
    void get_z(IloCplex cplex);
    void get_omega(IloCplex cplex);

    void o_bigger_lineError_plus_bigM();
    void h_bigger_o();
    void o_smaller_lineError();
    void o_smaller_z();
    void h_smaller_lineError();
    
    void get_o(IloCplex cplex);
    void get_h(IloCplex cplex);
    FunctionDetails get_fKey(int index);
    void addConstraints();
    void sharedConstraints();
    IloExpr objectiveFunction;
    map< int, FunctionDetails> fPosition;
    
    void  setTypeObjectiveFunctionFile(FunctionType type);
    
    void b_sum();
    void b_smaller_x();
    void columnsError();
    void a_bigger_columnError_plus_bigM();
    void a_smaller_columnError();
    void a_smaller_b();
    void c_smaller_columnError();
    void c_bigger_a();
    void get_columnError(IloCplex cplex);
    void adjustingErrorScale();
    void addAllConstraints();
    void penaltieMatrixOne();
    
    void columnFunctional();
    void modulusOmega();
    void rowFunctional();
    void modulusAlfa();
    
};

#endif /* Constraints_hpp */
