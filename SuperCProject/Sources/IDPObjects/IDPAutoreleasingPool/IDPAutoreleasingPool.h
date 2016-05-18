//
//  IDPAutoreleasingPool.h
//  SuperCProject
//
//  Created by Ievgen on 5/17/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPAutoreleasingPool_h
#define IDPAutoreleasingPool_h

#include "IDPObject.h"
#include "IDPLinkedList.h"

typedef struct IDPAutoreleasingPool IDPAutoreleasingPool;

struct IDPAutoreleasingPool {
    IDPObject _super;
    
    IDPLinkedList *_stacks;
};

extern
void __IDPAutoreleasingPoolDeallocate(IDPAutoreleasingPool *pool);

extern
IDPAutoreleasingPool *IDPAutoreleasingPoolCreate();

extern
void IDPAutoreleasingPoolAddObject(IDPObject *object);

extern
void IDPAutoreleasingPoolDrain();

extern
IDPAutoreleasingPool *IDPAutoreleasingPoolGet();

#endif /* IDPAutoreleasingPool_h */
