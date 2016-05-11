//
//  IDPLinkedListEnumerator.c
//  SuperCProject
//
//  Created by Student 104 on 5/10/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPLinkedListEnumerator.h"
#include "IDPObjectMacros.h"
#include "IDPLinkedListPrivate.h"
#include "IDPLinkedListEnumeratorPrivate.h"
#include "IDPLinkedListNode.h"

#pragma mark -
#pragma mark Private Declarations

static
void IDPLinkedListEnumeratorSetMutationsCount(IDPLinkedListEnumerator *enumerator, uint64_t mutationsCount);

static
uint64_t IDPLinkedListEnumeratorGetMutationsCount(IDPLinkedListEnumerator *enumerator);

static
void IDPLinkedListEnumeratorSetValid(IDPLinkedListEnumerator *enumerator, bool isValid);

static
void IDPLinkedListEnumeratorSetList(IDPLinkedListEnumerator *enumerator, IDPLinkedList *list);

static
void IDPLinkedListEnumeratorSetNode(IDPLinkedListEnumerator *enumerator, IDPLinkedListNode *node);

static
IDPLinkedList *IDPLinkedListEnumeratorGetList(IDPLinkedListEnumerator *enumerator);

#pragma mark -
#pragma mark Public Implementations

void __IDPLinkedListEnumeratorDeallocate(IDPLinkedListEnumerator *enumerator) {
    IDPLinkedListEnumeratorSetList(enumerator, NULL);
    
    IDPLinkedListEnumeratorSetNode(enumerator, NULL);
    
    IDPObjectRelease(enumerator);
}

IDPLinkedListEnumerator *IDPLinkedListEnumeratorCreateWithList(IDPLinkedList *list) {
    IDPLinkedListEnumerator *enumerator = IDPObjectCreateWithType(IDPLinkedListEnumerator);
    
    IDPLinkedListEnumeratorSetList(enumerator, list);
    
    IDPLinkedListEnumeratorSetMutationsCount(enumerator,
                                             IDPLinkedListGetMutationsCount(list));
    
    IDPLinkedListEnumeratorSetValid(enumerator, true);
    
    return enumerator;
}

IDPObject *IDPLinkedListEnumeratorGetNextObject(IDPLinkedListEnumerator *enumerator) {
    if (!enumerator || !IDPLinkedListEnumeratorIsValid(enumerator)) {
        return NULL;
    }
    
    IDPLinkedListNode *node = IDPLinkedListEnumeratorGetNode(enumerator);
    
    node = !node ? IDPLinkedListGetHead(IDPLinkedListEnumeratorGetList(enumerator)) :
        IDPLinkedListNodeGetNext(node);
    
    if (!node) {
        IDPLinkedListEnumeratorSetValid(enumerator, false);
    }
    
    IDPLinkedListEnumeratorSetNode(enumerator, node);
    
    return IDPLinkedListNodeGetData(IDPLinkedListEnumeratorGetNode(enumerator));
}

#pragma mark -
#pragma mark Private Implementations

void IDPLinkedListEnumeratorSetMutationsCount(IDPLinkedListEnumerator *enumerator, uint64_t mutationsCount) {
    if (!enumerator) {
        return;
    }
    
    enumerator->_mutationsCount = mutationsCount;
}

uint64_t IDPLinkedListEnumeratorGetMutationsCount(IDPLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_mutationsCount : 0;
}

void IDPLinkedListEnumeratorSetValid(IDPLinkedListEnumerator *enumerator, bool isValid) {
    if (!enumerator) {
        return;
    }
    
    enumerator->_isValid = isValid;
}

bool IDPLinkedListEnumeratorIsValid(IDPLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_isValid : false;
}

void IDPLinkedListEnumeratorSetList(IDPLinkedListEnumerator *enumerator, IDPLinkedList *list) {
    IDPObjectSetStrong(enumerator, _list, list);
}

IDPLinkedList *IDPLinkedListEnumeratorGetList(IDPLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_list : false;
}

void IDPLinkedListEnumeratorSetNode(IDPLinkedListEnumerator *enumerator, IDPLinkedListNode *node) {
    IDPObjectSetStrong(enumerator, _node, node);
}

IDPLinkedListNode *IDPLinkedListEnumeratorGetNode(IDPLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_node : NULL;
}

bool IDPLinkedListEnumeratorValidate(IDPLinkedListEnumerator *enumerator) {
    IDPLinkedList *list = IDPLinkedListEnumeratorGetList(enumerator);
    if (enumerator && list && IDPLinkedListEnumeratorIsValid(enumerator)
        && IDPLinkedListGetMutationsCount(list) == IDPLinkedListEnumeratorGetMutationsCount(enumerator))
    {
        return true;
    }
    
    return false;
}
