//
//  IDPLinkedListPrivate.h
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 5/3/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPLinkedListPrivate_h
#define IDPLinkedListPrivate_h

#include "IDPLinkedList.h"

typedef struct {
    void *previousNode;
    void *node;
    void *object;
} IDPLinkedListNodeContext;

typedef bool (*IDPLinkedListNodeComparisonFunction)(IDPLinkedListNode *node, IDPLinkedListNodeContext context);

extern
void IDPLinkedListSetHead(IDPLinkedList *list, IDPLinkedListNode *head);

extern
IDPLinkedListNode *IDPLinkedListGetHead(IDPLinkedList *list);

extern
void IDPLinkedListSetMutationsCount(IDPLinkedList *list, uint64_t count);

extern
uint64_t IDPLinkedListGetMutationsCount(IDPLinkedList *list);

extern
IDPLinkedListNode *IDPLinkedListGetNodeWithContext(IDPLinkedList *list,
                                                   IDPLinkedListNodeComparisonFunction comparator,
                                                   IDPLinkedListNodeContext *context);

extern
bool IDPLinkedListNodeContainsObject(IDPLinkedListNode *node, IDPLinkedListNodeContext context);

#endif /* IDPLinkedListPrivate_h */
