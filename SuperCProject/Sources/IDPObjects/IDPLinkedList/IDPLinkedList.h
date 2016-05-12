//
//  IDPLinkedList.h
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPLinkedList_h
#define IDPLinkedList_h

#include <stdbool.h>

#include "IDPObject.h"
#include "IDPLinkedListNode.h"

typedef struct IDPLinkedList IDPLinkedList;

struct IDPLinkedList {
    IDPObject _super;
    
    IDPLinkedListNode *_head;
    uint64_t _count;
    
    uint64_t _mutationsCount;
};

extern
void __IDPLinkedListDeallocate(IDPLinkedList *list);

extern
void IDPLinkedListAddObject(IDPLinkedList *list, IDPObject *object);

extern
IDPObject *IDPLinkedListGetFirstObject(IDPLinkedList *list);

extern
IDPObject *IDPLinkedListGetObjectBeforeObject(IDPLinkedList *list, IDPObject *object);

extern
IDPObject *IDPLinkedListGetObjectAfterObject(IDPLinkedList *list, IDPObject *object);

extern
void IDPLinkedListRemoveFirstObject(IDPLinkedList *list);

extern
void IDPLinkedListRemoveObject(IDPLinkedList *list, IDPObject *object);

extern
void IDPLinkedListRemoveAllObjects(IDPLinkedList *list);

extern
bool IDPLinkedListContainsObject(IDPLinkedList *list, IDPObject *object);

extern
uint64_t IDPLinkedListGetCount(IDPLinkedList *list);

#endif /* IDPLinkedList_h */
