//
//  Definitions.h
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Definitions_h
#define Definitions_h

#define SSTR( x ) static_cast< std::ostringstream &>( \
( std::ostringstream() << std::dec << "(" << x << ")" ) ).str()

#define SSTRC( x ) static_cast< std::ostringstream &>( \
( std::ostringstream() << std::dec << "{" << x << "}") ).str()

#define SSTRL( x ) static_cast< std::ostringstream &>( \
( std::ostringstream() << std::dec  << x ) ).str()

#if LOGLEVEL > 0
#define LOG(name) cout<<name<<endl;
#else
#define LOG(name)
#endif




#include "BlockError.hpp"
#include <ilcplex/ilocplex.h>

ILOSTLBEGIN

IloIntVar
typedef IloIntVar;
typedef IloArray<IloIntVarArray> IloIntVarArray2;
typedef IloArray<IloIntVarArray2> IloIntVarArray3;
typedef IloArray<IloIntVarArray3> IloIntVarArray4;

typedef IloArray<IloBoolVarArray> IloBoolVarArray2;
typedef IloArray<IloBoolVarArray2> IloBoolVarArray3;
typedef IloArray<IloBoolVarArray3> IloBoolVarArray4;

typedef IloArray<IloBoolArray> IloBoolArray2;
typedef IloArray<IloNumVarArray> IloNumVarMatrix;
typedef IloArray<IloNumArray> IloNumMatrix;

//mudança ...

typedef IloArray<IloNumVarArray>  IloNumVarArray2;
typedef IloArray<IloNumVarArray2> IloNumVarArray3;
typedef IloArray<IloNumVarArray3> IloNumVarArray4;


struct clusterGroup
{
    int *elements;
    int size;
};

enum MatrixDataType
{
    BINARY,
    EDGES,
    XML,
    LABEL,
    UNKNOW
};

enum executionSequence
{
    RANDOM,
    SEQUENTIAL
};
enum HeuristicStrategy
{
    BEST_SOLUTION,
    FIRST_EQUAL_OR_BEST_SOLUTION
};

enum FunctionType
{
    UNDEFINED,
    NBDO,
    NBDZ,
    NBWD,
    CBDO,
    CBDZ,
    CBWD,
    ALL_FUNCTIONS,
    RRB,
    CRB,
    RB,
    RDWD,
    CDWD,
    RDDO,
    RDDZ,
    CDDO,
    CDDZ,
    CF,
    RF,
    MIXED_FUNCTIONS
};

#define itFunctionType  int  it  = NBDO; it <= RF; it++

enum FunctionRelease
{
    ALL,
    DIAGONAL,
    OFF_DIAGONAL,
    NOT_SPECIFIED
};

struct FunctionDetails
{
    FunctionType type;
    FunctionRelease release;
    string name;
    bool symmetricProperty;
};

static char const *fTypeMapping[] =
{
    "UNDEFINED",
    "NBDO",
    "NBDZ",
    "NBWD",
    "CBDO",
    "CBDZ",
    "CBWD",
    "ALL_FUNCTIONS",
    "RRB",
    "CRB",
    "RB",
    "RDWD",
    "CDWD",
    "RDDO",
    "RDDZ",
    "CDDO",
    "CDDZ",
    "CF",
    "RF"
};

static char const *fReleaseMapping[] =
{
    "ALL",
    "DIAGONAL",
    "OFF_DIAGONAL"
};

static char const *constraintIndentier[] =
{
    "SHARED_CONSTRAINT",
    "DIAGONAL_SUM_EQUALS_ZERO",
    "DIAGONAL_SUM_EQUALS_ONE",
    "TOTAL_BLOCK_SUM_EQUALS_ZERO",
    "TOTAL_BLOCK_SUM_EQUALS_ONE",
    "NULLBLOCK_DIAGONAL_EQUALS_ZERO",
    "NULLBLOCK_DIAGONAL_EQUALS_ONE",
    "NULLBLOCK_WITHOUT_DIAGONAL",
    "COMPLETE_BLOCK_DIAGONAL_ZERO",
    "COMPLETE_BLOCK_DIAGONAL_ONE",
    "COMPLETE_BLOCK_WITHOUT_DIAGONAL",
    "ROW_REGULAR",
    "ROW_REGULAR_ERROR",
    "SUM_EMPTY_CLUSTER",
    "COL_REGULAR",
    "COL_REGULAR_ERROR",
    "REGULAR_BLOCK",
    "ROW_DOMINANT_WITHOUT_DIAGONAL",
    "SUM_OVER_F",
    "W_SUM",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O","COL_DOMINANT_WITHOUT_DIAGONAL",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M",
    "ROW_DOMINANT_DIAGONAL_ZERO",
    "ROW_DOMINANT_DIAGONAL_ONE",
    "COL_DOMINANT_DIAGONAL_ZERO",
    "COL_DOMINANT_DIAGONAL_ONE",
    "COLUMN_FUNCTIONAL",
    "MODULUS_OMEGA",
    "ROW_FUNCTIONAL",
    "MODULUS_ALFA"
};

