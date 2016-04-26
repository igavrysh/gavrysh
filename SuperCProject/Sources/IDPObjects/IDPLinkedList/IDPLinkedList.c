//
//  IDPLinkedList.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/25/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPLinkedList.h"
#include "IDPLinkedListNode.h"

#pragma mark - 
#pragma mark Private Declarations

static
void IDPLinkedListSetHead(IDPLinkedList *list, IDPLinkedListNode *head);

static
IDPLinkedListNode *IDPLinkedListGetHead(IDPLinkedList *list);

#pragma mark -
#pragma mark Public Implementation

void __IDPLinkedListDeallocate(void *object) {
    IDPLinkedListSetHead(object, NULL);
    
    __IDPObjectDeallocate(object);
}

IDPObject *IDPLinkedListGetFirstObject(IDPLinkedList *list) {
    IDPLinkedListNode *node = IDPLinkedListGetHead(list);
    
    return IDPLinkedListNodeGetObject(node);
}

void IDPLinkedListRemoveFirstObject(IDPLinkedList *list) {
    IDPLinkedListNode *node = IDPLinkedListGetHead(list);
    
    IDPLinkedListSetHead(list, IDPLinkedListNodeGetNextNode(node));
}

IDPObject *IDPLinkedListGetObjectBeforeObject(IDPLinkedList *list, IDPObject *object) {
    if (list && false == IDPLinkedListIsEmpty(list)) {
        // enumerate until object and remember previoud on each iteration
        IDPLinkedListNode *currentNode = IDPLinkedListGetHead(list);
        IDPObject *previousObject = NULL;
        
        do {
            IDPObject *currentObject = IDPLinkedListNodeGetObject(currentNode);
            if (object == currentObject) {
                return previousObject;
            }
            previousObject = currentObject;

        } while (NULL != (currentNode = IDPLinkedListNodeGetNextNode(currentNode)));
    }
    
    return NULL;
}

bool IDPLinkedListIsEmpty(IDPLinkedList *list) {
    return list && 0 == list->_count;
}

void IDPLinkedListAddObject(IDPLinkedList *list, void *object) {
    if (list) {
        IDPLinkedListNode *node = IDPLinkedListNodeCreateWithObject(object);
        IDPLinkedListNodeSetNextNode(node, IDPLinkedListGetHead(list));
        
        IDPLinkedListSetHead(list, node);
        
        list->_count++;
        
        IDPObjectRelease(node);
    }
}

void IDPLinkedListRemoveObject(IDPLinkedList *list, void *object) {
    // find node with object
    IDPLinkedListNode *node = IDPLinkedListGetHead(list);
    IDPLinkedListNode *previousNode = NULL;
    
    while (node) {
        IDPObject *currentObject = IDPLinkedListNodeGetObject(node);
        if (object == currentObject) {
            IDPLinkedListNode *nextNode = IDPLinkedListNodeGetNextNode(node);
            
            IDPLinkedListNodeSetNextNode(previousNode, nextNode);
            
            list->_count--;
        
            node = nextNode;
        }
        
        previousNode = node;
        node = IDPLinkedListNodeGetNextNode(node);
    }
}

void IDPLinkedListRemoveAllObjects(IDPLinkedList *list) {
    if (list) {
        IDPLinkedListSetHead(list, NULL);
        list->_count = 0;
    }
}

bool IDPLinkedListContainsObject(IDPLinkedList *list, void *object) {
    bool result = false;
    if (list) {
        // enumerate all nodes to find with object
        
    }
    
    return result;
}

uint64_t IDPLinkedListGetCount(IDPLinkedList *list) {
    return list ? list->_count : 0;
}

#pragma mark - 
#pragma mark Private Implementations

void IDPLinkedListSetHead(IDPLinkedList *list, IDPLinkedListNode *head) {
    if (list && list->_head != head) {
        IDPObjectRetain(head);
        IDPObjectRelease(list->_head);
        
        list->_head = head;
    }
}

IDPLinkedListNode *IDPLinkedListGetHead(IDPLinkedList *list) {
    return list ? list->_head : NULL;
}

