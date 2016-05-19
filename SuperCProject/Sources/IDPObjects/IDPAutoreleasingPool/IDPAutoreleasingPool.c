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

const size_t kIDPAutoreleasingPoolStackSize = 4096;

static
void IDPAutoreleasingPoolInitStacksList(IDPAutoreleasingPool *pool);

static
IDPLinkedList *IDPAutoreleasingPoolGetStacksList(IDPAutoreleasingPool *pool);

static
void IDPAutoreleasingPoolSetStacksList(IDPAutoreleasingPool *pool, IDPLinkedList *list);

static
void IDPAutoreleasingPoolPushObject(IDPAutoreleasingPool *pool, IDPObject *object);

static
void *IDPAutoreleasingPoolGetLastStack(IDPAutoreleasingPool *pool);

static
void *IDPAutoreleasingPoolGetLastNonEmptyStack(IDPAutoreleasingPool *pool);

static
void *IDPAutoreleasingPoolGetStackBeforeStack(IDPAutoreleasingPool *pool, IDPAutoreleasingStack *stack);

static
void *IDPAutoreleasingPoolGetStackAfterStack(IDPAutoreleasingPool *pool, IDPAutoreleasingStack *stack);

static
void *IDPAutoreleasingPoolAddStack(IDPAutoreleasingPool *pool);

static
void IDPAutoreleasingPoolRemoveLastStackIfNeeded(IDPAutoreleasingPool *pool);

static
void IDPAutoreleasingPoolRemoveLastStack(IDPAutoreleasingPool *pool);

static
void IDPAutoreleasingPoolSetValid(IDPAutoreleasingPool *pool, bool isValid);

static
bool IDPAutoreleasingPoolIsValid(IDPAutoreleasingPool *pool);

static
bool IDPAutoreleasingPoolShouldRemoveLastStack(IDPAutoreleasingPool *pool);

#pragma mark -
#pragma mark Public Implementations

void __IDPAutoreleasingPoolDeallocate(IDPAutoreleasingPool *pool) {
    IDPAutoreleasingPoolSetStacksList(pool, NULL);
    
    __IDPObjectDeallocate(pool);
}

static IDPAutoreleasingPool *__pool = NULL;

IDPAutoreleasingPool *IDPAutoreleasingPoolGet() {
    return __pool;
}

IDPAutoreleasingPool *IDPAutoreleasingPoolCreate() {
    IDPSingletonObjectCreateWithType(&__pool, IDPAutoreleasingPool);
    
    IDPAutoreleasingPool *pool = IDPAutoreleasingPoolGet();
    
    if (!IDPAutoreleasingPoolGetStacksList(pool)) {
        IDPAutoreleasingPoolInitStacksList(pool);
    }
    
    IDPAutoreleasingPoolPushObject(pool, NULL);
    
    return pool;
}

void IDPAutoreleasingPoolAddObject(IDPObject *object) {
    IDPAutoreleasingPool *pool = IDPAutoreleasingPoolGet();
    if (!pool) {
        return;
    }
    
    IDPAutoreleasingPoolPushObject(pool, object);
}

void IDPAutoreleasingPoolDrain() {
    IDPAutoreleasingPool *pool = IDPAutoreleasingPoolGet();
    if (!pool) {
        return;
    }
    
    IDPAutoreleasingStackBatchPopType res = IDPAutoreleasingStackBatchPopTypeNone;
    do {
        res = IDPAutoreleasingStackPopObjects(IDPAutoreleasingPoolGetLastNonEmptyStack(pool));
        if (res == IDPAutoreleasingStackBatchPopTypeFirstReached) {
           IDPAutoreleasingPoolRemoveLastStackIfNeeded(pool);
        }
    } while (res != IDPAutoreleasingStackBatchPopTypeNullReached);
    
    IDPAutoreleasingStack *lastStack = IDPAutoreleasingPoolGetLastStack(pool);
    IDPAutoreleasingStack *nextStack = IDPAutoreleasingPoolGetStackAfterStack(pool, lastStack);
    if (IDPAutoreleasingStackIsEmpty(lastStack) && !nextStack) {
        IDPAutoreleasingPoolSetValid(pool, false);
    }
}

#pragma mark -
#pragma mark Private Implementations

void IDPAutoreleasingPoolInitStacksList(IDPAutoreleasingPool *pool) {
    IDPLinkedList *stacksList = IDPObjectCreateWithType(IDPLinkedList);
    
    IDPObjectSetStrong(pool, _stacksList, stacksList);
    
    IDPObjectRelease(stacksList);
}

IDPLinkedList *IDPAutoreleasingPoolGetStacksList(IDPAutoreleasingPool *pool) {
    return pool ? pool->_stacksList : NULL;
}

