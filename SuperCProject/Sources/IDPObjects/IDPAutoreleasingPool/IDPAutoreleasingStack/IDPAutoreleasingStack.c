//
//  IDPAutoreleasingStack.c
//  SuperCProject
//
//  Created by Ievgen on 5/14/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPAutoreleasingStack.h"
#include "IDPObjectMacros.h"

#pragma mark -
#pragma mark Private Declarations

static
void IDPAutoreleasingStackSetCapacityWithSize(IDPAutoreleasingStack *stack, uint64_t size);

static
uint64_t IDPAutoreleasingStackGetCapacity(IDPAutoreleasingStack *stack);

static
void IDPAutoreleasingStackCountAddValue(IDPAutoreleasingStack *stack, int64_t delta);

static
uint64_t IDPAutoreleasingStackGetCount(IDPAutoreleasingStack *stack);

static
void IDPAutoreleasingStackSetDataWithSize(IDPAutoreleasingStack *stack, uint64_t size);

static
void IDPAutoreleasingStackSetObjectAtHead(IDPAutoreleasingStack *stack, IDPObject *object);

static
void IDPAutoreleasingStackAddObjectAtHead(IDPAutoreleasingStack *stack, IDPObject *object);

static
void IDPAutoreleasingStackRemoveObjectFromHead(IDPAutoreleasingStack *stack);

static
void IDPAutoreleasingStackResetHead(IDPAutoreleasingStack *stack);

static
IDPObject *IDPAutoreleasingStackGetHead(IDPAutoreleasingStack *stack);

static
IDPObject *IDPAutoreleasingStackGetObjectAtIndex(IDPAutoreleasingStack *stack, uint64_t index);

void IDPAutoreleasingStackSetObjectAtIndex(IDPAutoreleasingStack *stack, IDPObject *object, uint64_t index);

#pragma mark -
#pragma mark Public Implementations

void __IDPAutoreleasingStackDeallocate(IDPAutoreleasingStack *stack) {
    IDPAutoreleasingStackPopAllElements(stack);
    
    IDPAutoreleasingStackSetDataWithSize(stack, 0);
    
    __IDPObjectDeallocate(stack);
}

IDPAutoreleasingStack *IDPAutoreleasingStackCreateWithSize(uint64_t size) {
    IDPAutoreleasingStack *stack = IDPObjectCreateWithType(IDPAutoreleasingStack);
    
    IDPAutoreleasingStackSetDataWithSize(stack, size);
    
    IDPAutoreleasingStackSetCapacityWithSize(stack, size);
    
    return stack;
}

bool IDPAutoreleasingStackIsEmpty(IDPAutoreleasingStack *stack) {
    return stack ? IDPAutoreleasingStackGetCount(stack) == 0 : false;
}

bool IDPAutoreleasingStackIsFull(IDPAutoreleasingStack *stack) {
    return stack ? IDPAutoreleasingStackGetCount(stack) == IDPAutoreleasingStackGetCapacity(stack) : false;
}

void IDPAutoreleasingStackPushObject(IDPAutoreleasingStack *stack, IDPObject *object) {
    if (!stack || IDPAutoreleasingStackIsFull(stack)) {
        return;
    }
    
    IDPAutoreleasingStackAddObjectAtHead(stack, object);
    
    IDPAutoreleasingStackCountAddValue(stack, +1);
    
    IDPAutoreleasingStackResetHead(stack);
}

IDPAutoreleasingStackPopType IDPAutoreleasingStackPopObject(IDPAutoreleasingStack *stack, IDPObject **object) {
    if (!stack || IDPAutoreleasingStackIsEmpty(stack)) {
        object = NULL;
        return  IDPAutoreleasingStackPopTypeNone;
    }
    
    *object = IDPAutoreleasingStackGetHead(stack);
    
    IDPAutoreleasingStackRemoveObjectFromHead(stack);
    
    IDPAutoreleasingStackCountAddValue(stack, -1);
    
    IDPAutoreleasingStackResetHead(stack);
    
    return *object ? IDPAutoreleasingStackPopTypeObject : IDPAutoreleasingStackPopTypeNull;
}

