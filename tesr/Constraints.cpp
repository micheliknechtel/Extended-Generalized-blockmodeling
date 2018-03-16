//
//  Constraints.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 19/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Constraints.hpp"
#include "RowDominant.hpp"
#include "ColDominant.hpp"
#include <vector>

Constraints::Constraints(IloEnv env, IloModel model)
{
    this->env = env;
    this->model = model;
    
    fPSize = 0;
    
    clusterUpperBound = DataManager::getDataManager()->clusterUpperBound;
    networkSize = DataManager::getDataManager()->networkSize;
    functionSize =  DataManager::getDataManager()->functionSize;
    relationMatrix = DataManager::getDataManager()->relationMatrix;
    clusterLowerBound = DataManager::getDataManager()->clusterLowerBound;
    
    f = MultidimensionaIloArray::IloNumArray3_F(env, 0, networkSize * networkSize, "functions");
    w = MultidimensionaIloArray::IloNumArray3_W(env, 0, 1, "w");
    p = MultidimensionaIloArray::IloNumArray3_Penalties(env);
    x = MultidimensionaIloArray::IloNumVarArray2_x_without_artificial_symmetry(env, networkSize, networkSize,"x");
    
//        x = MultidimensionaIloArray::IloBoolArray2_x_without_artificial_symmetry(env, networkSize, networkSize,"x");
    y = MultidimensionaIloArray::IloNumArray4_y_without_artificial_symmetry(env, networkSize, networkSize, "y");
    
    
    
    
    if (true)
    {
        for(int i=0; i <networkSize; i++)
        {
            model.add(IloConversion(env, x[i], ILOBOOL));
        }
    }
    
//    if (true)
//    {
//        for(int i=0; i <networkSize; i++)
//            for(int j=0; j<i; j++)
//                for(int k=0; k <= min(i,clusterUpperBound-1); k++)
//                  model.add(IloConversion(env,   y[i][j][k], ILOBOOL));
//    }
    
    
    
    emptyCluster = IloNumVarArray(env, networkSize, 0,1, ILOINT);
    emptyCluster.setNames("clusterEmpty");
    
    // Regular Block, Row Regular and Col Regular - There is not Diagonal Variations!!!
    allocatingVariablesRegularBlocks();
    
    // Row Dominant Block - Diagonal Variations
    allocatingVariablesRowDominantBlock();
    
    // Column Dominant Block - Diagonal Variations
    allocatingVariablesColumnDominantBlock();
    
    // Complete Block - Diagonal Variations
    allocatingVariablesCompleteBlock();
    
    // Null Block - Diagonal Variations
    allocatingVariablesNullBlock();
    
    // Column Functional - Diagonal Variations
    allocatingVariablesColumnFunctionalBlock();
    
    // Row Functional - Diagonal Variations
    allocatingVariablesRowFunctionalBlock();
    
    // Diagonal Variables
    allocatingDiagonalVariables();
    
    typeObjectiveFunction = UNDEFINED;
    
}

void Constraints::allocatingVariablesColumnFunctionalBlock()
{
    FunctionRelease release = DataManager::getDataManager()->getDataManager()->getBlockRelease(CF);
    
    if (release!=NOT_SPECIFIED)
    {
        release = DataManager::getDataManager()->getDataManager()->getBlockRelease(CF, RF);
        omega = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "omega", release);
        
        if (DataManager::getDataManager()->getDataManager()->graph->itsSymmetricGraph)
        {
            alfa = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "alfa", release);
        }
    }
}

void Constraints::allocatingVariablesRowFunctionalBlock()
{
    FunctionRelease release = DataManager::getDataManager()->getDataManager()->getBlockRelease(RF);
    
    if (release!=NOT_SPECIFIED)
    {
        release = DataManager::getDataManager()->getDataManager()->getBlockRelease(CF, RF);
        
        alfa = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "alfa", release);
        
        if (DataManager::getDataManager()->getDataManager()->graph->itsSymmetricGraph )
        {
            omega = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "omega", release);
        }
    }
}


