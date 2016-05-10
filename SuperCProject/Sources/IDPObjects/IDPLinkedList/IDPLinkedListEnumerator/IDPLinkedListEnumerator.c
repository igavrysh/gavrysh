//
//  IDPLinkedListEnumerator.c
//  SuperCProject
//
//  Created by Student 104 on 5/10/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPLinkedListEnumerator.h"
#include "IDPLinkedListPrivate.h"
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
IDPLinkedListNode *IDPLinkedListEnumeratorGetNode(IDPLinkedListEnumerator *enumerator);

static
IDPLinkedList *IDPLinkedListEnumeratorGetList(IDPLinkedListEnumerator *enumerator);

#pragma mark -
#pragma mark Public Implementations

void __IDPLinkedListEnumeratorDeallocate(IDPLinkedList *list) {
    IDPObjectRelease(list);
}

IDPLinkedListEnumerator *IDPLinkedListEnumeratorCreateWithList(IDPLinkedList *list) {
    IDPLinkedListEnumerator *enumerator = IDPObjectCreateWithType(IDPLinkedListEnumerator);
    
    IDPLinkedListEnumeratorSetList(enumerator, list);
    
    IDPLinkedListEnumeratorSetMutationsCount(enumerator,
                                             IDPLinkedListGetMutationsCount(list));
    
    return enumerator;
}

IDPObject *IDPLinkedListEnumeratorGetNextObject(IDPLinkedListEnumerator *enumerator) {
    if (!enumerator) {
        return NULL;
    }
    
    if (!enumerator->_node) {
    
        IDPLinkedListEnumeratorSetNode(enumerator,
                                       IDPLinkedListGetHead(IDPLinkedListEnumeratorGetList(enumerator)));
    } else {
        IDPLinkedListEnumeratorSetNode(enumerator, IDPLinkedListNodeGetNext(enumerator->_node));
    }
    
    return IDPLinkedListNodeGetData(IDPLinkedListEnumeratorGetNode(enumerator));
}

bool IDPLinkedListEnumeratorIsValid(IDPLinkedListEnumerator *enumerator) {
    if (!enumerator || !IDPLinkedListEnumeratorGetList(enumerator)) {
        IDPLinkedListEnumeratorSetValid(enumerator, false);
    }
    
    if (!IDPLinkedListEnumeratorGetList(enumerator)
        || IDPLinkedListGetMutationsCount(IDPLinkedListEnumeratorGetList(enumerator))
        != IDPLinkedListEnumeratorGetMutationsCount(enumerator))
    {
        IDPLinkedListEnumeratorSetValid(enumerator, false);
    }
    
    return enumerator->_isValid;
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

void IDPLinkedListEnumeratorSetList(IDPLinkedListEnumerator *enumerator, IDPLinkedList *list) {
    if (!enumerator) {
        return;
    }
    
    enumerator->_list = list;
}

IDPLinkedList *IDPLinkedListEnumeratorGetList(IDPLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_list : false;
}

void IDPLinkedListEnumeratorSetNode(IDPLinkedListEnumerator *enumerator, IDPLinkedListNode *node) {
    if (!enumerator) {
        return;
    }
    
    enumerator->_node = node;
}

IDPLinkedListNode *IDPLinkedListEnumeratorGetNode(IDPLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_node : NULL;
}
