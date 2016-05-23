//
//  IDPAutoreleasingStack.c
//  SuperCProject
//
//  Created by Ievgen on 5/14/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "IDPAutoreleasingStack.h"
#include "IDPObjectMacros.h"
#include "IDPAutoreleasingStackPrivate.h"

#pragma mark -
#pragma mark Private Declarations

static
void IDPAutoreleasingStackSetCapacity(IDPAutoreleasingStack *stack, uint64_t capacity);

static
uint64_t IDPAutoreleasingStackGetCapacity(IDPAutoreleasingStack *stack);

static
void IDPAutoreleasingStackCountAddValue(IDPAutoreleasingStack *stack, int64_t delta);

static
uint64_t IDPAutoreleasingStackGetCount(IDPAutoreleasingStack *stack);

static
void IDPAutoreleasingStackAddObjectAtHead(IDPAutoreleasingStack *stack, IDPObject *object);

static
void IDPAutoreleasingStackRemoveObjectFromHead(IDPAutoreleasingStack *stack);

static
IDPObject *IDPAutoreleasingStackGetHead(IDPAutoreleasingStack *stack);

static
IDPObject *IDPAutoreleasingStackGetObjectAtIndex(IDPAutoreleasingStack *stack, uint64_t index);

static
void IDPAutoreleasingStackSetObjectAtIndex(IDPAutoreleasingStack *stack, IDPObject *object, uint64_t index);

static
void IDPAutoreleasingStackPopAllObjects(IDPAutoreleasingStack *stack);

#pragma mark -
#pragma mark Public Implementations

void __IDPAutoreleasingStackDeallocate(IDPAutoreleasingStack *stack) {
    IDPAutoreleasingStackPopAllObjects(stack);
    
    IDPAutoreleasingStackSetCapacity(stack, 0);
    
    __IDPObjectDeallocate(stack);
}

IDPAutoreleasingStack *IDPAutoreleasingStackCreateWithSize(size_t size) {
    IDPAutoreleasingStack *stack;
    
    assert(0 != size);
    
    return IDPAutoreleasingStackCreateWithCapacity(size / sizeof(stack->_data));
}

IDPAutoreleasingStack *IDPAutoreleasingStackCreateWithCapacity(uint64_t capacity) {
    IDPAutoreleasingStack *stack = IDPObjectCreateWithType(IDPAutoreleasingStack);
    
    IDPAutoreleasingStackSetCapacity(stack, capacity);
    
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
}

IDPAutoreleasingStackPopType IDPAutoreleasingStackPopObject(IDPAutoreleasingStack *stack) {
    if (!stack || IDPAutoreleasingStackIsEmpty(stack)) {
        return  IDPAutoreleasingStackPopTypeNone;
    }
    
    IDPObject *object = IDPAutoreleasingStackGetHead(stack);
    
    IDPAutoreleasingStackPopType result = object ? IDPAutoreleasingStackPopTypeObject : IDPAutoreleasingStackPopTypeNull;
    
    IDPAutoreleasingStackRemoveObjectFromHead(stack);
    
    IDPAutoreleasingStackCountAddValue(stack, -1);
    
    return result;
}

IDPAutoreleasingStackBatchPopType IDPAutoreleasingStackPopObjects(IDPAutoreleasingStack *stack) {
    if (!stack) {
        return IDPAutoreleasingStackBatchPopTypeNone;
    }
    
    IDPAutoreleasingStackPopType popResult = IDPAutoreleasingStackPopTypeNone;
    do {
        popResult = IDPAutoreleasingStackPopObject(stack);
    } while (IDPAutoreleasingStackPopTypeNull != popResult && !IDPAutoreleasingStackIsEmpty(stack));
    
    return (IDPAutoreleasingStackBatchPopType)popResult;
}

#pragma mark -
#pragma mark Private Implementations

void IDPAutoreleasingStackSetCapacity(IDPAutoreleasingStack *stack, uint64_t capacity) {
    if (!stack) {
        return;
    }
    
    if (stack->_data) {
        free(stack->_data);
    }
    
    if (capacity > 0) {
        stack->_data = calloc(1, capacity * sizeof(*stack->_data));
    }
    
    IDPObjectAssign(stack, _capacity, capacity);
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

IDPObject *IDPAutoreleasingStackGetHead(IDPAutoreleasingStack *stack) {
    return stack ? IDPAutoreleasingStackGetObjectAtIndex(stack, IDPAutoreleasingStackGetCount(stack) - 1) : NULL;
}

void IDPAutoreleasingStackPopAllObjects(IDPAutoreleasingStack *stack) {
    if (!stack) {
        return;
    }
    
    while (!IDPAutoreleasingStackIsEmpty(stack)) {
        IDPAutoreleasingStackBatchPopType result = IDPAutoreleasingStackPopObjects(stack);
        if (IDPAutoreleasingStackBatchPopTypeNone == result) {
            break;
        }
    }
}


