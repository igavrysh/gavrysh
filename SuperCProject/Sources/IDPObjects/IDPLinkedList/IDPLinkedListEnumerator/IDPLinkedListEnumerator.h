//
//  IDPLinkedListEnumerator.h
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 5/2/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPLinkedListEnumerator_h
#define IDPLinkedListEnumerator_h

#include <assert.h>
#include <stdbool.h>

#include "IDPObject.h"

typedef struct IDPLinkedListEnumerator IDPLinkedListEnumerator;

typedef struct IDPLinkedListNode IDPLinkedListNode;

typedef struct IDPLinkedList IDPLinkedList;

struct IDPLinkedListEnumerator{
    IDPObject _super;
    
    void *_list;
    IDPLinkedListNode *_node;
    uint64_t _mutationsCount;
    
    bool _valid;
};

extern
IDPLinkedListEnumerator *IDPLinkedListEnumeratorCreateWithList(IDPLinkedList *list);

extern
void *IDPLinkedListEnumeratorGetNextObject(IDPLinkedListEnumerator *enumerator);

extern
bool IDPLinkedListEnumeratorIsValid(IDPLinkedListEnumerator *enumerator);

extern
void __IDPLinkedListEnumeratorDeallocated(void *object);

#endif /* IDPLinkedListEnumerator_h */
