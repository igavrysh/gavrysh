//
//  IDPLinkedListEnumerator.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 5/2/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>

#include "IDPLinkedListEnumeratorPrivate.h"
#include "IDPLinkedListNode.h"
#include "IDPLinkedListPrivate.h"

#include "IDPObjectMacros.h"

#pragma mark -
#pragma mark Private Declararions

static
void IDPLinkedListEnumeratorSetValid(IDPLinkedListEnumerator *enumerator, bool valid);

static
void IDPLinkedListEnumeratorSetList(IDPLinkedListEnumerator *enumerator, IDPLinkedList *list);

static
IDPLinkedList *IDPLinkedListEnumeratorGetList(IDPLinkedListEnumerator *enumerator);

static
void IDPLinkedListEnumeratorSetNode(IDPLinkedListEnumerator *enumerator, IDPLinkedListNode *node);

static
void IDPLinkedListEnumeratorSetMutationsCount(IDPLinkedListEnumerator *enumerator, uint64_t mutationsCount);

static
uint64_t IDPLinkedListEnumeratorGetMutationsCount(IDPLinkedListEnumerator *enumarator);

static
bool IDPLinkedListEnumeratorMutationsValidate(IDPLinkedListEnumerator *enumerator);

#pragma mark -
#pragma mark Public Implementation

void __IDPLinkedListEnumeratorDeallocate(void *object) {
    IDPLinkedListEnumeratorSetList(object, NULL);
    IDPLinkedListEnumeratorSetNode(object, NULL);
    
    __IDPObjectDeallocate(object);
}

IDPLinkedListEnumerator *IDPLinkedListEnumeratorCreateWithList(IDPLinkedList *list) {
    if (NULL == list || NULL == IDPLinkedListGetHead(list)) {
        return NULL;
    }
    
    IDPLinkedListEnumerator *enumerator = IDPObjectCreateWithType(IDPLinkedListEnumerator);
    IDPLinkedListEnumeratorSetList(enumerator, list);
    IDPLinkedListEnumeratorSetMutationsCount(enumerator, IDPLinkedListGetMutationsCount(list));
    IDPLinkedListEnumeratorSetValid(enumerator, true);
    
    return enumerator;
}

void *IDPLinkedListEnumeratorGetNextObject(IDPLinkedListEnumerator *enumerator) {
    if (NULL != enumerator) {
        if (true == IDPLinkedListEnumeratorMutationsValidate(enumerator)) {
            // get current node
            IDPLinkedListNode *node = IDPLinkedListEnumeratorGetNode(enumerator);
            IDPLinkedList *list = IDPLinkedListEnumeratorGetList(enumerator);
            // find next node or get list head while first enumeration
            node = node ? IDPLinkedListNodeGetNextNode(node) : IDPLinkedListGetHead(list);
            // set current node
            IDPLinkedListEnumeratorSetNode(enumerator, node);
            
            if (!node) {
                IDPLinkedListEnumeratorSetValid(enumerator, false);
            }
            
            return IDPLinkedListNodeGetObject(node);
        }
    }
    
    return NULL;
}

void IDPLinkedListEnumeratorSetValid(IDPLinkedListEnumerator *enumerator, bool valid) {
    IDPAssignSetter(enumerator, _valid, valid);
}

bool IDPLinkedListEnumeratorIsValid(IDPLinkedListEnumerator *enumerator) {
    return enumerator && enumerator->_valid;
}

#pragma mark -
#pragma mark Private Implementations

void IDPLinkedListEnumeratorSetList(IDPLinkedListEnumerator *enumerator, IDPLinkedList *list) {
    IDPRetainSetter(enumerator, _list, list);
}

IDPLinkedList *IDPLinkedListEnumeratorGetList(IDPLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_list : NULL;
}

void IDPLinkedListEnumeratorSetNode(IDPLinkedListEnumerator *enumerator, IDPLinkedListNode *node) {
    IDPRetainSetter(enumerator, _node, node);
}

IDPLinkedListNode *IDPLinkedListEnumeratorGetNode(IDPLinkedListEnumerator *enumarator) {
    return enumarator ? enumarator->_node : NULL;
}

void IDPLinkedListEnumeratorSetMutationsCount(IDPLinkedListEnumerator *enumerator, uint64_t mutationsCount) {
    IDPAssignSetter(enumerator, _mutationsCount, mutationsCount);
}

uint64_t IDPLinkedListEnumeratorGetMutationsCount(IDPLinkedListEnumerator *enumarator) {
    return enumarator ? enumarator->_mutationsCount : 0;
}

bool IDPLinkedListEnumeratorMutationsValidate(IDPLinkedListEnumerator *enumerator) {
    if (true == IDPLinkedListEnumeratorIsValid(enumerator)) {
        IDPLinkedList *list = IDPLinkedListEnumeratorGetList(enumerator);
        assert(IDPLinkedListGetMutationsCount(list) == IDPLinkedListEnumeratorGetMutationsCount(enumerator));

        return true;
    }
    
    return false;
}


