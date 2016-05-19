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
IDPAutoreleasingStack *IDPAutoreleasingPoolGetLastStack(IDPAutoreleasingPool *pool);

static
IDPAutoreleasingStack *IDPAutoreleasingPoolGetStackBeforeStack(IDPAutoreleasingPool *pool, IDPAutoreleasingStack *stack);

static
IDPAutoreleasingStack *IDPAutoreleasingPoolAddStack(IDPAutoreleasingPool *pool);

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
    IDPSingletonObjectCreateOfType(&__pool, IDPAutoreleasingPool);
    
    IDPAutoreleasingPool *pool = IDPAutoreleasingPoolGet();
    
    if (!IDPAutoreleasingPoolGetStacksList(pool)) {
        IDPAutoreleasingPoolInitStacksList(pool);
    }
    
    IDPLinkedList *stacksList = IDPAutoreleasingPoolGetStacksList(pool);
    if (1 == IDPLinkedListGetCount(stacksList)
        && 0 == IDPAutoreleasingStackIsEmpty((IDPAutoreleasingStack *)IDPLinkedListGetFirstObject(stacksList))) {
        IDPAutoreleasingPoolSetValid(pool, true);
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
        res = IDPAutoreleasingStackPopObjects(IDPAutoreleasingPoolGetLastStack(pool));
        if (res == IDPAutoreleasingStackBatchPopTypeFirstReached) {
           IDPAutoreleasingPoolRemoveLastStackIfNeeded(pool);
        }
    } while (res != IDPAutoreleasingStackBatchPopTypeNullReached);
    
    IDPAutoreleasingStack *lastStack = IDPAutoreleasingPoolGetLastStack(pool);
    IDPAutoreleasingStack *previousStack = IDPAutoreleasingPoolGetStackBeforeStack(pool, lastStack);
    if (IDPAutoreleasingStackIsEmpty(lastStack) && !previousStack) {
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
    
    IDPAutoreleasingStack *headStack = IDPAutoreleasingPoolGetLastStack(pool);
    if (!headStack || IDPAutoreleasingStackIsFull(headStack)) {
        headStack = IDPAutoreleasingPoolAddStack(pool);
    }
    
    IDPAutoreleasingStackPushObject(headStack, object);
}

IDPAutoreleasingStack *IDPAutoreleasingPoolAddStack(IDPAutoreleasingPool *pool) {
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

IDPAutoreleasingStack *IDPAutoreleasingPoolGetLastStack(IDPAutoreleasingPool *pool) {
    if (!pool) {
        return NULL;
    }
    
    IDPLinkedList *stacks = IDPAutoreleasingPoolGetStacksList(pool);
    
    IDPAutoreleasingStack *stack = (IDPAutoreleasingStack *)IDPLinkedListGetFirstObject(stacks);
    while (stack && IDPAutoreleasingStackIsEmpty(stack)) {
        stack = IDPAutoreleasingPoolGetStackBeforeStack(pool, stack);
    }
    
    return stack;
}

IDPAutoreleasingStack *IDPAutoreleasingPoolGetStackBeforeStack(IDPAutoreleasingPool *pool, IDPAutoreleasingStack *stack) {
    if (!pool || !stack) {
        return NULL;
    }

    return (IDPAutoreleasingStack *)IDPLinkedListGetObjectBeforeObject(IDPAutoreleasingPoolGetStacksList(pool), (IDPObject *)stack);
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
    
    IDPLinkedList *stacks = IDPAutoreleasingPoolGetStacksList(pool);
    
    IDPAutoreleasingStack *lastStack = (IDPAutoreleasingStack *)IDPLinkedListGetFirstObject(stacks);
    IDPAutoreleasingStack *lastNonEmptyStack = IDPAutoreleasingPoolGetLastStack(pool);
    IDPAutoreleasingStack *previousStack = IDPAutoreleasingPoolGetStackBeforeStack(pool, lastStack);
    
    if (!lastStack || !lastNonEmptyStack || !previousStack) {
        return false;
    }
    
    if (lastStack != previousStack) {
        return true;
    }
    
    return false;
}
