//
//  IDPAutoreleasingStackPrivate.h
//  SuperCProject
//
//  Created by Ievgen on 5/22/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPAutoreleasingStackPrivate_h
#define IDPAutoreleasingStackPrivate_h

#include "IDPAutoreleasingStack.h"

typedef struct IDPAutoreleasingStackContext IDPAutoreleasingStackContext;

struct IDPAutoreleasingStackContext {
    IDPAutoreleasingStack *previousStack;
    
    IDPAutoreleasingStack *stack;
};

#endif /* IDPAutoreleasingStackPrivate_h */
