//
//  IDPLinkedList.h
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPLinkedList_h
#define IDPLinkedList_h

#include "IDPObject.h"
#include "IDPLinkedListNode.h"

typedef struct IDPLinkedList IDPLinkedList;

struct IDPLinkedList {
    IDPObject _super;
    
    IDPLinkedListNode *_head;
    uint64_t _count;
};



#endif /* IDPLinkedList_h */