void Constraints::allocatingDiagonalVariables()
{
    if (DataManager::getDataManager()->getDataManager()->areThereBlockWithDiagonalVariationZero())
    {
        dsOne = MultidimensionaIloArray::IloNumArray2_tbs_c_h(env, networkSize, 0, networkSize, "dsOne", DIAGONAL);
    }
    
    if (DataManager::getDataManager()->getDataManager()->areThereBlockWithDiagonalVariationOne())
    {
        dsZero = MultidimensionaIloArray::IloNumArray2_tbs_c_h(env, networkSize, 0, networkSize, "dsZero", DIAGONAL);
    }
}

void Constraints::allocatingVariablesCompleteBlock()
{
    if(DataManager::getDataManager()->releaseCompleteBlock != NOT_SPECIFIED)
    {
        tbsZero = MultidimensionaIloArray::IloNumArray2_tbs_c_h(env, networkSize, 0, networkSize * networkSize, "tbsZero", DataManager::getDataManager()->releaseCompleteBlock);
    }
}

void Constraints::allocatingVariablesNullBlock()
{
    if (DataManager::getDataManager()->releaseNullBlock != NOT_SPECIFIED)
    {
        tbsOne = MultidimensionaIloArray::IloNumArray2_tbs_c_h(env, networkSize, 0, networkSize * networkSize, "tbsOne", DataManager::getDataManager()->releaseNullBlock);
    }
}

void Constraints::allocatingVariablesColumnDominantBlock()
{
    if (DataManager::getDataManager()->releaseColumnDominantBlock != NOT_SPECIFIED)
    {
        columnError = MultidimensionaIloArray::IloNumArray3_lineError_columnError(env,  0, networkSize, "columnError");
        a = MultidimensionaIloArray::IloNumArray3_O_A(env,  0, networkSize , "a");
        b = MultidimensionaIloArray::IloNumArray3_Z_B(env, 0, 1,  "b");
        c = MultidimensionaIloArray::IloNumArray2_tbs_c_h(env, clusterUpperBound, 0, networkSize, "c", DataManager::getDataManager()->releaseColumnDominantBlock);
        
        if (DataManager::getDataManager()->getDataManager()->graph->itsSymmetricGraph)
        {
            lineError = MultidimensionaIloArray::IloNumArray3_lineError_columnError(env,  0, networkSize, "lineError");
            o = MultidimensionaIloArray::IloNumArray3_O_A(env,  0, networkSize , "o");
            z = MultidimensionaIloArray::IloNumArray3_Z_B(env, 0, 1,  "z");
            h = MultidimensionaIloArray::IloNumArray2_tbs_c_h(env, clusterUpperBound, 0, networkSize, "h", DataManager::getDataManager()->releaseColumnDominantBlock);
        }
    }
}

void Constraints::allocatingVariablesRowDominantBlock()
{
    if (DataManager::getDataManager()->releaseRowDominantBlock != NOT_SPECIFIED)
    {
        lineError = MultidimensionaIloArray::IloNumArray3_lineError_columnError(env,  0, networkSize, "lineError");
        o = MultidimensionaIloArray::IloNumArray3_O_A(env,  0, networkSize , "o");
        z = MultidimensionaIloArray::IloNumArray3_Z_B(env, 0, 1,  "z");
        h = MultidimensionaIloArray::IloNumArray2_tbs_c_h(env, clusterUpperBound, 0, networkSize, "h", DataManager::getDataManager()->releaseRowDominantBlock);
        
        if (DataManager::getDataManager()->getDataManager()->graph->itsSymmetricGraph)
        {
            columnError = MultidimensionaIloArray::IloNumArray3_lineError_columnError(env,  0, networkSize, "columnError");
            a = MultidimensionaIloArray::IloNumArray3_O_A(env,  0, networkSize , "a");
            b = MultidimensionaIloArray::IloNumArray3_Z_B(env, 0, 1,  "b");
            c = MultidimensionaIloArray::IloNumArray2_tbs_c_h(env, clusterUpperBound, 0, networkSize, "c", DataManager::getDataManager()->releaseRowDominantBlock);
        }
    }
}

