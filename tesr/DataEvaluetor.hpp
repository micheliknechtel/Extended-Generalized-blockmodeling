//
//  DataEvaluetor.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 27/03/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef DataEvaluetor_hpp
#define DataEvaluetor_hpp

#include <stdio.h>
#include "DataControler.hpp"

class DataEvaluetor {
    
public:
    void prepareData();
    void processingData(DataControler *d );
};

#endif /* DataEvaluetor_hpp */