void IDPAutoreleasingPoolSetStacksList(IDPAutoreleasingPool *pool, IDPLinkedList *list) {
    IDPObjectSetStrong(pool, _stacksList, list);
}

void IDPAutoreleasingPoolPushObject(IDPAutoreleasingPool *pool, IDPObject *object) {
    if (!pool) {
        return;
    }
    
    IDPAutoreleasingStack *headStack = IDPAutoreleasingPoolGetLastNonEmptyStack(pool);
    if (!headStack || IDPAutoreleasingStackIsFull(headStack)) {
        if (!headStack && !object) {
            IDPAutoreleasingPoolSetValid(pool, true);
        }
        
        headStack = IDPAutoreleasingPoolGetLastStack(pool);
        if (!headStack) {
            headStack = IDPAutoreleasingPoolAddStack(pool);
        }
    }
    
    if (IDPAutoreleasingPoolIsValid(pool)) {
        IDPAutoreleasingStackPushObject(headStack, object);
    }
}

void *IDPAutoreleasingPoolAddStack(IDPAutoreleasingPool *pool) {
    if (!pool) {
        return NULL;
    }
    
    IDPAutoreleasingStack *stack = IDPAutoreleasingStackCreateWithSize(kIDPAutoreleasingPoolStackSize);
    
    IDPLinkedListAddObject(IDPAutoreleasingPoolGetStacksList(pool), (IDPObject *)stack);
    
    IDPObjectRelease(stack);
    
    return stack;
}

void IDPAutoreleasingPoolRemoveLastStackIfNeeded(IDPAutoreleasingPool *pool) {
    if (IDPAutoreleasingPoolShouldRemoveLastStack(pool)) {
        IDPAutoreleasingPoolRemoveLastStack(pool);
    }
}

void IDPAutoreleasingPoolRemoveLastStack(IDPAutoreleasingPool *pool) {
    if (!pool) {
        return;
    }
    
    IDPLinkedListRemoveFirstObject(IDPAutoreleasingPoolGetStacksList(pool));
}

void *IDPAutoreleasingPoolGetLastStack(IDPAutoreleasingPool *pool) {
    return pool ? (IDPAutoreleasingStack *)IDPLinkedListGetFirstObject(IDPAutoreleasingPoolGetStacksList(pool)) : NULL;
}

void *IDPAutoreleasingPoolGetLastNonEmptyStack(IDPAutoreleasingPool *pool) {
    if (!pool) {
        return NULL;
    }
    
    IDPAutoreleasingStack *stack = IDPAutoreleasingPoolGetLastStack(pool);
    
    while (stack && IDPAutoreleasingStackIsEmpty(stack)) {
        stack = IDPAutoreleasingPoolGetStackAfterStack(pool, stack);
    }
    
    return stack;
}

void *IDPAutoreleasingPoolGetStackBeforeStack(IDPAutoreleasingPool *pool, IDPAutoreleasingStack *stack) {
    if (!pool || !stack) {
        return NULL;
    }

    return (IDPAutoreleasingStack *)IDPLinkedListGetObjectBeforeObject(IDPAutoreleasingPoolGetStacksList(pool), (IDPObject *)stack);
}

void *IDPAutoreleasingPoolGetStackAfterStack(IDPAutoreleasingPool *pool, IDPAutoreleasingStack *stack) {
    if (!pool || !stack) {
        return NULL;
    }
    
    return (IDPAutoreleasingStack *)IDPLinkedListGetObjectAfterObject(IDPAutoreleasingPoolGetStacksList(pool), (IDPObject *)stack);
}

void IDPAutoreleasingPoolSetValid(IDPAutoreleasingPool *pool, bool isValid) {
    IDPObjectAssign(pool, _isValid, isValid);
}

bool IDPAutoreleasingPoolIsValid(IDPAutoreleasingPool *pool) {
    return pool ? pool->_isValid : false;
}

bool IDPAutoreleasingPoolShouldRemoveLastStack(IDPAutoreleasingPool *pool) {
    if (!pool) {
        return false;
    }
    
    IDPAutoreleasingStack *lastStack = IDPAutoreleasingPoolGetLastStack(pool);
    
    IDPAutoreleasingStack *lastNonEmptyStack = IDPAutoreleasingPoolGetLastNonEmptyStack(pool);
    
    IDPAutoreleasingStack *previousStack = IDPAutoreleasingPoolGetStackBeforeStack(pool, lastNonEmptyStack);
    
    if (!lastStack || !lastNonEmptyStack || !previousStack) {
        return false;
    }
    
    return lastStack != previousStack;
}