void Constraints::allocatingVariablesRegularBlocks()
{
    // Regular Block
    if (DataManager::getDataManager()->isTypeAdded(RB))
    {
        rowError = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "rowError", DataManager::getDataManager()->releaseRegularBlock);
        colError = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "colError", DataManager::getDataManager()->releaseRegularBlock);
    }
    else
    {
        // Row Regular Block
        if (DataManager::getDataManager()->releaseRegularBlock!= NOT_SPECIFIED)
        {
            rowError = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "rowError", DataManager::getDataManager()->releaseRegularBlock);
            if (DataManager::getDataManager()->getDataManager()->graph->itsSymmetricGraph)
            {
                colError = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "colError", DataManager::getDataManager()->releaseRegularBlock);
            }
        }
        // Col Regular Block
        if (DataManager::getDataManager()->releaseRegularBlock!= NOT_SPECIFIED)
        {
            colError = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "colError", DataManager::getDataManager()->releaseRegularBlock);
            if (DataManager::getDataManager()->getDataManager()->graph->itsSymmetricGraph)
            {
                rowError = MultidimensionaIloArray::IloNumVarArray3_ColError_RowError(env, networkSize, 0, networkSize, "rowError", DataManager::getDataManager()->releaseRegularBlock);
            }
        }
    }
}

/*********************************************************/
/*Shared Constraints*/
/*********************************************************/

void Constraints::diagonalSumEqualsOne()
{
    ((SharedConstraint*) this)->diagonalSumEqualsOne();
}

void Constraints::sumOverF()
{
    ((SharedConstraint*) this)->sumOverF();
}

void Constraints::diagonalSumEqualsZero()
{
    ((SharedConstraint*) this)->diagonalSumEqualsZero();
}

void Constraints::totalBlockSumEqualsOne()
{
    ((SharedConstraint*) this)->totalBlockSumEqualsOne();
}

void Constraints::totalBlockSumEqualsZero()
{
    ((SharedConstraint*) this)->totalBlockSumEqualsZero();
}

void Constraints::clusterHasAtLeastOneNode()
{
    ((SharedConstraint*) this)->clusterHasAtLeastOneNode();
};

void Constraints::nodeBelongsOnlyOneCluster()
{
    ((SharedConstraint*) this)->nodeBelongsOnlyOneCluster();
};

void Constraints::blockSize()
{
    ((SharedConstraint*) this)->blockSize();
}

void Constraints::sumEmptyCluster()
{
    ((SharedConstraint*) this)->sumEmptyCluster();
}

void Constraints::rowRegularError()
{
    ((SharedConstraint*) this)->rowRegularError();
}

void Constraints::colRegularError()
{
    ((SharedConstraint*) this)->colRegularError();
}

void Constraints::linesError()
{
    ((SharedConstraint*) this)->linesError();
}

void Constraints::columnsError()
{
    ((SharedConstraint*) this)->columnsError();
}

void Constraints::blockDimensions()
{
    ((SharedConstraint*) this)->blockDimensions();
}
/*********************************************************/
/*Row Functional Block Constraints*/
/*********************************************************/
void Constraints::rowFunctional()
{
    ((RowFunctional*) this)->rowFunctional();
}

void Constraints::modulusAlfa()
{
    ((RowFunctional*) this)->modulusAlfa();
}
/*********************************************************/
/*Column Functional Block Constraints*/
/*********************************************************/
void Constraints::columnFunctional()
{
    ((ColumnFunctional*) this)->columnFunctional();
}

void Constraints::modulusOmega()
{
    ((ColumnFunctional*) this)->modulusOmega();
}
/*********************************************************/
/*Null Block Constraints*/
/*********************************************************/

void Constraints::nullBlockDiagonalEqualsOne()
{
    ((NullBlock*) this)->nullBlockDiagonalEqualsOne();
}

void Constraints::nullBlockWithoutDiagonal()
{
    ((NullBlock*) this)->nullBlockWithoutDiagonal();
}

void Constraints::nullBlockDiagonalEqualsZero()
{
    ((NullBlock*) this)->nullBlockDiagonalEqualsZero();
}

IloExpr Constraints::getObjectiveFuncion()
{
    return objectiveFunction;
}

/*********************************************************/
/*Complete Block Constraints*/
/*********************************************************/

