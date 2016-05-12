//
//  IDPLinkedListTests.c
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>
#include <string.h>

#include "IDPLinkedListNode.h"
#include "IDPLinkedList.h"
#include "IDPLinkedListTests.h"
#include "IDPLinkedListEnumerator.h"

#include "IDPPrintingFunctions.h"

#pragma mark -
#pragma mark Private Declaration

static
void IDPLinkedListOneNodeTest();

static
void IDPLinkedListAddOneNodeTest();

static
void IDPLinkedListAddMultipleNodesTest();

static
void IDPLinkedListRemoveAllObjectsTest();

static
void IDPLinkedListRemoveObjectsTest();

static
void IDPLinkedListAddRemoveObjectPerformanceTest();

static
void IDPLinkedListEnumeratorTest();

#pragma mark -
#pragma mark Public Implementation

void IDPLinkedListBehaviorTests(void) {
    IDPPerformTest(IDPLinkedListOneNodeTest);
    
    IDPPerformTest(IDPLinkedListAddOneNodeTest);
    
    IDPPerformTest(IDPLinkedListAddMultipleNodesTest);
    
    IDPPerformTest(IDPLinkedListRemoveAllObjectsTest);
    
    IDPPerformTest(IDPLinkedListRemoveObjectsTest);
    
    const uint64_t count = 10000000;
    for (uint64_t index = 0; index < count; index++) {
        IDPPerformTest(IDPLinkedListAddRemoveObjectPerformanceTest);
    }
}

void IDPLinkedListEnumeratorBehaviorTests(void) {
    IDPPerformTest(IDPLinkedListEnumeratorTest);
}

#pragma mark -
#pragma mark Private Implementation

void IDPLinkedListOneNodeTest() {
    // after first IDPLinkedListNode #1 was created
    //      create second IDPLinkedListNode, and attach it to the first one
    //      reference count of the first Node should be 1, second node Sould be 2
    // after releasing first node
    //      reference count of the second node should be 1
    
    IDPLinkedListNode *node1 = IDPLinkedListNodeCreate();
    IDPLinkedListNode *node2 = IDPLinkedListNodeCreate();
    
    IDPObject *object = IDPObjectCreateWithType(IDPObject);
    
    IDPLinkedListNodeSetData(node1, object);
    IDPLinkedListNodeSetNext(node1, node2);
    
    assert(1 == IDPObjectGetReferenceCount(node1));
    assert(2 == IDPObjectGetReferenceCount(node2));
    assert(2 == IDPObjectGetReferenceCount(object));
    
    
    IDPObjectRelease(node1);
    
    assert(1 == IDPObjectGetReferenceCount(node2));
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPObjectRelease(node2);
    IDPObjectRelease(object);
}

void IDPLinkedListAddOneNodeTest() {
    // after IDPLinkedList was created
    //      list reference count should be equal to 1
    //  after object was created and added as a node to linked list
    //      IDPObject reference count should be equal to 2
    //      list reference count should be equalt to 1
    //      IDPLinkedListGetFirstObject should return refrence to object
    //      list should contain object
    //      list should not contain newly created object which was not added to the list
    //  after removing all objects
    //      object reference count should be equal to 1
    //      list referene count should be equal to 1
    //      list nodes count should be equal to 9
    //      list should not contain object
    //      list first object should be equal to NULL
    IDPLinkedList *list = IDPObjectCreateWithType(IDPLinkedList);
    
    assert(1 == IDPObjectGetReferenceCount(list));
    
    IDPObject *object = IDPObjectCreateWithType(IDPObject);
    
    IDPLinkedListAddObject(list, object);
    
    assert(2 == IDPObjectGetReferenceCount(object));
    
    assert(1 == IDPObjectGetReferenceCount(list));
    
    assert(object == IDPLinkedListGetFirstObject(list));
    
    assert(IDPLinkedListContainsObject(list, object));
    
    IDPObject *object2 = IDPObjectCreateWithType(IDPObject);
    assert(!IDPLinkedListContainsObject(list, object2));
    IDPObjectRelease(object2);
    
    IDPLinkedListRemoveAllObjects(list);
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    assert(1 == IDPObjectGetReferenceCount(list));
    
    assert(0 == IDPLinkedListGetCount(list));
    
    assert(!IDPLinkedListContainsObject(list, object));
    
    assert(!IDPLinkedListGetFirstObject(list));
    
    IDPObjectRelease(object);
    
    IDPObjectRelease(list);
}

