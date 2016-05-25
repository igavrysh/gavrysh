//
//  IDPLinkedListPrivate.h
//  SuperCProject
//
//  Created by Student 104 on 5/10/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef SuperCProject_IDPLinkedListPrivate_h
#define SuperCProject_IDPLinkedListPrivate_h

#include <stdbool.h>

#include "IDPLinkedList.h"

typedef struct IDPLinkedListNodeContext IDPLinkedListNodeContext;

struct IDPLinkedListNodeContext {
    IDPLinkedListNode *previousNode;
    
    IDPLinkedListNode *node;
    
    IDPObject *data;
};

typedef struct IDPLinkedListDataContext IDPLinkedListDataContext;

struct IDPLinkedListDataContext {
    void *data;
    void *previousData;
};

typedef struct IDPLinkedListNodeDataContext IDPLinkedListNodeDataContext;

struct IDPLinkedListNodeDataContext {
    IDPLinkedListDataContext *dataContext;
    IDPComparisonFunction compare;
    IDPLinkedListNodeContext *nodeContext;
};

extern
IDPLinkedListNodeContext IDPLinkedListGetContextWithFunctionAndObject(IDPLinkedList *list, IDPComparisonFunction function, IDPObject *object);

extern
uint64_t IDPLinkedListGetMutationsCount(IDPLinkedList *list);

extern
IDPLinkedListNode *IDPLinkedListGetHead(IDPLinkedList *list);

#endif
