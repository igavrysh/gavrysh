//
//  IDPArrayTests.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/17/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//
#include <assert.h>

#include "IDPPrintingFunctions.h"
#include "IDPArrayTests.h"
#include "IDPArray.h"

#pragma mark -
#pragma mark Private Declarations

static
void IDPArrayOneObjectBehaviourTest(void);

static
void IDPArrayMultipleObjectBehaviourTest(void);


#pragma mark -
#pragma mark Public

void IDPArrayTestPerform(void) {
    for (uint64_t index = 0; index < 100000; index++) {
        IDPPerformTest(IDPArrayOneObjectBehaviourTest);
    }
    
    for (uint64_t index = 0; index < 100000; index++) {
        IDPPerformTest(IDPArrayMultipleObjectBehaviourTest);
    }
}

#pragma mark -
#pragma mark Private Implementations


void IDPArrayOneObjectBehaviourTest(void) {
    //  after array was created
    IDPArray *array = IDPObjectCreateWithType(IDPArray);
    
    //      array must not be NULL
    assert(NULL != array);
    
    //      array retain count be equal to 1
    uint64_t arrayRetainCount = IDPObjectGetReferenceCount(array);
    assert(1 == arrayRetainCount);
    
    //      array must be empty
    assert(0 == IDPArrayGetCount(array));

    //      array objects count must be 0
    
    //  after array was created
    IDPObject *object = IDPObjectCreateWithType(IDPObject);
    
    //      object must not be NULL
    assert(NULL != object);
    
    //      object reference count must be equal to 1
    assert(1 == IDPObjectGetReferenceCount(object));
    
    //      array must not contain an object
    assert(kIDPNotFound == IDPArrayGetIndexOfObject(array, object));
    
    //      object index in array must be invalid (object not found)
    assert(kIDPNotFound == IDPArrayGetIndexOfObject(array, object));
    
    //  after object was added to array
    IDPArrayAddObject(array, object);
    
    //      array count must be equal to 1
    assert(1 == IDPArrayGetCount(array));
    
    //      array reference count must not change
    assert(1 == arrayRetainCount);
    
    //      object index in array must be 0
    assert(0 == IDPArrayGetIndexOfObject(array, object));
    
    //      object reference count must be equal incremented by 1
    assert(2 == IDPObjectGetReferenceCount(object));
    
    //      array object at index 0 must be equal to added object
    assert(object == IDPArrayGetObjectAtIndex(array, 0));
    
    //      array must contain an object
    assert(true == IDPArrayContainsObject(array, object));
    
    //  after object at index was removed from array
    IDPArrayRemoveObjectAtIndex(array, 0);
    
    //      array count must equal to 0
    assert(0 == IDPArrayGetCount(array));
    
    //      array reference count must not change
    assert(arrayRetainCount == IDPObjectGetReferenceCount(array));
    
    //      object index in index in array must be invalid (object not found)
    assert(kIDPNotFound == IDPArrayGetIndexOfObject(array, object));
    
    //      object reference count must be decremented by 1
    assert(1 == IDPObjectGetReferenceCount(object));
    
    //      array must not contain an object
    assert(false == IDPArrayContainsObject(array, object));
    
    IDPObjectRelease(object);
    IDPObjectRelease(array);
}

void IDPArrayMultipleObjectBehaviourTest() {
    //  after one origin object was added 5 times in array
    IDPArray *array = IDPObjectCreateWithType(IDPArray);
    IDPObject *originObject = IDPObjectCreateWithType(IDPObject);
    
    for (uint64_t iterator = 0; iterator < 5; iterator++) {
        IDPArrayAddObject(array, originObject);
    }
    
    //      array count must be equal to 5
    assert(5 == IDPArrayGetCount(array));
    
    //      objects at indices 0 -4 must be equal to object
    for (uint64_t index = 0; index < 5; index++) {
        assert(IDPArrayGetObjectAtIndex(array, index) == originObject);
    }
    
    //  after added another object (not equal to origin object)
    IDPObject *object2 = IDPObjectCreateWithType(IDPObject);
    IDPArrayAddObject(array, object2);
    
    //      array count must be equal to 6
    assert(6 == IDPArrayGetCount(array));
    
    //      origin objects at inices 0-4 must be equal to irigin object
    for (uint64_t index = 0; index < 5; index++) {
        assert(IDPArrayGetObjectAtIndex(array, index) ==  originObject);
    }
    
    //      added object must be at index 5
    assert(IDPArrayGetObjectAtIndex(array, 5) == object2);

    //  after object at index 3 was removed
    IDPArrayRemoveObjectAtIndex(array, 3);
    
    //      array count must be equal to 5
    assert(5 == IDPArrayGetCount(array));
    
    //      objects at indices 0-3 must be equal to origin object
    for (uint64_t index = 0; index < 4; index++) {
        assert(IDPArrayGetObjectAtIndex(array, index) ==  originObject);
    }
    
    //      added object must be at index 4
    assert(IDPArrayGetObjectAtIndex(array, 4) == object2);
    
    //  after removing all object from array
    IDPArrayRemoveAllObjects(array);
    
    //      array must be empty
    assert(0 == IDPArrayGetCount(array));
    
    //      array must no contain origin object and object2
    assert(false == IDPArrayContainsObject(array, originObject));
    assert(false == IDPArrayContainsObject(array, object2));
    
    IDPObjectRelease(object2);
    IDPObjectRelease(originObject);
    IDPObjectRelease(array);
    
}
