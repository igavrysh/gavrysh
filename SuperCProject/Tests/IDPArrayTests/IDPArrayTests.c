//
//  IDPArrayTests.c
//  SuperCProject
//
//  Created by Ievgen on 5/5/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>
#include <string.h>

#include "IDPArrayTests.h"
#include "IDPArray.h"

#include "IDPPrintingFunctions.h"


#pragma mark -
#pragma mark Private Declaration

static
void IDPArrayOneObjectContainerTest();

static
void IDPArrayMultipleObjectsContainerTest();

#pragma mark -
#pragma mark Public Implementation

void IDPArrayBehaviorTests(void) {
    
    //for (uint64_t index = 0; index < 100000; index++) {
        IDPPerformTest(IDPArrayOneObjectContainerTest);
    //}
    
    for (uint64_t index = 0; index < 100000; index++) {
        IDPPerformTest(IDPArrayMultipleObjectsContainerTest);
    }
}

#pragma mark -
#pragma mark Private Implementation

void IDPArrayOneObjectContainerTest() {
    //  after array with size 4 was created
    //      array reference count is equal 1, array size should be equal to 0
    //  after adding object into IDPArray
    //      object reference count is equal to 2
    //      array reference count is equal to 1
    //      array size should be equal to 1
    //      object at index 0 should be equal to added object
    //      index of just added object should be equal to 0
    //  after array release
    //      added object reference count should be equal to 1
    
    IDPArray *array = IDPArrayCreateWithCapacity(4);
    
    assert(1 == IDPObjectGetReferenceCount(array));
    
    assert(0 == IDPArrayGetCount(array));
    
    IDPObject *object = IDPObjectCreateWithType(IDPObject);
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPArrayAddObject(array, object);
    
    assert(2 == IDPObjectGetReferenceCount(object));
    
    assert(1 == IDPObjectGetReferenceCount(array));
    
    assert(1 == IDPArrayGetCount(array));
    
    assert(0 == IDPArrayGetIndexOfObject(array, object));
    
    assert(object == IDPArrayGetObjectAtIndex(array, 0));
    
    IDPObjectRelease(array);
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPObjectRelease(object);
}

void IDPArrayMultipleObjectsContainerTest() {
    //  after array with size 4 was created
    //      array reference count is equal 1, array size should be equal to 0
    //  after adding 10 objects into IDPArray
    //      object reference count is equal to 11
    //      array reference count is equal to 1
    //      array size should be equal to 10
    //      object at index 5 should be equal to added object
    //      index of just added object should be equal to 0
    //  after array release
    //      added object reference count should be equal to 1
    
    IDPArray *array = IDPArrayCreateWithCapacity(4);
    
    assert(1 == IDPObjectGetReferenceCount(array));
    
    assert(0 == IDPArrayGetCount(array));
    
    IDPObject *object = IDPObjectCreateWithType(IDPObject);
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    for (uint64_t index = 0; index < 10; index++) {
        IDPArrayAddObject(array, object);
        assert(2 + index == IDPObjectGetReferenceCount(object));
    }
    
    assert(11 == IDPObjectGetReferenceCount(object));
    
    assert(1 == IDPObjectGetReferenceCount(array));
    
    assert(10 == IDPArrayGetCount(array));
    
    assert(0 == IDPArrayGetIndexOfObject(array, object));
    
    assert(object == IDPArrayGetObjectAtIndex(array, 5));
    
    IDPObjectRelease(array);
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPObjectRelease(object);
}






