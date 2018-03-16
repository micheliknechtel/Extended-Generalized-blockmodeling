//
//  RowRegular.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 18/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef RowRegular_hpp
#define RowRegular_hpp

#include <stdio.h>
#include "Constraints.hpp"

class RowRegular : public Constraints {
    
public:
    void rowRegular();
    void rowRegular_All();
    void rowRegular_OffDiagonal();
    void rowRegular_Diagonal();
};

#endif /* RowRegular_hpp */
