//
//  IDPAutoreleasingPool.c
//  SuperCProject
//
//  Created by Ievgen on 5/17/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "IDPAutoreleasingPool.h"
#include "IDPAutoreleasingStack.h"
#include "IDPObjectMacros.h"
#include "IDPLinkedListPrivate.h"
#include "IDPAutoreleasingStackPrivate.h"


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
void *IDPAutoreleasingPoolGetStackForAddingObjectWithContext(IDPAutoreleasingPool *pool, IDPAutoreleasingStackContext lastNonEmptyStackContext);

static
void IDPAutoreleasingPoolPushObject(IDPAutoreleasingPool *pool, IDPObject *object);

static
void *IDPAutoreleasingPoolGetLastStack(IDPAutoreleasingPool *pool);

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
bool IDPAutoreleasingPoolIsLastNotEmptyStack(void *stack, void *context);

static
bool IDPAutoreleasingPoolIsValid(IDPAutoreleasingPool *pool);

static
bool IDPAutoreleasingPoolShouldRemoveLastStack(IDPAutoreleasingPool *pool);

static
IDPAutoreleasingStackContext IDPAutoreleasingPoolGetLastNotEmptyStackContext(IDPAutoreleasingPool *pool);

static
IDPAutoreleasingStackContext IDPAutoreleasingPoolGetContextUsingFunctionAndStack(IDPAutoreleasingPool *pool, IDPComparisonFunction compare, IDPAutoreleasingStack *stack);

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
    
    IDPAutoreleasingStackBatchPopType result = IDPAutoreleasingStackBatchPopTypeNone;
    do {
        IDPAutoreleasingStackContext lastNonEmptyStackContext = IDPAutoreleasingPoolGetLastNotEmptyStackContext(pool);
        
        result = IDPAutoreleasingStackPopObjects(lastNonEmptyStackContext.stack);
        if (result == IDPAutoreleasingStackBatchPopTypeFirstReached) {
           IDPAutoreleasingPoolRemoveLastStackIfNeeded(pool);
        }
    } while (result != IDPAutoreleasingStackBatchPopTypeNullReached);
    
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
    
    IDPAutoreleasingStackContext lastNonEmptyStackContext = IDPAutoreleasingPoolGetLastNotEmptyStackContext(pool);
    
    if (!lastNonEmptyStackContext.stack) {
        assert(!object);

        IDPAutoreleasingPoolSetValid(pool, true);
    }
    
    if (IDPAutoreleasingPoolIsValid(pool)) {
        IDPAutoreleasingStack *stackForObjectAdding
            = IDPAutoreleasingPoolGetStackForAddingObjectWithContext(pool, lastNonEmptyStackContext);
        
        IDPAutoreleasingStackPushObject(stackForObjectAdding, object);
    }
}

void *IDPAutoreleasingPoolGetStackForAddingObjectWithContext(IDPAutoreleasingPool *pool, IDPAutoreleasingStackContext lastNonEmptyStackContext)
{
    if (!lastNonEmptyStackContext.stack || IDPAutoreleasingStackIsFull(lastNonEmptyStackContext.stack)) {
        if (lastNonEmptyStackContext.previousStack) {
            return lastNonEmptyStackContext.previousStack;
        } else {
            return IDPAutoreleasingPoolAddStack(pool);
        }
    }
    
    return lastNonEmptyStackContext.stack;
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
    
    IDPAutoreleasingStackContext lastNonEmptyStackContex = IDPAutoreleasingPoolGetLastNotEmptyStackContext(pool);
    
    if (!lastStack || !lastNonEmptyStackContex.stack || !lastNonEmptyStackContex.previousStack) {
        return false;
    }
    
    return lastStack != lastNonEmptyStackContex.previousStack;
}

bool IDPAutoreleasingPoolIsLastNotEmptyStack(void *object, void *context) {
    if (!object || !context) {
        return false;
    }
    
    IDPAutoreleasingStackContext *stackContext = context;
    
    stackContext->previousStack = stackContext->stack;
    stackContext->stack = (IDPAutoreleasingStack *)object;
    
    return !IDPAutoreleasingStackIsEmpty(stackContext->stack)
        && (!stackContext->previousStack || IDPAutoreleasingStackIsEmpty(stackContext->previousStack));
}

IDPAutoreleasingStackContext IDPAutoreleasingPoolGetLastNotEmptyStackContext(IDPAutoreleasingPool *pool) {
    return IDPAutoreleasingPoolGetContextUsingFunctionAndStack(pool, &IDPAutoreleasingPoolIsLastNotEmptyStack, NULL);
}

IDPAutoreleasingStackContext IDPAutoreleasingPoolGetContextUsingFunctionAndStack(IDPAutoreleasingPool *pool, IDPComparisonFunction compare, IDPAutoreleasingStack *stack)
{
    IDPAutoreleasingStackContext stackContext;
    memset(&stackContext, 0, sizeof(stackContext));
    
    if (!pool) {
        return stackContext;
    }
    
    stackContext.stack = stack;
    
    if (IDPLinkedListFindObjectWithContext(IDPAutoreleasingPoolGetStacksList(pool), compare, &stackContext)) {
        return stackContext;
    }
    
    memset(&stackContext, 0, sizeof(stackContext));
    return stackContext;
}
