//
//  IDPLinkedListEnumerator.h
//  SuperCProject
//
//  Created by Student 104 on 5/10/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef __SuperCProject__IDPLinkedListEnumerator__
#define __SuperCProject__IDPLinkedListEnumerator__

#include "IDPObject.h"
#include "IDPLinkedListNode.h"
#include "IDPLinkedList.h"

typedef struct IDPLinkedListEnumerator IDPLinkedListEnumerator;

struct IDPLinkedListEnumerator {
    IDPObject _super;

    IDPLinkedList *_list;
    IDPLinkedListNode *_node;

    uint64_t _mutationsCount;
    bool _isValid;
};

extern
void __IDPLinkedListEnumeratorDeallocate(IDPLinkedList *list);

extern
IDPLinkedListEnumerator *IDPLinkedListEnumeratorCreateWithList(IDPLinkedList *list);

extern
IDPLinkedListNode *IDPLinkedListEnumeratorGetNext(IDPLinkedListEnumerator *enumerator);

extern
bool IDPLinkedListEnumeratorIsValid(IDPLinkedListEnumerator *enumerator);


#endif /* defined(__SuperCProject__IDPLinkedListEnumerator__) */
