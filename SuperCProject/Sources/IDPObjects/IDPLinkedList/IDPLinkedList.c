//
//  IDPLinkedList.c
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPObjectMacros.h"
#include "IDPLinkedList.h"
#include "IDPLinkedListEnumerator.h"
#include "IDPLinkedListPrivate.h"
#include "IDPLinkedListEnumeratorPrivate.h"

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

static
bool IDPLinkedListNodeContainsObject(IDPLinkedListNode *node, IDPLinkedListNodeContext *context);

static
IDPLinkedListNode *IDPLinkedListFindNodeWithContext(IDPLinkedList *list,
                                                    IDPLinkedListComparator compare,
                                                    IDPLinkedListNodeContext *context);

static
IDPLinkedListNodeContext IDPLinkedListGetContextWithObject(IDPLinkedList *list, IDPObject *object);

static
bool IDPLinkedListNodeContextIsNodeExists(IDPLinkedListNodeContext context);

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

IDPObject *IDPLinkedListGetObjectBeforeObject(IDPLinkedList *list, IDPObject *object) {
    return IDPLinkedListNodeGetData(IDPLinkedListGetContextWithObject(list, object).previousNode);
}

IDPObject *IDPLinkedListGetObjectAfterObject(IDPLinkedList *list, IDPObject *object) {
    return IDPLinkedListNodeGetData(IDPLinkedListNodeGetNext(IDPLinkedListGetContextWithObject(list, object).node));
}

void IDPLinkedListRemoveObject(IDPLinkedList *list, IDPObject *object) {
    if (!list) {
        return;
    }
    
    IDPLinkedListNodeContext context = IDPLinkedListGetContextWithObject(list, object);
    
    if(!IDPLinkedListNodeContextIsNodeExists(context)) {
        return;
    }
    
    if (context.node == IDPLinkedListGetHead(list)) {
        IDPLinkedListRemoveFirstObject(list);
    } else {
        IDPLinkedListNodeSetNext(context.previousNode, IDPLinkedListNodeGetNext(context.node));
        IDPLinkedListAddValueToCount(list, -1);
    }
    
    IDPLinkedListMutationsCountAddValue(list, +1);
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
    
    IDPLinkedListNodeContext context = IDPLinkedListGetContextWithObject(list, object);
    
    return IDPLinkedListNodeContextIsNodeExists(context);
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

bool IDPLinkedListNodeContainsObject(IDPLinkedListNode *node, IDPLinkedListNodeContext *context) {
    if (!node || !context) {
        return false;
    }
    
    context->previousNode = context->node;
    context->node = node;
    
    return IDPLinkedListNodeGetData(node) == context->data;
}

IDPLinkedListNode *IDPLinkedListFindNodeWithContext(IDPLinkedList *list,
                                                    IDPLinkedListComparator compare,
                                                    IDPLinkedListNodeContext *context)
{
    if (!list || !compare) {
        return NULL;
    }
    
    IDPLinkedListEnumerator *enumerator = IDPLinkedListEnumeratorCreateWithList(list);
    
    IDPObject *currentObject = IDPLinkedListEnumeratorGetNextObject(enumerator);
    
    IDPLinkedListNode *result = NULL;
    
    while (IDPLinkedListEnumeratorIsValid(enumerator)) {
        IDPLinkedListNode *currentNode = IDPLinkedListEnumeratorGetNode(enumerator);
        
        if (compare(currentNode, context)) {
            result = currentNode;
            break;
        }
        
        currentObject = IDPLinkedListEnumeratorGetNextObject(enumerator);
    }
    
    IDPObjectRelease(enumerator);
    
    return result;
}

IDPLinkedListNodeContext IDPLinkedListGetContextWithObject(IDPLinkedList *list, IDPObject *object) {
    IDPLinkedListNodeContext context;
    
    if (!list) {
        return context;
    }
    
    context.data = object;
    
    if (IDPLinkedListFindNodeWithContext(list, &IDPLinkedListNodeContainsObject, &context)) {
        return context;
    }
    
    context.data = NULL;
    context.node = NULL;
    context.previousNode = NULL;
    
    return context;
}

bool IDPLinkedListNodeContextIsNodeExists(IDPLinkedListNodeContext context) {
    return context.node;
}