void Constraints::completeBlockWithoutDiagonal()
{
    ((CompleteBlock*) this)->completeBlockWithoutDiagonal();
}

void Constraints::completeBlockDiagonalOne()
{
    ((CompleteBlock*) this)->completeBlockDiagonalOne();
}

void Constraints::completeBlockDiagonalZero()
{
    ((CompleteBlock*) this)->completeBlockDiagonalZero();
}

/*********************************************************/
/*Row Regular Constraints*/
/*********************************************************/
void Constraints::rowRegular()
{
    ((RowRegular *) this)->rowRegular();
}

/*********************************************************/
/*Col Regular Constraints*/
/*********************************************************/
void Constraints::colRegular()
{
    ((ColRegular *) this)->colRegular();
}

/*********************************************************/
/*Regular Constraints*/
/*********************************************************/

void Constraints::regularBlock()
{
    ((RegularBlock *) this)->regularBlock();
}

/*********************************************************/
/*Row Dominant*/
/*********************************************************/

void Constraints::rowDominantWithoutDiagonal()
{
    ((RowDominant *) this)->rowDominantWithoutDiagonal();
}

void Constraints::rowDominantDiagonalZero()
{
    ((RowDominant *) this)->rowDominantDiagonalZero();
}

void Constraints::rowDominantDiagonalOne()
{
    ((RowDominant *) this)->rowDominantDiagonalOne();
}

/*********************************************************/
/*Col Dominant*/
/*********************************************************/

void Constraints::colDominantWithoutDiagonal()
{
    ((ColDominant *) this)->colDominantWithoutDiagonal();
}

void Constraints::colDominantDiagonalZero()
{
    ((ColDominant *) this)->colDominantDiagonalZero();
}

void Constraints::colDominantDiagonalOne()
{
    ((ColDominant *) this)->colDominantDiagonalOne();
}

/*********************************************************/
/*Linear Constraints*/
/*********************************************************/

void Constraints::linearizing()
{
    ((LinearConstraint*) this)->linearizing();
};

void Constraints::w_sum()
{
    ((LinearConstraint*) this)->w_sum();
}

void Constraints::b_sum()
{
    ((LinearConstraint*) this)->b_sum();
}

void Constraints::z_sum()
{
    ((LinearConstraint*) this)->z_sum();
}

void Constraints::z_smaller_x()
{
    ((LinearConstraint*) this)->z_smaller_x();
}

void Constraints::b_smaller_x()
{
    ((LinearConstraint*) this)->b_smaller_x();
}

void Constraints::o_bigger_lineError_plus_bigM()
{
    ((LinearConstraint*) this)->o_bigger_lineError_plus_bigM();
}

void Constraints::a_bigger_columnError_plus_bigM()
{
    ((LinearConstraint*) this)->a_bigger_columnError_plus_bigM();
}

void Constraints::h_bigger_o()
{
    ((LinearConstraint*) this)->h_bigger_o();
}

void Constraints::c_bigger_a()
{
    ((LinearConstraint*) this)->c_bigger_a();
}
void  Constraints::o_smaller_lineError()
{
    ((LinearConstraint*) this)->o_smaller_lineError();
}

void  Constraints::a_smaller_columnError()
{
    ((LinearConstraint*) this)->a_smaller_columnError();
}

void Constraints::o_smaller_z()
{
    ((LinearConstraint*) this)->o_smaller_z();
}

void Constraints::a_smaller_b()
{
    ((LinearConstraint*) this)->a_smaller_b();
}

void Constraints::h_smaller_lineError()
{
    ((LinearConstraint*) this)->h_smaller_lineError();
}

void Constraints::c_smaller_columnError()
{
    ((LinearConstraint*) this)->c_smaller_columnError();
}

/*********************************************************/
/*Extracting Methods*/
/*********************************************************/

void Constraints::get_omega(IloCplex cplex)
{
    ((Extractor*) this)->get_omega(cplex);
}

void Constraints::get_tbsOne(IloCplex cplex)
{
    ((Extractor*) this)->get_tbsOne(cplex);
}

void Constraints::get_tbsZero(IloCplex cplex)
{
    ((Extractor*) this)->get_tbsZero(cplex);
}

