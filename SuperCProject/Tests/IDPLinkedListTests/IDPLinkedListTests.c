//
//  IDPLinkedListTests.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 5/2/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>

#include "IDPLinkedListTests.h"

#include "IDPLinkedList.h"
#include "IDPLinkedListEnumerator.h"
#include "IDPPrintingFunctions.h"

#pragma mark -
#pragma mark Private Declarations

static
void IDPLinkedListEnumeratorBehaviourTest(void);

static
void IDPLinkedListOneObjectTest(void);

#pragma mark -
#pragma mark Public Implementations

void IDPLinkedListBehaviourTest(void) {
    IDPPerformTest(IDPLinkedListEnumeratorBehaviourTest);
    
    IDPPerformTest(IDPLinkedListOneObjectTest);
}

#pragma mark - 
#pragma mark Private Implementations

void IDPLinkedListEnumeratorBehaviourTest(void) {
    //  after list was created with 5 objects
    IDPLinkedList *list = IDPObjectCreateWithType(IDPLinkedList);
    for (uint index = 0; index < 5; index++) {
        IDPObject *object = IDPObjectCreateWithType(IDPObject);
        
        IDPLinkedListAddObject(list, object);
        
        IDPObjectRelease(object);
    }
    
    //  list reference count shoulb be 1
    assert(1 == IDPObjectGetReferenceCount(list));
    
    //  list count should be 5
    assert(5 == IDPLinkedListGetCount(list));
    
    //  after enumerator was created
    IDPLinkedListEnumerator *enumerator = IDPLinkedListEnumeratorFromList(list);
    
    //      list reference count should be 2
    assert(2 == IDPObjectGetReferenceCount(list));
    
    //      enumerator reference ocunt should be 1
    assert(1 == IDPObjectGetReferenceCount(enumerator));
    
    //      enumerator iterations count should be equal be 5
    uint64_t iterationsCount = 0;
    IDPObject *object = IDPLinkedListEnumeratorGetNextObject(enumerator);
    while (true == IDPLinkedListEnumeratorIsValid(enumerator)) {
        iterationsCount++;
        
        object = IDPLinkedListEnumeratorGetNextObject(enumerator);
    }
    
    assert(5 == iterationsCount);
    
    IDPObjectRelease(enumerator);
    IDPObjectRelease(list);
}

void IDPLinkedListOneObjectTest(void) {
   //   after list was created
    IDPLinkedList *list = IDPObjectCreateWithType(IDPLinkedList);
    
    //      list should be empty
    assert(true == IDPLinkedListIsEmpty(list));
    
    //      after object was created
    IDPObject *object = IDPObjectCreateWithType(IDPObject);
    
    //      list must contain an object
    assert(false == IDPLinkedListContainsObject(list, object));
    
    // after object was added to list
    IDPLinkedListAddObject(list, object);
    
    //      object referenceCount must be 2
    assert(2 == IDPObjectGetReferenceCount(object));
    
    //      list must not be empty
    assert(false == IDPLinkedListIsEmpty(list));
    
    //      list must contain object
    assert(true == IDPLinkedListContainsObject(list, object));
    
    // after object was removed from list
    IDPLinkedListRemoveObject(list, object);
    
    //      list should be empty
    assert(true == IDPLinkedListIsEmpty(list));
    
    //      list must contain object
    assert(false == IDPLinkedListContainsObject(list, object));
    
    //      object referenceCount must be 1
    assert(1 == IDPObjectGetReferenceCount(object));
    
    // after object was added 20 times
    for (uint64_t iterator = 0; iterator < 2000; iterator++) {
        IDPLinkedListAddObject(list, object);
    }
    
    //      list must not be empty
    assert(false == IDPLinkedListIsEmpty(list));
    
    //      list must contain object
    assert(true == IDPLinkedListContainsObject(list, object));
    
    
    // object reference count should be equal 2001
    assert(2001 == IDPObjectGetReferenceCount(object));
    
    // after object was removed from list
    IDPLinkedListRemoveFirstObject(list);
    
    // object reference count should be equal 2000
    assert(2000 == IDPObjectGetReferenceCount(object));
    
    // after object was removed from the list
    IDPLinkedListRemoveObject(list, object);
    
    //      object referenceCount must be 1
    assert(1 == IDPObjectGetReferenceCount(object));
    
    assert(true == IDPLinkedListIsEmpty(list));
    
    IDPObjectRelease(object);
    IDPObjectRelease(list);
}