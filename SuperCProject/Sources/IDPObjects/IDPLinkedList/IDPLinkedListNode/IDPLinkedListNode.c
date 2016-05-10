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
#pragma mark Public Implementations

void __IDPLinkedListNodeDeallocate(IDPLinkedListNode *node) {
    IDPLinkedListNodeSetNext(node, NULL);
    IDPLinkedListNodeSetData(node, NULL);
    
    __IDPObjectDeallocate(node);
}

IDPLinkedListNode *IDPLinkedListNodeCreate() {
    return IDPObjectCreateWithType(IDPLinkedListNode);
}

IDPLinkedListNode *IDPLinkedListNodeCreateWithData(IDPObject *data) {
    IDPLinkedListNode *node = IDPLinkedListNodeCreate();
    
    IDPLinkedListNodeSetData(node, data);
    
    return node;
}

IDPObject *IDPLinkedListNodeGetData(IDPLinkedListNode *node) {
    return node ? node->_data : NULL;
}

void IDPLinkedListNodeSetData(IDPLinkedListNode *node, IDPObject *object) {
    IDPObjectSetStrong(node, _data, object);
}

IDPLinkedListNode *IDPLinkedListNodeGetNext(IDPLinkedListNode *node) {
    return node ? node->_nextNode : NULL;
}

void IDPLinkedListNodeSetNext(IDPLinkedListNode *node, IDPLinkedListNode *nextNode) {
    IDPObjectSetStrong(node, _nextNode, nextNode);
}

bool IDPLinkedListNodeHasNext(IDPLinkedListNode *node) {
    return node ? node->_nextNode : false;
}
