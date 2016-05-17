//
//  IDPAutoreleasingPool.c
//  SuperCProject
//
//  Created by Ievgen on 5/17/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPAutoreleasingPool.h"
#include "IDPAutoreleasingStack.h"
#include "IDPObjectMacros.h"

#pragma mark -
#pragma mark Private Declarations

const uint64_t kIDPAutoreleasingPoolStackSize = 4096;

static
IDPLinkedList *IDPAutoreleasingPoolGetStacks(IDPAutoreleasingPool *pool);

static
void IDPAutoreleasingPoolSetStacks(IDPAutoreleasingPool *pool, IDPLinkedList *list);

static
void IDPAutoreleasingPoolPushObject(IDPAutoreleasingPool *pool, IDPObject *object);

static
IDPAutoreleasingStack *IDPAutoreleasingPoolGetHeadStack(IDPAutoreleasingPool *pool);

static
IDPAutoreleasingStack *IDPAutoreleasingPoolAddHeadStack(IDPAutoreleasingPool *pool);

static
void IDPAutoreleasingPoolRemoveHeadStack(IDPAutoreleasingPool *pool);

#pragma mark -
#pragma mark Public Implementations

void __IDPAutoreleasingPoolDeallocate(IDPAutoreleasingPool *pool) {
    IDPAutoreleasingPoolSetStacks(pool, NULL);
    
    __IDPObjectDeallocate(pool);
}

IDPAutoreleasingPool *IDPAutoreleasingPoolCreate() {
    static IDPAutoreleasingPool *pool;
    
    IDPSingletonObjectCreateOfType(&pool, IDPAutoreleasingPool);
    
    IDPAutoreleasingPoolPushObject(pool, NULL);
    
    return pool;
}

void IDPAutoreleasingPoolAddObject(IDPAutoreleasingPool *pool, IDPObject *object) {
    if (!pool) {
        return;
    }
    
    IDPAutoreleasingPoolPushObject(pool, object);
}

void IDPAutoreleasingPoolDrain(IDPAutoreleasingPool *pool) {
    if (pool) {
        return;
    }
    
    IDPAutoreleasingStackBatchPopType res = IDPAutoreleasingStackBatchPopTypeNone;
    do {
        res = IDPAutoreleasingStackPopObjects(IDPAutoreleasingPoolGetHeadStack(pool));
        IDPAutoreleasingPoolRemoveHeadStack(pool);
    } while (res != IDPAutoreleasingStackBatchPopTypeNullRiched);
}

#pragma mark -
#pragma mark Private Implementations

IDPLinkedList *IDPAutoreleasingPoolGetStacks(IDPAutoreleasingPool *pool) {
    return pool ? pool->_stacks : NULL;
}

void IDPAutoreleasingPoolSetStacks(IDPAutoreleasingPool *pool, IDPLinkedList *list) {
    IDPObjectSetStrong(pool, _stacks, list);
}

void IDPAutoreleasingPoolPushObject(IDPAutoreleasingPool *pool, IDPObject *object) {
    if (!pool) {
        return;
    }
    
    IDPAutoreleasingStack *headStack = IDPAutoreleasingPoolGetHeadStack(pool);
    if (!headStack || IDPAutoreleasingStackIsFull(headStack)) {
        headStack = IDPAutoreleasingPoolAddHeadStack(pool);
    }
    
    IDPAutoreleasingStackPushObject(headStack, object);
}

IDPAutoreleasingStack *IDPAutoreleasingPoolAddHeadStack(IDPAutoreleasingPool *pool) {
    if (!pool) {
        return NULL;
    }
    
    IDPAutoreleasingStack *stack = IDPAutoreleasingStackCreateWithSize(kIDPAutoreleasingPoolStackSize);
    
    IDPLinkedListAddObject(IDPAutoreleasingPoolGetStacks(pool), (IDPObject *)stack);
    
    IDPObjectRelease(stack);
    
    return stack;
}

void IDPAutoreleasingPoolRemoveHeadStack(IDPAutoreleasingPool *pool) {
    if (!pool) {
        return;
    }
    
    IDPLinkedListRemoveFirstObject(IDPAutoreleasingPoolGetStacks(pool));
}

IDPAutoreleasingStack *IDPAutoreleasingPoolGetHeadStack(IDPAutoreleasingPool *pool) {
    return pool ? (IDPAutoreleasingStack *)IDPLinkedListGetFirstObject(IDPAutoreleasingPoolGetStacks(pool)) : NULL;
}
