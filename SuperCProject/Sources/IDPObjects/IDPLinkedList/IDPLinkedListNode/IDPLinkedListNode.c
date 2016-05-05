//
//  IDPLinkedListNode.c
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPLinkedListNode.h"
#include "IDPObjectMacros.h"


#pragma mark -
#pragma mark Private Declarations


#pragma mark -
#pragma mark Public Implementations

void __IDPLinkedListNodeDeallocate(IDPLinkedListNode *node) {
    
    __IDPObjectDeallocate(node);
}

IDPLinkedListNode *IDPLinkedListNodeCreate() {
    return IDPObjectCreateWithType(IDPLinkedListNode);
}

void *IDPLinkedListNodeGetData(IDPLinkedListNode *node) {
    return node ? node->_data : NULL;
}

extern
void IDPLinkedListNodeSetData(IDPLinkedListNode *node, void *data) {
    if (!node) {
        return;
    }
    
    IDPObjectSetStrong(node, _data, data);
}

extern
IDPLinkedListNode *IDPLinkedListNodeGetNext(IDPLinkedListNode *node) {
    return node ? node->_nextNode : NULL;
}

extern
void IDPLinkedListNodeSetNext(IDPLinkedListNode *node, IDPLinkedListNode *nextNode) {
    if (!node) {
        return;
    }
    
    IDPObjectSetStrong(node, _nextNode, nextNode);
}

extern
bool IDPLinkedListNodeHasNext(IDPLinkedListNode *node) {
    return node ? node->_nextNode : false;
}


#pragma mark -
#pragma mark Private Implementations