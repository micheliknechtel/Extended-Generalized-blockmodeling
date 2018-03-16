//
//  ColRegular.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 19/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef ColRegular_hpp
#define ColRegular_hpp

#include <stdio.h>
#include "Constraints.hpp"

class ColRegular : public Constraints {
    
    
public:
    void colRegular();
    void colRegularAll();
    void colRegularOffDiagonal();
    void colRegularDiagonal();
};

#endif /* ColRegular_hpp */