void IDPLinkedListAddMultipleNodesTest() {
    // after IDPLinkedList was created
    //      list reference count should be equal to 1
    
    IDPLinkedList *list = IDPObjectCreateWithType(IDPLinkedList);
    
    IDPObject *object1 = IDPObjectCreateWithType(IDPObject);
    IDPObject *object2 = IDPObjectCreateWithType(IDPObject);
    IDPObject *object3 = IDPObjectCreateWithType(IDPObject);
    IDPObject *object4 = IDPObjectCreateWithType(IDPObject);
    
    IDPLinkedListAddObject(list, object1);
    IDPLinkedListAddObject(list, object2);
    IDPLinkedListAddObject(list, object3);
    IDPLinkedListAddObject(list, object4);
    
    assert(IDPLinkedListContainsObject(list, object1));
    assert(IDPLinkedListContainsObject(list, object2));
    assert(IDPLinkedListContainsObject(list, object3));
    assert(IDPLinkedListContainsObject(list, object4));
    
    assert(2 == IDPObjectGetReferenceCount(object1));
    assert(2 == IDPObjectGetReferenceCount(object2));
    assert(2 == IDPObjectGetReferenceCount(object3));
    assert(2 == IDPObjectGetReferenceCount(object4));
    
    IDPLinkedListRemoveObject(list, object2);
    
    assert(IDPLinkedListContainsObject(list, object1));
    assert(!IDPLinkedListContainsObject(list, object2));
    assert(IDPLinkedListContainsObject(list, object3));
    assert(IDPLinkedListContainsObject(list, object4));
    assert(2 == IDPObjectGetReferenceCount(object1));
    assert(1 == IDPObjectGetReferenceCount(object2));
    assert(2 == IDPObjectGetReferenceCount(object3));
    assert(2 == IDPObjectGetReferenceCount(object4));
    
    IDPLinkedListRemoveFirstObject(list);
    assert(IDPLinkedListContainsObject(list, object1));
    assert(!IDPLinkedListContainsObject(list, object2));
    assert(IDPLinkedListContainsObject(list, object3));
    assert(!IDPLinkedListContainsObject(list, object4));
    assert(2 == IDPObjectGetReferenceCount(object1));
    assert(1 == IDPObjectGetReferenceCount(object2));
    assert(2 == IDPObjectGetReferenceCount(object3));
    assert(1 == IDPObjectGetReferenceCount(object4));
    
    assert(object3 == IDPLinkedListGetFirstObject(list));
    
    IDPLinkedListRemoveFirstObject(list);
    
    IDPLinkedListRemoveFirstObject(list);
    
    assert(0 == IDPLinkedListGetCount(list));
    
    IDPLinkedListRemoveAllObjects(list);
    
    IDPObjectRelease(list);
    
    IDPObjectRelease(object4);
    IDPObjectRelease(object3);
    IDPObjectRelease(object2);
    IDPObjectRelease(object1);
}

void IDPLinkedListRemoveAllObjectsTest() {
    IDPLinkedList *list = IDPObjectCreateWithType(IDPLinkedList);
    
    IDPObject *object1 = IDPObjectCreateWithType(IDPObject);
    IDPObject *object2 = IDPObjectCreateWithType(IDPObject);
    IDPObject *object3 = IDPObjectCreateWithType(IDPObject);
    
    IDPLinkedListAddObject(list, object1);
    IDPLinkedListAddObject(list, object2);
    IDPLinkedListAddObject(list, object3);
    
    assert(2 == IDPObjectGetReferenceCount(object1));
    assert(2 == IDPObjectGetReferenceCount(object2));
    assert(2 == IDPObjectGetReferenceCount(object3));
    
    assert(3 == IDPLinkedListGetCount(list));
    
    IDPLinkedListRemoveAllObjects(list);
    
    assert(0 == IDPLinkedListGetCount(list));
    
    assert(1 == IDPObjectGetReferenceCount(object1));
    assert(1 == IDPObjectGetReferenceCount(object2));
    assert(1 == IDPObjectGetReferenceCount(object3));
    
    IDPObjectRelease(list);
    
    IDPObjectRelease(object1);
    IDPObjectRelease(object2);
    IDPObjectRelease(object3);
}