IDPAutoreleasingStackBatchPopType IDPAutoreleasingStackPopAllElementsUntilNullOrFirst(IDPAutoreleasingStack *stack) {
    if (!stack) {
        return IDPAutoreleasingStackBatchPopTypeNone;
    }
    
    IDPAutoreleasingStackPopType popResult;
    do {
        IDPObject *object = NULL;
        popResult = IDPAutoreleasingStackPopObject(stack, &object);
    } while (IDPAutoreleasingStackPopTypeNull != popResult && !IDPAutoreleasingStackIsEmpty(stack));
    
    IDPAutoreleasingStackBatchPopType batchPopResult;
    switch (popResult) {
        case IDPAutoreleasingStackPopTypeNull:
            batchPopResult = IDPAutoreleasingStackBatchPopTypeNullRiched;
            break;
            
        case IDPAutoreleasingStackPopTypeObject:
            batchPopResult = IDPAutoreleasingStackBatchPopTypeFirstRiched;
            break;
            
        default:
            batchPopResult = IDPAutoreleasingStackBatchPopTypeNone;
            break;
    }
    
    return batchPopResult;
}

void IDPAutoreleasingStackPopAllElements(IDPAutoreleasingStack *stack) {
    if (!stack || IDPAutoreleasingStackIsEmpty(stack)) {
        return;
    }
    
    do {
        IDPAutoreleasingStackPopAllElementsUntilNullOrFirst(stack);
    } while (!IDPAutoreleasingStackIsEmpty(stack));
}

#pragma mark -
#pragma mark Private Implementations

void IDPAutoreleasingStackSetCapacityWithSize(IDPAutoreleasingStack *stack, uint64_t size) {
    IDPObjectAssign(stack, _capacity, size / sizeof(stack->_data));
}

uint64_t IDPAutoreleasingStackGetCapacity(IDPAutoreleasingStack *stack) {
    return stack ? stack->_capacity : 0;
}

void IDPAutoreleasingStackCountAddValue(IDPAutoreleasingStack *stack, int64_t delta) {
    IDPObjectAssign(stack, _count, stack->_count + delta);
}

uint64_t IDPAutoreleasingStackGetCount(IDPAutoreleasingStack *stack) {
    return stack ? stack->_count : 0;
}

void IDPAutoreleasingStackSetObjectAtIndex(IDPAutoreleasingStack *stack, IDPObject *object, uint64_t index) {
    if (!stack) {
        return;
    }
    
    IDPObject **element = stack->_data + index;
    
    if (!object) {
        IDPObjectRelease(*element);
    }
    
    *(stack->_data + index) = object;
}

IDPObject *IDPAutoreleasingStackGetObjectAtIndex(IDPAutoreleasingStack *stack, uint64_t index) {
    return stack && index < IDPAutoreleasingStackGetCount(stack) ? *(stack->_data + index) : NULL;
}

void IDPAutoreleasingStackAddObjectAtHead(IDPAutoreleasingStack *stack, IDPObject *object) {
    IDPAutoreleasingStackSetObjectAtIndex(stack, object, IDPAutoreleasingStackGetCount(stack));
}

void IDPAutoreleasingStackRemoveObjectFromHead(IDPAutoreleasingStack *stack) {
    IDPAutoreleasingStackSetObjectAtIndex(stack, NULL, IDPAutoreleasingStackGetCount(stack) - 1);
}

void IDPAutoreleasingStackSetDataWithSize(IDPAutoreleasingStack *stack, uint64_t size) {
    if (!stack) {
        return;
    }
    
    if (!stack->_data) {
        free(stack->_data);
    }
    
    if (size > 0) {
        stack->_data = calloc(1, size);
    }
}

void IDPAutoreleasingStackResetHead(IDPAutoreleasingStack *stack) {
    IDPObjectAssign(stack, _head, IDPAutoreleasingStackGetObjectAtIndex(stack, IDPAutoreleasingStackGetCount(stack) - 1));
}

IDPObject *IDPAutoreleasingStackGetHead(IDPAutoreleasingStack *stack) {
    return stack ? stack->_head : NULL;
}

