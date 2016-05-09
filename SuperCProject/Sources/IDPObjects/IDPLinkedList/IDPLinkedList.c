//
//  IDPLinkedList.c
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPObjectMacros.h"
#include "IDPLinkedList.h"

#pragma mark -
#pragma mark Private Declarations

static
IDPLinkedListNode *IDPLinkedListGetHead(IDPLinkedList *list);

static
void IDPLinkedListSetHead(IDPLinkedList *list, IDPLinkedListNode *node);

static
void IDPLinkedListAddValueToCount(IDPLinkedList *list, int64_t deltaCount);

static
void IDPLinkedListSetCount(IDPLinkedList *list, uint64_t count);

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
            }
            
            IDPLinkedListAddValueToCount(list, -1);
        }
        
        prevNode = node;
        node = nextNode;
    }
}

void IDPLinkedListRemoveAllObjects(IDPLinkedList *list) {
    IDPLinkedListSetCount(list, 0);
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
    if (!list) {
        return;
    }
    
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
    
    if (0 == count) {
        IDPLinkedListSetHead(list, NULL);
    }
    
    list->_count = count;
}
