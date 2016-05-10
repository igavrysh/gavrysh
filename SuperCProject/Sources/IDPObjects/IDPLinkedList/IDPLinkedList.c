//
//  IDPLinkedList.c
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPObjectMacros.h"
#include "IDPLinkedList.h"
#include "IDPLinkedListPrivate.h"

#pragma mark -
#pragma mark Private Declarations

static
void IDPLinkedListSetHead(IDPLinkedList *list, IDPLinkedListNode *node);

static
void IDPLinkedListAddValueToCount(IDPLinkedList *list, int64_t deltaCount);

static
void IDPLinkedListSetCount(IDPLinkedList *list, uint64_t count);

static
void IDPLinkedListSetMutationsCount(IDPLinkedList *list, uint64_t mutationsCount);

static
void IDPLinkedListMutationsCountAddValue(IDPLinkedList *list, int64_t addValue);

#pragma mark -
#pragma mark Public Implementations

void __IDPLinkedListDeallocate(IDPLinkedList *list) {
    IDPLinkedListRemoveAllObjects(list);
    
    __IDPObjectDeallocate(list);
}

void IDPLinkedListAddObject(IDPLinkedList *list, IDPObject *object) {
    if (!list) {
        return;
    }
    
    IDPLinkedListNode *node = IDPLinkedListNodeCreateWithData(object);
    IDPLinkedListNodeSetNext(node, IDPLinkedListGetHead(list));
    
    IDPLinkedListSetHead(list, node);
    
    IDPLinkedListAddValueToCount(list, +1);
    
    IDPLinkedListMutationsCountAddValue(list, +1);
    
    IDPObjectRelease(node);
}

IDPObject *IDPLinkedListGetFirstObject(IDPLinkedList *list) {    
    return IDPLinkedListNodeGetData(IDPLinkedListGetHead(list));
}

void IDPLinkedListRemoveFirstObject(IDPLinkedList *list) {
    IDPLinkedListNode *head = IDPLinkedListGetHead(list);

    IDPLinkedListSetHead(list, IDPLinkedListNodeGetNext(head));
    
    IDPLinkedListAddValueToCount(list, -1);
}

void IDPLinkedListRemoveObject(IDPLinkedList *list, IDPObject *object) {
    if (!list) {
        return;
    }
    
    IDPLinkedListNode *node = IDPLinkedListGetHead(list);
    IDPLinkedListNode *prevNode = NULL;
    while (node) {
        IDPLinkedListNode *nextNode = IDPLinkedListNodeGetNext(node);
        if (object == IDPLinkedListNodeGetData(node)) {
            if (node == IDPLinkedListGetHead(list)) {
                IDPLinkedListRemoveFirstObject(list);
            } else {
                IDPLinkedListNodeSetNext(prevNode, nextNode);
                IDPLinkedListAddValueToCount(list, -1);
            }
            
            IDPLinkedListMutationsCountAddValue(list, +1);
        } else {
            prevNode = node;
        }
        
        node = nextNode;
    }
}

void IDPLinkedListRemoveAllObjects(IDPLinkedList *list) {
    IDPLinkedListSetHead(list, NULL);
    
    IDPLinkedListSetCount(list, 0);
    
    IDPLinkedListMutationsCountAddValue(list, +1);
}

bool IDPLinkedListContainsObject(IDPLinkedList *list, IDPObject *object) {
    if (!list) {
        return false;
    }
    
    IDPLinkedListNode *node = IDPLinkedListGetHead(list);
    while (node) {
        if (object == IDPLinkedListNodeGetData(node)) {
            return true;
        }
        
        node = IDPLinkedListNodeGetNext(node);
    }
    
    return false;
}

uint64_t IDPLinkedListGetCount(IDPLinkedList *list) {
    return list ? list->_count : 0;
}

#pragma mark -
#pragma mark Private Implementations

IDPLinkedListNode *IDPLinkedListGetHead(IDPLinkedList *list) {
    return list ? list->_head: NULL;
}

void IDPLinkedListSetHead(IDPLinkedList *list, IDPLinkedListNode *node) {
    IDPObjectSetStrong(list, _head, node);
}

void IDPLinkedListAddValueToCount(IDPLinkedList *list, int64_t deltaCount) {
    if (!list) {
        return;
    }
    
    IDPLinkedListSetCount(list, IDPLinkedListGetCount(list) + deltaCount);
}

void IDPLinkedListSetCount(IDPLinkedList *list, uint64_t count) {
    if (!list) {
        return;
    }
    
    list->_count = count;
}

uint64_t IDPLinkedListGetMutationsCount(IDPLinkedList *list) {
    return list ? list->_mutationsCount : 0;
}

void IDPLinkedListSetMutationsCount(IDPLinkedList *list, uint64_t mutationsCount) {
    if (!list) {
        return;
    }
    
    list->_mutationsCount = mutationsCount;
}

void IDPLinkedListMutationsCountAddValue(IDPLinkedList *list, int64_t addValue) {
    IDPLinkedListSetMutationsCount(list, IDPLinkedListGetMutationsCount(list) + addValue);
}
