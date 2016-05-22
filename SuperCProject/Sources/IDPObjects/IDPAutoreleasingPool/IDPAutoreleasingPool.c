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

const size_t kIDPAutoreleasingPoolStackSize = 10;

static
void IDPAutoreleasingPoolInitStacksList(IDPAutoreleasingPool *pool);

static
IDPLinkedList *IDPAutoreleasingPoolGetStacksList(IDPAutoreleasingPool *pool);

static
void IDPAutoreleasingPoolSetStacksList(IDPAutoreleasingPool *pool, IDPLinkedList *list);

static
void *IDPAutoreleasingPoolGetStackForAddingObjectWithContext(IDPAutoreleasingPool *pool,
                                                             IDPAutoreleasingStackContext lastNonEmptyStackContext,
                                                             IDPAutoreleasingStackContext firstEmptyStackContext);

static
void IDPAutoreleasingPoolPushObject(IDPAutoreleasingPool *pool, IDPObject *object);

static
void *IDPAutoreleasingPoolGetLastStack(IDPAutoreleasingPool *pool);

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

static
IDPAutoreleasingStackContext IDPAutoreleasingPoolGetLastNotEmptyStackContext(IDPAutoreleasingPool *pool);

static
IDPAutoreleasingStackContext IDPAutoreleasingPoolGetFirstEmptyStackContext(IDPAutoreleasingPool *pool);

static
IDPAutoreleasingStackContext IDPAutoreleasingPoolGetContextUsingFunction(IDPAutoreleasingPool *pool, IDPComparisonFunction compare);

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
    IDPAutoreleasingStackContext firstEmptyStackContext = IDPAutoreleasingPoolGetFirstEmptyStackContext(pool);
    
    IDPAutoreleasingStack *stackForObjectAdding = IDPAutoreleasingPoolGetStackForAddingObjectWithContext(pool, lastNonEmptyStackContext, firstEmptyStackContext);
    
    if (!lastNonEmptyStackContext.stack) {
        assert(!object);
        if (!object) {
            IDPAutoreleasingPoolSetValid(pool, true);
        }
    }
    
    if (IDPAutoreleasingPoolIsValid(pool)) {
        IDPAutoreleasingStackPushObject(stackForObjectAdding, object);
    }
}

void *IDPAutoreleasingPoolGetStackForAddingObjectWithContext(IDPAutoreleasingPool *pool,
                                                             IDPAutoreleasingStackContext lastNonEmptyStackContext,
                                                             IDPAutoreleasingStackContext firstEmptyStackContext)
{
    if (!lastNonEmptyStackContext.stack || IDPAutoreleasingStackIsFull(lastNonEmptyStackContext.stack)) {
        if (!lastNonEmptyStackContext.previousStack) {
            return firstEmptyStackContext.stack ? firstEmptyStackContext.stack : IDPAutoreleasingPoolAddStack(pool);
        } else {
            return lastNonEmptyStackContext.previousStack;
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
    
    IDPAutoreleasingStackContext lastNonEmptyStackContex = IDPAutoreleasingPoolGetLastNotEmptyStackContext(pool);
    
    if (!lastStack || !lastNonEmptyStackContex.stack || !lastNonEmptyStackContex.previousStack) {
        return false;
    }
    
    return lastStack != lastNonEmptyStackContex.previousStack;
}

bool IDPAutoreleasingPoolIsLastNodeWithNotEmptyStack(IDPLinkedListNode *node, void *context) {
    if (!node || !context) {
        return false;
    }
    
    IDPLinkedListNodeContext *nodeContext = (IDPLinkedListNodeContext *)context;
    
    return !IDPAutoreleasingStackIsEmpty((IDPAutoreleasingStack *)IDPLinkedListNodeGetData(nodeContext->node))
        && (!nodeContext->previousNode || IDPAutoreleasingStackIsEmpty((IDPAutoreleasingStack *)IDPLinkedListNodeGetData(nodeContext->previousNode)));
}

bool IDPAutoreleasingPoolIsFirstNodeWithEmptyStack(IDPLinkedListNode *node, void *context) {
    if (!node || !context) {
        return false;
    }
    
    IDPLinkedListNodeContext *nodeContext = (IDPLinkedListNodeContext *)context;
    IDPLinkedListNode *nextNode = IDPLinkedListNodeGetNext(node);
    
    return IDPAutoreleasingStackIsEmpty((IDPAutoreleasingStack *)IDPLinkedListNodeGetData(nodeContext->node))
        && (!nextNode || !IDPAutoreleasingStackIsEmpty((IDPAutoreleasingStack *)IDPLinkedListNodeGetData(nextNode)));
}

IDPAutoreleasingStackContext IDPAutoreleasingPoolGetLastNotEmptyStackContext(IDPAutoreleasingPool *pool) {
    return IDPAutoreleasingPoolGetContextUsingFunction(pool, &IDPAutoreleasingPoolIsLastNodeWithNotEmptyStack);
}

IDPAutoreleasingStackContext IDPAutoreleasingPoolGetFirstEmptyStackContext(IDPAutoreleasingPool *pool) {
    return IDPAutoreleasingPoolGetContextUsingFunction(pool, &IDPAutoreleasingPoolIsFirstNodeWithEmptyStack);
}

IDPAutoreleasingStackContext IDPAutoreleasingPoolGetContextUsingFunction(IDPAutoreleasingPool *pool, IDPComparisonFunction compare) {
    IDPAutoreleasingStackContext stackContext;
    memset(&stackContext, 0, sizeof(stackContext));
    
    if (!pool) {
        return stackContext;
    }
    
    IDPLinkedListNodeContext nodeContext = IDPLinkedListGetContextWithFunctionAndObject(IDPAutoreleasingPoolGetStacksList(pool), compare, NULL);
    stackContext.stack = (IDPAutoreleasingStack *)IDPLinkedListNodeGetData(nodeContext.node);
    stackContext.previousStack = (IDPAutoreleasingStack *)IDPLinkedListNodeGetData(nodeContext.previousNode);
    
    return stackContext;
}
