//
//  LinearConstraint.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 29/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef LinearConstraint_hpp
#define LinearConstraint_hpp

#include <stdio.h>
#include "Constraints.hpp"

class LinearConstraint: public Constraints
{
    
public:
    void linearizing();
    
    void xik_plus_xjl_plus_yijkl_equals_one();
    void y_smaller_xjl();
    void y_smaller_xik();
    void quadraticAssignmentProblem();
    
    void w_sum();
    
    void z_smaller_x();
    void z_smaller_x_All();
    void z_smaller_x_OffDiagonal();
    void z_smaller_x_Diagonal();
    
    void z_sum();
    void z_sum_All();
    void z_sum_OffDiagonal();
    void z_sum_Diagonal();
    
    void o_bigger_lineError_plus_bigM();
    void o_bigger_lineError_plus_bigM_All();
    void o_bigger_lineError_plus_bigM_OffDiagonal();
    void o_bigger_lineError_plus_bigM_Diagonal();
    
    void o_smaller_lineError();
    void o_smaller_Error_All();
    void o_smaller_Error_OffDiagonal();
    void o_smaller_Error_Diagonal();
    
    void h_bigger_o();
    void h_bigger_o_All();
    void h_bigger_o_OffDiagonal();
    void h_bigger_o_Diagonal();
    
    void h_smaller_lineError();
    void h_smaller_lineErrorAll();
    void h_smaller_lineErrorOffDiagonal();
    void h_smaller_lineErrorDiagonal();
    
    void o_smaller_z();
    void o_smaller_NzAll();
    void o_smaller_NzOffDiagonal();
    void o_smaller_NzDiagonal();
    void add_o_smaller_Nz(int k, int l, int i);
    
    void b_sum();
    void b_sum_All();
    void b_sum_OffDiagonal();
    void b_sum_Diagonal();
    
    void b_smaller_x();
    void b_smaller_x_All();
    void b_smaller_x_OffDiagonal();
    void b_smaller_x_Diagonal();
    
    void a_bigger_columnError_plus_bigM();
    void a_bigger_columnError_plus_bigM_All();
    void a_bigger_columnError_plus_bigM_OffDiagonal();
    void a_bigger_columnError_plus_bigM_Diagonal();
    
    void a_smaller_columnError();
    void a_smaller_Error_All();
    void a_smaller_Error_OffDiagonal();
    void a_smaller_Error_Diagonal();
    
    void a_smaller_b();
    void a_smaller_NzAll();
    void a_smaller_NzOffDiagonal();
    void a_smaller_NzDiagonal();
    void add_a_smaller_Nz(int k, int l, int i);
    
    void c_bigger_a();
    void c_bigger_a_All();
    void c_bigger_a_OffDiagonal();
    void c_bigger_a_Diagonal();
    
    void c_smaller_columnError();
    void c_smaller_columnError_All();
    void c_smaller_columnError_OffDiagonal();
    void c_smaller_columnError_Diagonal();
};
#endif /* LinearConstraint_hpp */
