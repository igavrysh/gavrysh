//
//  IDPLinkedList.h
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/25/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPLinkedList_h
#define IDPLinkedList_h

#include <stdbool.h>

#include "IDPObject.h"

typedef struct IDPLinkedListNode IDPLinkedListNode;

typedef struct {
    IDPObject _super;
    
    IDPLinkedListNode *_head;
    
    uint64_t _count;
} IDPLinkedList;

extern
IDPObject *IDPLinkedListGetFirstObject(IDPLinkedList *list);

extern
void IDPLinkedListRemoveFirstObject(IDPLinkedList *list);

extern
IDPObject *IDPLinkedListGetObjectBeforeObject(IDPLinkedList *list, IDPObject *object);

extern
bool IDPLinkedListIsEmpty(IDPLinkedList *list);

extern
void IDPLinkedListAddObject(IDPLinkedList *list, void *object);

extern
void IDPLinkedListRemoveObject(IDPLinkedList *list, void *object);

extern
void IDPLinkedListRemoveAllObjects(IDPLinkedList *list);

extern
bool IDPLinkedListContainsObject(IDPLinkedList *list, void *object);

extern
uint64_t IDPLinkedListGetCount(IDPLinkedList *list);

extern
void __IDPLinkedListDeallocate(void *object);

#endif /* IDPLinkedList_h */
