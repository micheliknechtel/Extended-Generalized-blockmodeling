//
//  SharedConstraint.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 28/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef SharedConstraints_hpp
#define SharedConstraints_hpp

#include <stdio.h>
#include "Constraints.hpp"

class SharedConstraint: public Constraints
{
public:
    void diagonalSumEqualsOne();
    void diagonalSumEqualsZero();
    
    void totalBlockSumEqualsZero();
    void totalBlockSumEqualsZero_All();
    void totalBlockSumEqualsZero_OffDiagonal();
    void totalBlockSumEqualsZero_Diagonal();
    
    void totalBlockSumEqualsOne();
    void totalBlockSumEqualsOne_All();
    void totalBlockSumEqualsOne_OffDiagonal();
    void totalBlockSumEqualsOne_Diagonal();
    
    void sumOverF();
    void sumOverFSymmetric(FunctionRelease release, IloExpr expr_02, int i, int k, int l);
    void sumOverFNotSymmetric(FunctionRelease release, IloExpr expr_02, int i, int k, int l);
    void sumOverFMixProperties();
 
    void columnsError();
    void columnsErrorAll();
    void columnsErrorOffDiagonal();
    void columnsErrorDiagonal();
    
    void linesError();
    void linesErrorAll();
    void linesErrorOffDiagonal();
    void linesErrorDiagonal();

    void rowRegularError();
    void rowRegularErrorAll();
    void rowRegularErrorDiagonal();
    void rowRegularErrorOffDiagonal();

    void colRegularError();
    void colRegularErrorAll();
    void colRegularErrorDiagonal();
    void colRegularErrorOffDiagonal();
    
    void blockSize();
    
    void clusterHasAtLeastOneNode();
    void nodeBelongsOnlyOneCluster();
    void hello(){cout<<"OI";};
    void sumEmptyCluster();
};
#endif /* SharedConstraints_hpp */
