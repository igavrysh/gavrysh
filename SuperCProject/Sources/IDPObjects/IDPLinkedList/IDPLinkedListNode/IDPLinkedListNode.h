//
//  IDPLinkedListNode.h
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPLinkedListNode_h
#define IDPLinkedListNode_h

#include <stdbool.h>

#include "IDPObject.h"

typedef struct IDPLinkedListNode IDPLinkedListNode;

struct IDPLinkedListNode {
    IDPObject _super;
    
    IDPLinkedListNode *_nextNode;
    IDPObject *_data;
};

extern
void __IDPLinkedListNodeDeallocate(IDPLinkedListNode *node);

extern
IDPLinkedListNode *IDPLinkedListNodeCreate();

extern
IDPLinkedListNode *IDPLinkedListNodeCreateWithData(IDPObject *data);

extern
IDPObject *IDPLinkedListNodeGetData(IDPLinkedListNode *node);

extern
void IDPLinkedListNodeSetData(IDPLinkedListNode *node, IDPObject *object);

extern
IDPLinkedListNode *IDPLinkedListNodeGetNext(IDPLinkedListNode *node);

extern
void IDPLinkedListNodeSetNext(IDPLinkedListNode *node, IDPLinkedListNode *nextNode);

extern
bool IDPLinkedListNodeHasNext(IDPLinkedListNode *node);

#endif /* IDPLinkedListNode_h */