void Constraints::getRelationMatrix()
{
    ((Extractor*) this)->getRelationMatrix();
}

void Constraints::get_emptyCluster(IloCplex cplex)
{
    ((Extractor*) this)->get_emptyCluster(cplex);
}

void Constraints::get_y(IloCplex cplex)
{
    ((Extractor*) this)->get_y(cplex);
}

void Constraints::get_NullBlockDiagonalZero(IloCplex cplex)
{
    ((Extractor*) this)->get_NullBlockDiagonalZero(cplex);
}

void Constraints::get_x(IloCplex cplex)
{
    ((Extractor*) this)->get_x(cplex);
}

void Constraints::get_w(IloCplex cplex)
{
    ((Extractor*) this)->get_w(cplex);
}

void Constraints::get_rowError(IloCplex cplex)
{
    ((Extractor*) this)->get_rowError(cplex);
}

void Constraints::get_colError(IloCplex cplex)
{
    ((Extractor*) this)->get_colError(cplex);
}

void Constraints::get_f(IloCplex cplex)
{
    ((Extractor*) this)->get_f(cplex);
}

void  Constraints::getGroup(IloCplex cplex)
{
    ((Extractor*) this)->getGroup(cplex);
}

void Constraints::getMatrixBlock(IloCplex cplex)
{
    ((Extractor*) this)->getMatrixBlock(cplex);
}

void Constraints::get_dsOne(IloCplex cplex)
{
    ((Extractor*) this)->get_dsOne(cplex);
}

void Constraints::get_dsZero(IloCplex cplex)
{
    ((Extractor*) this)->get_dsZero(cplex);
}

void Constraints::get_bSize(IloCplex cplex)
{
    ((Extractor*) this)->get_bSize(cplex);
}
void Constraints::get_NullBlockDiagonalOne(IloCplex cplex)
{
    ((Extractor*) this)->get_NullBlockDiagonalOne(cplex);
}

void Constraints::get_NullBlockWithoutDiagonal(IloCplex cplex)
{
    ((Extractor*) this)->get_NullBlockWithoutDiagonal(cplex);
}

void  Constraints::get_CompleteBlockWithoutDiagonal(IloCplex cplex)
{
    ((Extractor*) this)->get_CompleteBlockWithoutDiagonal(cplex);
}

void Constraints::get_CompleteBlockDiagonalOne(IloCplex cplex)
{
    ((Extractor*) this)->get_CompleteBlockDiagonalOne(cplex);
}

void Constraints::get_CompleteBlockDiagonalZero(IloCplex cplex)
{
    ((Extractor*) this)->get_CompleteBlockDiagonalZero(cplex);
}

void Constraints::get_AllFunctions(IloCplex cplex)
{
    ((Extractor*) this)->get_AllFunctions(cplex);
}

void Constraints::get_linesError(IloCplex cplex)
{
    ((Extractor*) this)->get_linesError(cplex);
}

void Constraints::get_columnError(IloCplex cplex)
{
    ((Extractor*) this)->get_columnError(cplex);
}

void Constraints::get_z(IloCplex cplex)
{
    ((Extractor*) this)->get_z(cplex);
}

void Constraints::get_o(IloCplex cplex)
{
    ((Extractor*) this)->get_o(cplex);
}

void Constraints::get_h(IloCplex cplex)
{
    ((Extractor*) this)->get_h(cplex);
}

/*********************************************************/
/* Mixed Stuffs*/
/*********************************************************/


void Constraints::addConstraints()
{
    addAllConstraints();
    penaltieMatrixOne();
    //    adjustingErrorScale();
    sumOverF();
    w_sum();
}

void Constraints::addAllConstraints()
{
    int size = (int) DataManager::getDataManager()->functionMapping.size();
    
    for (int i = 0; i<size; i++)
    {
        DataManager::getDataManager()->setCurrentfDetails(i);
        setTypeObjectiveFunctionFile(DataManager::getDataManager()->functionMapping[i].type);
    }
}

void  Constraints::setTypeObjectiveFunctionFile(FunctionType type)
{
    typeObjectiveFunction = type;
    ConstraintManager::getConstraintManager()->addFunctionConstraints(type,this);
}


