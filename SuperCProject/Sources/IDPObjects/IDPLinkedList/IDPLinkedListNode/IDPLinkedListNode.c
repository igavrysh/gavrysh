//
//  IDPLinkedListNode.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/16/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>

#include "IDPLinkedListNode.h"

#pragma mark -
#pragma mark Public

void __IDPLinkedListNodeDeallocate(void *object) {
    IDPLinkedListNodeSetObject(object, NULL);
    IDPLinkedListNodeSetNextNode(object, NULL);
    
    __IDPObjectDeallocate(object);
}

IDPLinkedListNode *IDPLinkedListNodeCreateWithObject(IDPObject *object) {
    IDPLinkedListNode *result = IDPObjectCreateWithType(IDPLinkedListNode);
    IDPLinkedListNodeSetObject(result, object);
    
    return result;
}

IDPLinkedListNode *IDPLinkedListNodeGetNextNode(IDPLinkedListNode *node) {
    return node ? node->_nextNode : NULL;
}

void IDPLinkedListNodeSetNextNode(IDPLinkedListNode *node, IDPLinkedListNode *nextNode) {
    if (NULL != node && node->_nextNode != nextNode) {
        IDPObjectRetain(nextNode);
        
        IDPObjectRelease(node->_nextNode);
        node->_nextNode = nextNode;
    }
}

IDPObject *IDPLinkedListNodeGetObject(IDPLinkedListNode *node) {
    return node ? node->_object : NULL;
}

void IDPLinkedListNodeSetObject(IDPLinkedListNode *node, void *object) {
    if (NULL != node) {
        assert(node != object);
        
        void *previousObject = node->_object;
        
        if (previousObject != object) {
            IDPObjectRetain(object);
            IDPObjectRelease(previousObject);
            
            node->_object = object;
        }
    }
}
