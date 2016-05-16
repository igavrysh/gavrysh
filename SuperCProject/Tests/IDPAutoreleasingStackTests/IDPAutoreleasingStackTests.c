//
//  IDPAutoreleasingStackTests.c
//  SuperCProject
//
//  Created by Ievgen on 5/13/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>

#include "IDPAutoreleasingStackTests.h"
#include "IDPAutoreleasingStack.h"
#include "IDPPrintingFunctions.h"

#pragma mark -
#pragma mark Private Declarations

static
void IDPAutoreleasingStackObjectTest(void);

static
void IDPAutoreleasingStackOneNULLPushTest(void);

static
void IDPAutoreleasingStackIsFullTest(void);

#pragma mark -
#pragma mark Public Implementations

void IDPAutoreleasingStackBehaviorTests(void) {
    IDPPerformTest(IDPAutoreleasingStackObjectTest);
    
    IDPPerformTest(IDPAutoreleasingStackOneNULLPushTest);
    
    IDPPerformTest(IDPAutoreleasingStackIsFullTest);
}

#pragma mark -
#pragma mark Private Implementation

void IDPAutoreleasingStackObjectTest(void) {
    //  after stack was created with size 512
    //      stack must be empty
    //      stack must not be full
    //  after object was created
    //      object reference count must be 1
    //      after object pushed in stack
    //          object referenece count must not change
    //          stack must not be empty
    //          stack must not be full
    //      after object was poped
    //          pop type must be PoppedObject
    //          object reference count must be decremented
    //          stack must be empty
    //          stack must not be full
    IDPAutoreleasingStack *stack = IDPAutoreleasingStackCreateWithSize(512);
    
    assert(IDPAutoreleasingStackIsEmpty(stack));
    
    assert(!IDPAutoreleasingStackIsFull(stack));
    
    IDPObject *object = IDPObjectCreateWithType(IDPObject);
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPAutoreleasingStackPushObject(stack, object);
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    assert(!IDPAutoreleasingStackIsEmpty(stack));
    
    assert(!IDPAutoreleasingStackIsFull(stack));

    IDPAutoreleasingStackPopType res = IDPAutoreleasingStackPopObject(stack);
    
    assert(IDPAutoreleasingStackPopTypeObject == res);
    
    assert(0 == IDPObjectGetReferenceCount(object));
    
    assert(IDPAutoreleasingStackIsEmpty(stack));
    
    assert(!IDPAutoreleasingStackIsFull(stack));
    
    IDPObjectRelease(stack);
}

void IDPAutoreleasingStackOneNULLPushTest(void) {
    //  after stack was created with size 512 (64 pointers to it)
    //      stack must be empty
    //      stack must not be full
    //  after NULL pushed to stack
    //      stack must not be empty
    //      stack must not be full
    //  after one object was poped
    //      stack must be empty
    //      stack must not be full
    
    IDPAutoreleasingStack *stack = IDPAutoreleasingStackCreateWithSize(512);
    
    assert(IDPAutoreleasingStackIsEmpty(stack));
    
    assert(!IDPAutoreleasingStackIsFull(stack));
    
    IDPAutoreleasingStackPushObject(stack, NULL);
    
    assert(!IDPAutoreleasingStackIsEmpty(stack));
    
    assert(!IDPAutoreleasingStackIsFull(stack));
    
    IDPAutoreleasingStackPopType res = IDPAutoreleasingStackPopObject(stack);
    
    assert(IDPAutoreleasingStackPopTypeNull == res);
    
    assert(IDPAutoreleasingStackIsEmpty(stack));
    
    assert(!IDPAutoreleasingStackIsFull(stack));
    
    IDPObjectRelease(stack);
}

void IDPAutoreleasingStackIsFullTest(void) {
    //  after stack was created for 64 objects
    //      stack must be empty
    //      stack must not be full
    //  after object was created
    //      after object pushed in stack 64 times
    //          object referenece count must not change
    //          stack must not be empty
    //          stack must be full
    //      after object was poped
    //          pop type must be PoppedObject
    //          object reference count must be decremented
    //          stack must not be empty
    //          stack must not be full
    //      after all objects was poped
    //          stack must be empty
    //          stack must be not full
    
    uint64_t count = 64;
    
    IDPAutoreleasingStack *stack = IDPAutoreleasingStackCreateWithSize(count * sizeof(stack->_data));
    
    assert(IDPAutoreleasingStackIsEmpty(stack));
    
    assert(!IDPAutoreleasingStackIsFull(stack));
    
    IDPObject *object = IDPObjectCreateWithType(IDPObject);
    IDPObjectRetain(object);
    
    assert(2 == IDPObjectGetReferenceCount(object));
    
    IDPAutoreleasingStackPushObject(stack, object);
    
    assert(2 == IDPObjectGetReferenceCount(object));
    
    for (int index = 0; index < count; index++) {
        IDPAutoreleasingStackPushObject(stack, object);
    }
    
    assert(!IDPAutoreleasingStackIsEmpty(stack));
    assert(IDPAutoreleasingStackIsFull(stack));
    assert(2 == IDPObjectGetReferenceCount(object));
    
    IDPAutoreleasingStackPopObject(stack);
    
    assert(!IDPAutoreleasingStackIsEmpty(stack));
    assert(!IDPAutoreleasingStackIsFull(stack));
    assert(1 == IDPObjectGetReferenceCount(object));
    
    while (!IDPAutoreleasingStackIsEmpty(stack)) {
        IDPAutoreleasingStackBatchPopType result = IDPAutoreleasingStackPopObjects(stack);
        if (IDPAutoreleasingStackBatchPopTypeNone == result) {
            break;
        }
    }
    
    assert(IDPAutoreleasingStackIsEmpty(stack));
    assert(!IDPAutoreleasingStackIsFull(stack));
    
    IDPObjectRelease(stack);
}
