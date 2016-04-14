//
//  IDPGenericDefineList.h
//  SuperCProject
//
//  Created by Ievgen on 4/6/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#ifndef IDPGenericList_h

#define IDPGenericList_h

#include <stdio.h>
#include <stdbool.h>

typedef struct IDPListNode IDPListNode;
typedef struct IDPList IDPList;

struct IDPListNode {
    void *data;
    IDPListNode *next;
};

struct IDPList {
    unsigned long size;
    IDPListNode *first;
    IDPListNode *last;
};

extern
IDPList *IDPCreateNewList();

extern
bool IDPIsEmptyList(IDPList *list);

extern
unsigned long IDPGetSizeForList(IDPList *list);

extern
void *IDPGetFrontNodeDataForList(IDPList *list);

extern
void IDPPopulateFrontNodeForListWithData(IDPList *list, void *data);

extern
void *IDPRemoveFrontNodeForList(IDPList *list);

#endif /* IDPGenericDefineList_h */
