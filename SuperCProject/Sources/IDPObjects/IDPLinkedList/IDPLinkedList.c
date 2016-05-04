//
//  IDPLinkedList.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/25/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>
#include <string.h>

#include "IDPLinkedList.h"

#include "IDPLinkedListEnumerator.h"
#include "IDPLinkedListNode.h"
#include "IDPLinkedListPrivate.h"
#include "IDPLinkedListEnumeratorPrivate.h"

#include "IDPObjectMacros.h"

#pragma mark - 
#pragma mark Private Declarations

static
void IDPLinkedListSetCount(IDPLinkedList *list, uint64_t count);

static
void IDPLinkedListMutate(IDPLinkedList *list);

#pragma mark -
#pragma mark Public Implementation

void __IDPLinkedListDeallocate(void *object) {
    IDPLinkedListSetHead(object, NULL);
    
    __IDPObjectDeallocate(object);
}

IDPLinkedListEnumerator *IDPLinkedListEnumeratorFromList(IDPLinkedList *list) {
    return IDPLinkedListEnumeratorCreateWithList(list);
}

IDPObject *IDPLinkedListGetFirstObject(IDPLinkedList *list) {
    IDPLinkedListNode *node = IDPLinkedListGetHead(list);
    
    return IDPLinkedListNodeGetObject(node);
}

void IDPLinkedListRemoveFirstObject(IDPLinkedList *list) {
    if (NULL != list && false == IDPLinkedListIsEmpty(list)) {
        IDPLinkedListNode *node = IDPLinkedListGetHead(list);
        IDPLinkedListSetHead(list, IDPLinkedListNodeGetNextNode(node));
        IDPLinkedListSetCount(list, IDPLinkedListGetCount(list) - 1);
    }
}

IDPObject *IDPLinkedListGetObjectBeforeObject(IDPLinkedList *list, IDPObject *object) {
    if (NULL != list && false == IDPLinkedListIsEmpty(list)) {
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
    if (NULL != list) {
        IDPLinkedListNode *node = IDPLinkedListNodeCreateWithObject(object);
        IDPLinkedListNodeSetNextNode(node, IDPLinkedListGetHead(list));
        
        IDPLinkedListSetHead(list, node);
        IDPLinkedListSetCount(list, IDPLinkedListGetCount(list) + 1);
        
        IDPObjectRelease(node);
    }
}

void IDPLinkedListRemoveObject(IDPLinkedList *list, void *object) {
    // find node with object
    IDPLinkedListNode *node = IDPLinkedListGetHead(list);
    IDPLinkedListNode *previousNode = NULL;
    
    while (node) {
        IDPObject *currentObject = IDPLinkedListNodeGetObject(node);
        IDPLinkedListNode *nextNode = IDPLinkedListNodeGetNextNode(node);
        
        if (object == currentObject) {
            if (node == IDPLinkedListGetHead(list)) {
                IDPLinkedListSetHead(list, nextNode);
            } else {
                IDPLinkedListNodeSetNextNode(previousNode, nextNode);
            }
            
            IDPLinkedListSetCount(list, IDPLinkedListGetCount(list) - 1);
        }
        
        previousNode = node;
        node = nextNode;
    }
}

void IDPLinkedListRemoveAllObjects(IDPLinkedList *list) {
    if (list) {
        IDPLinkedListSetCount(list, 0);
        
        //IDPLinkedListSetHead(list, NULL);
        //list->_count = 0;
    }
}

bool IDPLinkedListContainsObject(IDPLinkedList *list, void *object) {
    bool result = false;
    if (list) {
        // enumerate all nodes to find with object
        IDPLinkedListNode *node = IDPLinkedListGetHead(list);
        while (NULL != node) {
            IDPLinkedListNodeContext context;
            
            memset(&context, 0, sizeof(context));
            
            context.object = object;
            
            result = NULL != IDPLinkedListGetNodeWithContext(list, IDPLinkedListNodeContainsObject, &context);
            
            node = IDPLinkedListNodeGetNextNode(node);
        }
    }
    
    return result;
}

uint64_t IDPLinkedListGetCount(IDPLinkedList *list) {
    return list ? list->_count : 0;
}

#pragma mark - 
#pragma mark Private Implementations

void IDPLinkedListSetCount(IDPLinkedList *list, uint64_t count) {
    if (list) {
        if (0 == count) {
            IDPLinkedListSetHead(list, NULL);
        }
        
        list->_count = count;
        IDPLinkedListMutate(list);
    }
}

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

void IDPLinkedListSetMutationsCount(IDPLinkedList *list, uint64_t count) {
    IDPAssignSetter(list, _mutationsCount, count);
}

uint64_t IDPLinkedListGetMutationsCount(IDPLinkedList *list) {
    return list ? list->_mutationsCount : 0;
}

void IDPLinkedListMutate(IDPLinkedList *list) {
    IDPLinkedListSetMutationsCount(list, IDPLinkedListGetMutationsCount(list) + 1);
}

IDPLinkedListNode *IDPLinkedListGetNodeWithContext(IDPLinkedList *list,
                                                   IDPLinkedListNodeComparisonFunction comparator,
                                                   IDPLinkedListNodeContext *context)
{
    IDPLinkedListNode *result = NULL;
    if (NULL != list) {
        IDPLinkedListEnumerator *enumerator = IDPLinkedListEnumeratorCreateWithList(list);
        
        while (true == IDPLinkedListEnumeratorIsValid(enumerator)
               && NULL != IDPLinkedListEnumeratorGetNextObject(enumerator))
        {
            IDPLinkedListNode *node = IDPLinkedListEnumeratorGetNode(enumerator);
            
            context->node = node;
            
            if (true == IDPLinkedListNodeContainsObject(node, *context)) {
                result = node;
                break;
            }
            
            context->previousNode = node;
        }
        
        IDPObjectRelease(enumerator);
    }
    
    return result;
}

extern
bool IDPLinkedListNodeContainsObject(IDPLinkedListNode *node, IDPLinkedListNodeContext context) {
    return node && context.object == IDPLinkedListNodeGetObject(node);
}