void Constraints::penaltieMatrixOne()
{
    int size = (int) DataManager::getDataManager()->functionMapping.size();
    
    for (int i = 0; i<size; i++)
    {
        IloNum value = 1;
        
        FunctionRelease release =  DataManager::getDataManager()->functionMapping[i].release;
        
        int limit = clusterUpperBound-1;
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if(release == DIAGONAL)
                p[i][k][0] = value;
            
            //            if (itsSymmetricGraph && !DataManager::getDataManager()->areThereNonSymmetricPropertie())
            
            if (itsSymmetricGraph)
                limit = k;
            
            for (int l = 0; l<=limit; l++)
            {
                if(release != DIAGONAL)
                    p[i][k][l] = value;
            }
        }
    }
}


void Constraints::adjustingErrorScale()
{
    int size = (int) DataManager::getDataManager()->functionMapping.size();
    
    for (int i = 0; i<size; i++)
    {
        float value = networkSize;
        
        FunctionType type  = DataManager::getDataManager()->functionMapping[i].type;
        FunctionRelease release =  DataManager::getDataManager()->functionMapping[i].release;
        
        if(type==NBDO || type==NBDZ || type==NBWD || type==CBDO || type==CBDZ || type==CBWD || type==RDDO)
            value = 1;
        
        
        int limit = clusterUpperBound-1;
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if(release == DIAGONAL)
                p[i][k][0] = value;
            
            if (itsSymmetricGraph)
                limit = k;
            
            for (int l = 0; l<=limit; l++)
            {
                if(release != DIAGONAL)
                    p[i][k][l] = value;
            }
        }
    }
}


void  Constraints::setTypeObjectiveFunction(FunctionType type)
{
    typeObjectiveFunction = type;
    
    switch (typeObjectiveFunction)
    {
        case NBDO:
            sharedConstraints();
            diagonalSumEqualsZero();
            totalBlockSumEqualsOne();
            nullBlockDiagonalEqualsOne();
            w_sum();
            break;
            
        case NBDZ:
            sharedConstraints();
            diagonalSumEqualsOne();
            totalBlockSumEqualsOne();
            nullBlockDiagonalEqualsZero();
            w_sum();
            break;
            
        case NBWD:
            sharedConstraints();
            totalBlockSumEqualsOne();
            nullBlockWithoutDiagonal();
            w_sum();
            break;
            
        case CBWD:
            sharedConstraints();
            totalBlockSumEqualsZero();
            completeBlockWithoutDiagonal();
            w_sum();
            break;
            
        case CBDO:
            sharedConstraints();
            diagonalSumEqualsZero();
            totalBlockSumEqualsZero();
            completeBlockDiagonalOne();
            w_sum();
            break;
            
        case CBDZ:
            sharedConstraints();
            diagonalSumEqualsOne();
            totalBlockSumEqualsZero();
            completeBlockDiagonalZero();
            w_sum();
            break;
            
        case RRB:
            sharedConstraints();
            rowRegular();
            rowRegularError();
            w_sum();
            break;
            
        case CRB:
            sharedConstraints();
            colRegular();
            colRegularError();
            w_sum();
            break;
            
        case RDWD:
            sharedConstraints();
            rowDominantWithoutDiagonal();
            w_sum();
            z_sum();
            z_smaller_x();
            linesError();
            o_bigger_lineError_plus_bigM();
            o_smaller_lineError();
            o_smaller_z();
            h_smaller_lineError();
            h_bigger_o();
            break;
            
        case CDWD:
            sharedConstraints();
            colDominantWithoutDiagonal();
            w_sum();
            b_sum();
            b_smaller_x();
            columnsError();
            a_bigger_columnError_plus_bigM();
            a_smaller_columnError();
            a_smaller_b();
            c_smaller_columnError();
            c_bigger_a();
            break;
            
            
        case RB:
            sharedConstraints();
            rowRegularError();
            colRegularError();
            regularBlock();
            w_sum();
            break;
            
        case ALL_FUNCTIONS:
            sharedConstraints();
            
            diagonalSumEqualsZero();
            diagonalSumEqualsOne();
            totalBlockSumEqualsZero();
            totalBlockSumEqualsOne();
            
            nullBlockDiagonalEqualsZero();
            nullBlockDiagonalEqualsOne();
            nullBlockWithoutDiagonal();
            
            completeBlockDiagonalZero();
            completeBlockDiagonalOne();
            completeBlockWithoutDiagonal();
            rowRegular();
            rowRegularError();
            colRegular();
            colRegularError();
            regularBlock();
            rowDominantWithoutDiagonal();
            z_sum();
            z_smaller_x();
            linesError();
            o_bigger_lineError_plus_bigM();
            o_smaller_lineError();
            o_smaller_z();
            h_smaller_lineError();
            h_bigger_o();
            w_sum();
            sumOverF();
            break;
            
        default:
            break;
    }
}