void IDPLinkedListRemoveObjectsTest() {
    IDPLinkedList *list = IDPObjectCreateWithType(IDPLinkedList);
    
    IDPObject *object1 = IDPObjectCreateWithType(IDPObject);
    IDPObject *object2 = IDPObjectCreateWithType(IDPObject);
    IDPObject *object3 = IDPObjectCreateWithType(IDPObject);
    
    IDPLinkedListAddObject(list, object1);
    IDPLinkedListAddObject(list, object2);
    IDPLinkedListAddObject(list, object3);
    
    assert(2 == IDPObjectGetReferenceCount(object1));
    assert(2 == IDPObjectGetReferenceCount(object2));
    assert(2 == IDPObjectGetReferenceCount(object3));
    
    assert(3 == IDPLinkedListGetCount(list));
    
    IDPLinkedListRemoveObject(list, object3);
    assert(2 == IDPLinkedListGetCount(list));
    IDPLinkedListRemoveObject(list, object1);
    assert(1 == IDPLinkedListGetCount(list));
    IDPLinkedListRemoveObject(list, object2);
    assert(0 == IDPLinkedListGetCount(list));
    
    assert(1 == IDPObjectGetReferenceCount(object1));
    assert(1 == IDPObjectGetReferenceCount(object2));
    assert(1 == IDPObjectGetReferenceCount(object3));
    
    IDPObjectRelease(list);
    
    IDPObjectRelease(object1);
    IDPObjectRelease(object2);
    IDPObjectRelease(object3);
}

void IDPLinkedListAddRemoveObjectPerformanceTest() {
    const uint64_t count = 100;
    
    IDPLinkedList *list = IDPObjectCreateWithType(IDPLinkedList);
    for (uint64_t index = 0; index < count; index++) {
        IDPObject *object = IDPObjectCreateWithType(IDPObject);
        
        IDPLinkedListAddObject(list, object);
        
        assert(IDPLinkedListContainsObject(list, object));
        
        assert(index + 1 == IDPLinkedListGetCount(list));
        
        IDPObjectRelease(object);
        assert(1 == IDPObjectGetReferenceCount(object));
    }
    
    for (uint64_t index = 0; index < count; index++)  {
        assert(count - index == IDPLinkedListGetCount(list));
        
        IDPLinkedListRemoveFirstObject(list);
        
        assert(count - index - 1 == IDPLinkedListGetCount(list));
    }
    
    IDPObjectRelease(list);
}

void IDPLinkedListEnumeratorTest() {
    const uint64_t count = 2;
    
    IDPLinkedList *list = IDPObjectCreateWithType(IDPLinkedList);
    
    for (uint64_t index = 0; index < count; index++) {
        IDPObject *object = IDPObjectCreateWithType(IDPObject);
        
        IDPLinkedListAddObject(list, object);
        
        IDPObjectRelease(object);
    }
    
    IDPLinkedListEnumerator *enumerator = IDPLinkedListEnumeratorCreateWithList(list);
    uint64_t iterations = 0;
    IDPObject *object = IDPLinkedListEnumeratorGetNextObject(enumerator);
    while (true == IDPLinkedListEnumeratorIsValid(enumerator)) {
        iterations++;
        
        object = IDPLinkedListEnumeratorGetNextObject(enumerator);
    }
    
    assert(iterations == IDPLinkedListGetCount(list));
    
    IDPObjectRelease(enumerator);
    
    IDPObjectRelease(list);
}