enum constraintsEnum
{
    SHARED_CONSTRAINT,
    DIAGONAL_SUM_EQUALS_ZERO,
    DIAGONAL_SUM_EQUALS_ONE,
    TOTAL_BLOCK_SUM_EQUALS_ZERO,
    TOTAL_BLOCK_SUM_EQUALS_ONE,
    NULLBLOCK_DIAGONAL_EQUALS_ZERO,
    NULLBLOCK_DIAGONAL_EQUALS_ONE,
    NULLBLOCK_WITHOUT_DIAGONAL,
    COMPLETE_BLOCK_DIAGONAL_ZERO,
    COMPLETE_BLOCK_DIAGONAL_ONE,
    COMPLETE_BLOCK_WITHOUT_DIAGONAL,
    ROW_REGULAR,
    ROW_REGULAR_ERROR,
    SUM_EMPTY_CLUSTER,
    COL_REGULAR,
    COL_REGULAR_ERROR,
    REGULAR_BLOCK,
    ROW_DOMINANT_WITHOUT_DIAGONAL,
    SUMOVERF,
    W_SUM,
    Z_SUM,
    Z_SMALLER_X,
    LINES_ERROR,
    O_BIGGER_LINE_ERROR_PLUS_BIG_M,
    O_SMALLER_ERROR,
    O_SMALLER_NZ,
    H_SMALLER_LINE_ERROR,
    H_BIGGER_O,
    COL_DOMINANT_WITHOUT_DIAGONAL,
    B_SUM,
    B_SMALLER_X,
    COLUMN_ERROR,
    A_SMALLER_ERROR,
    A_SMALLER_NZ,
    C_SMALLER_COLUMN_ERROR,
    C_BIGGER_A,
    A_BIGGER_COLUMN_ERROR_PLUS_BIG_M,
    ROW_DOMINANT_DIAGONAL_ZERO,
    ROW_DOMINANT_DIAGONAL_ONE,
    COL_DOMINANT_DIAGONAL_ZERO,
    COL_DOMINANT_DIAGONAL_ONE,
    COLUMN_FUNCTIONAL,
    MODULUS_OMEGA,
    ROW_FUNCTIONAL,
    MODULUS_ALFA
};

#define itConstraintsEnum  int  it  = DIAGONAL_SUM_EQUALS_ZERO; it <= MODULUS_ALFA; it++