void Constraints::sharedConstraints()
{
    
    if (!DataManager::getDataManager()->emptyCluster)
    {
        clusterHasAtLeastOneNode();
    }
    nodeBelongsOnlyOneCluster();
    linearizing();
}

void  Constraints::setObjectiveFunction(IloExpr  expr)
{
    switch (typeObjectiveFunction)
    {
        case NBDZ:
            objectiveFunction = expr;
            LOG("NBDZ!!!");
            break;
        case NBDO:
            objectiveFunction = expr;
            LOG("NBDO!!!");
            break;
        case NBWD:
            objectiveFunction = expr;
            LOG("NBWD!!!");
            break;
        case CBDZ:
            objectiveFunction = expr;
            LOG("CBDZ!!!");
            break;
        case CBDO:
            objectiveFunction = expr;
            LOG("CBDO!!!");
            break;
        case CBWD:
            objectiveFunction = expr;
            LOG("CBWD!!!");
            break;
        case ALL_FUNCTIONS:
            objectiveFunction = expr;
            LOG("ALL_FUNCTIONS!!!");
            break;
        case UNDEFINED:
            cout<<"Error: = Objective function undefined!!!"<<endl<<endl;
            break;
        case RRB:
            objectiveFunction = expr;
            LOG("RRB !!!");
            break;
        case CRB:
            objectiveFunction = expr;
            LOG("CRB !!!");
            break;
        case RB:
            objectiveFunction = expr;
            LOG("RB !!!");
            break;
        case RDWD:
            objectiveFunction = expr;
            LOG("RDWD !!!");
            break;
        case RDDZ:
            objectiveFunction = expr;
            LOG("RDDZ !!!");
            break;
        case RDDO:
            objectiveFunction = expr;
            LOG("RDDO !!!");
            break;
        case CDDZ:
            objectiveFunction = expr;
            LOG("CDDZ !!!");
            break;
        case CDDO:
            objectiveFunction = expr;
            LOG("CDDO !!!");
            break;
        case CDWD:
            objectiveFunction = expr;
            LOG("CDWD !!!");
            break;
        case CF:
            objectiveFunction = expr;
            LOG("CF !!!");
            break;
        default:
            break;
    }
}

void Constraints::addFunction(FunctionDetails fDetails)
{
    fPosition.insert(pair<int,FunctionDetails>(fPSize,fDetails));
    fPSize++;
}

int Constraints::get_fPosition(FunctionType type)
{
    map<int, FunctionDetails>::iterator it = fPosition.begin();
    
    for (it=fPosition.begin(); it!=fPosition.end(); ++it)
    {
        if (it->second.type == type)
        {
            return it->first;
        }
    }
    cout<<"Error geting fPosition!!!";
    return NULL;
}

void Constraints::get_fIndex(int index)
{
    string strName;
    
    if (fPosition[index].name.size()==2)
    {
        strName = fPosition[index].name + "  ";
    }
    else if (fPosition[index].name.size()==3)
    {
        strName = fPosition[index].name + " ";
    }
    else
        strName = fPosition[index].name;
    
    cout<<strName+" ";
}


FunctionDetails Constraints::get_fKey(int index)
{
    return fPosition[index];
}

void Constraints::get_MapingFunctions()
{
    for (int i = 0 ; i<fPSize; i++)
    {
        cout<<"f = "<<i<<endl;
        get_fIndex(i);
    }
}
