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
    IDPLinkedListNode previousNode;
    
    IDPLinkedListNode node;
    
    IDPObject data;
};

typedef bool (*IDPLinkedListComparator)(IDPLinkedListNode *node,
                                        IDPLinkedListNodeContext *nodeContext);

extern
uint64_t IDPLinkedListGetMutationsCount(IDPLinkedList *list);

extern
IDPLinkedListNode *IDPLinkedListGetHead(IDPLinkedList *list);

#endif
