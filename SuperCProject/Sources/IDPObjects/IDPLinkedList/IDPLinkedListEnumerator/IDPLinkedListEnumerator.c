//
//  IDPLinkedListEnumerator.c
//  SuperCProject
//
//  Created by Student 104 on 5/10/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPLinkedListEnumerator.h"

#include "IDPLinkedListPrivate.h"

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

IDPLinkedListNode *IDPLinkedListEnumeratorGetNext(IDPLinkedListEnumerator *enumerator) {
    if (!enumerator) {
        return NULL;
    }
    
    
    if (!enumerator->_node) {
        enumerator->_node = IDPLinkedListGetHead(IDPLinkedListEnumeratorGetList(enumerator));
    } else {
        enumerator->_node = IDPLinkedListNodeGetNext(enumerator->_node);
    }
    
    return enumerator->_node;
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