static string ARRAY_CF[] =
{
    "SHARED_CONSTRAINT",
    "COLUMN_FUNCTIONAL",
    "MODULUS_OMEGA",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_CF_SIZE = 4;

static string ARRAY_CF_SYM[] =
{
    "SHARED_CONSTRAINT",
    "COLUMN_FUNCTIONAL",
    "MODULUS_OMEGA",
    "MODULUS_ALFA",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_CF_SYM_SIZE = 5;

static string ARRAY_RF[] =
{
    "SHARED_CONSTRAINT",
    "ROW_FUNCTIONAL",
    "MODULUS_ALFA",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_RF_SIZE = 4;

static string ARRAY_RF_SYM[] =
{
    "SHARED_CONSTRAINT",
    "ROW_FUNCTIONAL",
    "MODULUS_OMEGA",
    "MODULUS_ALFA",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_RF_SYM_SIZE = 5;

static string ARRAY_NBDO[] =
{
    "SHARED_CONSTRAINT",
    "DIAGONAL_SUM_EQUALS_ZERO",
    "TOTAL_BLOCK_SUM_EQUALS_ONE",
    "NULLBLOCK_DIAGONAL_EQUALS_ONE"
};
const int  ARRAY_NBDO_SIZE = 4;

static string ARRAY_NBDZ[] =
{
    "SHARED_CONSTRAINT",
    "DIAGONAL_SUM_EQUALS_ONE",
    "TOTAL_BLOCK_SUM_EQUALS_ONE",
    "NULLBLOCK_DIAGONAL_EQUALS_ZERO"
};
const int  ARRAY_NBDZ_SIZE = 4;

static string ARRAY_NBWD[] =
{
    "SHARED_CONSTRAINT",
    "TOTAL_BLOCK_SUM_EQUALS_ONE",
    "NULLBLOCK_WITHOUT_DIAGONAL"
};
const int  ARRAY_NBWD_SIZE = 3;

static string ARRAY_CBDO[] =
{
    "SHARED_CONSTRAINT",
    "DIAGONAL_SUM_EQUALS_ZERO",
    "TOTAL_BLOCK_SUM_EQUALS_ZERO",
    "COMPLETE_BLOCK_DIAGONAL_ONE",
};
const int  ARRAY_CBDO_SIZE = 5;

static string ARRAY_CBDZ[] =
{
    "SHARED_CONSTRAINT",
    "DIAGONAL_SUM_EQUALS_ONE",
    "TOTAL_BLOCK_SUM_EQUALS_ZERO",
    "COMPLETE_BLOCK_DIAGONAL_ZERO"
};
const int  ARRAY_CBDZ_SIZE = 4;

static string ARRAY_CBWD[] =
{
    "SHARED_CONSTRAINT",
    "TOTAL_BLOCK_SUM_EQUALS_ZERO",
    "COMPLETE_BLOCK_WITHOUT_DIAGONAL"
};
const int  ARRAY_CBWD_SIZE = 3;

static string ARRAY_RRB[] =
{
    "SHARED_CONSTRAINT",
    "ROW_REGULAR",
    "ROW_REGULAR_ERROR",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_RRB_SIZE = 4;

static string ARRAY_RRB_SYM[] =
{
    "SHARED_CONSTRAINT",
    "ROW_REGULAR",
    "ROW_REGULAR_ERROR",
    "COL_REGULAR_ERROR",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_RRB_SYM_SIZE = 5;

static string ARRAY_CRB[] =
{
    "SHARED_CONSTRAINT",
    "COL_REGULAR",
    "COL_REGULAR_ERROR",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_CRB_SIZE = 4;

static string ARRAY_CRB_SYM[] =
{
    "SHARED_CONSTRAINT",
    "COL_REGULAR",
    "COL_REGULAR_ERROR",
    "ROW_REGULAR_ERROR",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_CRB_SYM_SIZE = 5;

static string ARRAY_CDWD[] =
{
    "SHARED_CONSTRAINT",
    "COL_DOMINANT_WITHOUT_DIAGONAL",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_CDWD_SIZE = 11;

static string ARRAY_CDWD_SYM[] =
{
    "SHARED_CONSTRAINT",
    "COL_DOMINANT_WITHOUT_DIAGONAL",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M"
};
const int  ARRAY_CDWD_SYM_SIZE = 19;

static string ARRAY_CDDO[] =
{
    "SHARED_CONSTRAINT",
    "COL_DOMINANT_DIAGONAL_ONE",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "DIAGONAL_SUM_EQUALS_ZERO"
};
const int  ARRAY_CDDO_SIZE = 12;

static string ARRAY_CDDO_SYM[] =
{
    "SHARED_CONSTRAINT",
    "COL_DOMINANT_DIAGONAL_ONE",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "DIAGONAL_SUM_EQUALS_ZERO",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M"
};
const int  ARRAY_CDDO_SYM_SIZE = 20;



static string ARRAY_CDDZ[] =
{
    "SHARED_CONSTRAINT",
    "COL_DOMINANT_DIAGONAL_ZERO",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "DIAGONAL_SUM_EQUALS_ONE"
};
const int  ARRAY_CDDZ_SIZE = 12;

static string ARRAY_CDDZ_SYM[] =
{
    "SHARED_CONSTRAINT",
    "COL_DOMINANT_DIAGONAL_ZERO",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "DIAGONAL_SUM_EQUALS_ONE",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M"
};
const int  ARRAY_CDDZ_SYM_SIZE = 20;


static string ARRAY_RDWD[] =
{
    "SHARED_CONSTRAINT",
    "ROW_DOMINANT_WITHOUT_DIAGONAL",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_RDWD_SIZE = 11;

static string ARRAY_RDWD_SYM[] =
{
    "SHARED_CONSTRAINT",
    "ROW_DOMINANT_WITHOUT_DIAGONAL",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M"
};
const int  ARRAY_RDWD_SYM_SIZE = 18;


static string ARRAY_RDDO[] =
{
    "SHARED_CONSTRAINT",
    "ROW_DOMINANT_DIAGONAL_ONE",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "DIAGONAL_SUM_EQUALS_ZERO"
};
const int  ARRAY_RDDO_SIZE = 12;

static string ARRAY_RDDO_SYM[] =
{
    "SHARED_CONSTRAINT",
    "ROW_DOMINANT_DIAGONAL_ONE",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "DIAGONAL_SUM_EQUALS_ZERO",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M"
};
const int  ARRAY_RDDO_SYM_SIZE = 20;

static string ARRAY_RDDZ[] =
{
    "SHARED_CONSTRAINT",
    "ROW_DOMINANT_DIAGONAL_ZERO",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "DIAGONAL_SUM_EQUALS_ONE"
};
const int  ARRAY_RDDZ_SIZE = 12;

static string ARRAY_RDDZ_SYM[] =
{
    "SHARED_CONSTRAINT",
    "ROW_DOMINANT_DIAGONAL_ZERO",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M",
    "SUM_EMPTY_CLUSTER",
    "DIAGONAL_SUM_EQUALS_ONE",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M"
};
const int  ARRAY_RDDZ_SYM_SIZE = 20;

static string ARRAY_RB[] =
{
    "SHARED_CONSTRAINT",
    "ROW_REGULAR_ERROR",
    "COL_REGULAR_ERROR",
    "REGULAR_BLOCK",
    "SUM_EMPTY_CLUSTER"
};
const int  ARRAY_RB_SIZE = 5;


static string ARRAY_ALL_FUNCTIONS[] = {
    "SHARED_CONSTRAINT",
    "DIAGONAL_SUM_EQUALS_ZERO",
    "DIAGONAL_SUM_EQUALS_ONE",
    "TOTAL_BLOCK_SUM_EQUALS_ZERO",
    "TOTAL_BLOCK_SUM_EQUALS_ONE",
    "NULLBLOCK_DIAGONAL_EQUALS_ZERO",
    "NULLBLOCK_DIAGONAL_EQUALS_ONE",
    "NULLBLOCK_WITHOUT_DIAGONAL",
    "COMPLETE_BLOCK_DIAGONAL_ZERO",
    "COMPLETE_BLOCK_DIAGONAL_ONE",
    "COMPLETE_BLOCK_WITHOUT_DIAGONAL",
    "ROW_REGULAR",
    "ROW_REGULAR_ERROR",
    "SUM_EMPTY_CLUSTER",
    "COL_REGULAR",
    "COL_REGULAR_ERROR",
    "REGULAR_BLOCK",
    "ROW_DOMINANT_WITHOUT_DIAGONAL",
    "SUM_OVER_F",
    "Z_SUM",
    "Z_SMALLER_X",
    "LINES_ERROR",
    "O_BIGGER_LINE_ERROR_PLUS_BIG_M",
    "O_SMALLER_ERROR",
    "O_SMALLER_NZ",
    "H_SMALLER_LINE_ERROR",
    "H_BIGGER_O",
    "COL_DOMINANT_WITHOUT_DIAGONAL",
    "B_SUM",
    "B_SMALLER_X",
    "COLUMN_ERROR",
    "A_SMALLER_ERROR",
    "A_SMALLER_NZ",
    "C_SMALLER_COLUMN_ERROR",
    "C_BIGGER_A",
    "A_BIGGER_COLUMN_ERROR_PLUS_BIG_M",
    "ROW_DOMINANT_DIAGONAL_ZERO",
    "ROW_DOMINANT_DIAGONAL_ONE",
    "COL_DOMINANT_DIAGONAL_ZERO",
    "COL_DOMINANT_DIAGONAL_ONE",
    "COLUMN_FUNCTIONAL",
    "MODULUS_OMEGA",
    "ROW_FUNCTIONAL",
    "MODULUS_ALFA"

};
const int  ARRAY_ALL_FUNCTIONS_SIZE = 42;


#endif /* Definitions_h */
