//
//  IDPAutoreleasingStack.h
//  SuperCProject
//
//  Created by Ievgen on 5/14/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPAutoreleasingStack_h
#define IDPAutoreleasingStack_h

#include <stdbool.h>
#include <stdio.h>

#include "IDPObject.h"

typedef enum {
    IDPAutoreleasingStackPopTypeNone,
    IDPAutoreleasingStackPopTypeNull,
    IDPAutoreleasingStackPopTypeObject
} IDPAutoreleasingStackPopType;

typedef enum {
    IDPAutoreleasingStackBatchPopTypeNone,
    IDPAutoreleasingStackBatchPopTypeNullRiched,
    IDPAutoreleasingStackBatchPopTypeFirstRiched
} IDPAutoreleasingStackBatchPopType;

typedef struct IDPAutoreleasingStack IDPAutoreleasingStack;

struct IDPAutoreleasingStack {
    IDPObject _super;
    
    IDPObject **_data;
    IDPObject *_head;
    
    uint64_t _count;
    uint64_t _capacity;
};

extern
void __IDPAutoreleasingStackDeallocate(IDPAutoreleasingStack *stack);

extern
IDPAutoreleasingStack *IDPAutoreleasingStackCreateWithSize(uint64_t size);

extern
bool IDPAutoreleasingStackIsEmpty(IDPAutoreleasingStack *stack);

extern
bool IDPAutoreleasingStackIsFull(IDPAutoreleasingStack *stack);

extern
void IDPAutoreleasingStackPushObject(IDPAutoreleasingStack *stack, IDPObject *object);

extern
IDPAutoreleasingStackPopType IDPAutoreleasingStackPopObject(IDPAutoreleasingStack *stack, IDPObject **object);

extern
IDPAutoreleasingStackBatchPopType IDPAutoreleasingStackPopAllElementsUntilNullOrFirst(IDPAutoreleasingStack *stack);

extern
void IDPAutoreleasingStackPopAllElements(IDPAutoreleasingStack *stack);

#endif /* IDPAutoreleasingStack_h */
