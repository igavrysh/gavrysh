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

#include "IDPPrintingFunctions.h"

#pragma mark -
#pragma mark Private Declaration

static
void IDPLinkedListOneNodeTest();

#pragma mark -
#pragma mark Public Implementation

void IDPLinkedListBehaviorTests(void) {
    
    IDPPerformTest(IDPLinkedListOneNodeTest);
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
