//
//  IDPLinkedList.c
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>
#include <string.h>

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
bool IDPLinkedListNodeContainsObject(void *object, void *context);

static
IDPLinkedListNodeContext IDPLinkedListGetContextWithObject(IDPLinkedList *list, IDPObject *object);

static
IDPLinkedListNode *IDPLinkedListFindNodeWithContext(IDPLinkedList *list, IDPComparisonFunction compare, void *context);

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
    
    if(!context.node) {
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
    
    return context.node;
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

bool IDPLinkedListNodeContainsObject(void *nodeObj, void *context) {
    if (!nodeObj || !context) {
        return false;
    }
    
    IDPLinkedListNodeContext *nodeContext = (IDPLinkedListNodeContext *)context;
    IDPLinkedListNode *node = nodeObj;
    
    nodeContext->previousNode = nodeContext->node;
    nodeContext->node = node;

    return IDPLinkedListNodeGetData(node) == nodeContext->data;
}

bool IDPLinkedListInterimEnumeratorFunction(void *object, void *context) {
    if (!object || !context) {
        return false;
    }
    
    IDPLinkedListNodeContext *nodeContext = (IDPLinkedListNodeContext *)context;
    nodeContext->compare(object, context);
    
    nodeContext->attachedContext;
}

IDPLinkedListNode *IDPLinkedListFindNodeWithContext(IDPLinkedList *list, IDPComparisonFunction compare, void *context) {
    if (!list || !compare) {
        return NULL;
    }
    
    IDPLinkedListEnumerator *enumerator = IDPLinkedListEnumeratorCreateWithList(list);
    IDPLinkedListNode *result = NULL;
    
    while ((result = IDPLinkedListEnumeratorGetNextNode(enumerator))
           && IDPLinkedListEnumeratorIsValid(enumerator))
    {
        if (compare(result, context)) {
            break;
        }
    }
    
    IDPObjectRelease(enumerator);
    
    return result;
}

IDPLinkedListNode *IDPLinkedListFindObjectWithContext(IDPLinkedList *list, IDPComparisonFunction compare, void *context) {
    IDPLinkedListNodeContext nodeContext;
    memset(&nodeContext, 0, sizeof(nodeContext));
    
    if (!list) {
        return NULL;
    }
    
    nodeContext.attachedContext = context;
    nodeContext.compare = &IDPLinkedListNodeContainsObject;
    
    return IDPLinkedListFindNodeWithContext(list, compare, &nodeContext);
}

IDPLinkedListNodeContext IDPLinkedListGetContextWithObject(IDPLinkedList *list, IDPObject *object) {
    return IDPLinkedListGetContextWithFunctionAndObject(list, &IDPLinkedListNodeContainsObject, object);
}

IDPLinkedListNodeContext IDPLinkedListGetContextWithFunctionAndObject(IDPLinkedList *list, IDPComparisonFunction function, IDPObject *object)
{
    IDPLinkedListNodeContext context;
    memset(&context, 0, sizeof(context));
    
    if (!list) {
        return context;
    }
    
    context.data = object;
    
    if (IDPLinkedListFindNodeWithContext(list, function, &context)) {
        return context;
    }
    
    memset(&context, 0, sizeof(context));
    return context;
}
