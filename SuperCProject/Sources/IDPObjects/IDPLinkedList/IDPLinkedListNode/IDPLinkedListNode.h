//
//  IDPLinkedListNode.h
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/16/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPLinkedListNode_h
#define IDPLinkedListNode_h

#include <stdio.h>

#include "IDPObject.h"

typedef struct IDPLinkedListNode IDPLinkedListNode;

struct IDPLinkedListNode {
    IDPObject _super;
    
    IDPLinkedListNode *_nextNode;
    void *_object;
};

extern
void __IDPLinkedListNodeDeallocate(void *object);

extern
IDPLinkedListNode *IDPLinkedListNodeCreateWithObject(IDPObject *object);

extern
IDPLinkedListNode *IDPLinkedListNodeGetNextNode(IDPLinkedListNode *node);

extern
void IDPLinkedListNodeSetNextNode(IDPLinkedListNode *node, IDPLinkedListNode *nextNode);

extern
IDPObject *IDPLinkedListNodeGetObject(IDPLinkedListNode *node);


extern
void IDPLinkedListNodeSetObject(IDPLinkedListNode *node, void *object);


#endif /* IDPLinkedListNode_h */
