//
//  IDPGenericList.c
//  SuperCProject
//
//  Created by Ievgen on 4/8/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "IDPGenericList.h"

bool IDPIsEmptyList(IDPList *list) {
    return list->size == 0;
}

unsigned long IDPGetSizeForList(IDPList *list) {
    return list->size;
}

void *IDPGetFrontNodeDataForList(IDPList *list) {
    return list->first->data;
}

void IDPPopulateFrontNodeForListWithData(IDPList *list, void *data) {
    
    IDPListNode *listNode = (IDPListNode *) malloc(sizeof(*listNode));
    listNode->data = data;
    listNode->next = list->first;
    list->first = listNode;
    list->size++;
}

void *IDPRemoveFrontNodeForList(IDPList *list) {
    if (list->size == 0) {
        return NULL;
    }
    
    IDPListNode *listNodeToDrop = list->first;
    list->first = list->first->next;
    list->size--;
    void *data = listNodeToDrop->data;
    free(listNodeToDrop);
    
    return data;
}

IDPList *IDPCreateNewList() {
    IDPList *res = (IDPList *)malloc(sizeof(*res));
    res->size = 0;
    res->first = NULL;
    
    return res;
}
