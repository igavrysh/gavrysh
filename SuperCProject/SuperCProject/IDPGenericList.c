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

bool IDPIsEmptyList(const IDPList *list) {
    return list->size == 0;
}

unsigned long IDPGetSizeForList(const IDPList *list) {
    return list->size;
}

void * IDPGetFrontNodeDataForList(const IDPList *list) {
    return list->first->data;
}

void IDPPopulateFrontNodeForListWithData(IDPList *list, void *data) {
    
    IDPListNode *newNode = (IDPListNode *) malloc(sizeof(IDPListNode));
    newNode->data = data;
    newNode->next = list->first;
    list->first = newNode;
    list->size++;
}

void * IDPRemoveFrontNodeForList(IDPList *list) {
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

IDPList * IDPCreateNewList() {
    IDPList *res = (IDPList *)malloc(sizeof(IDPList));
    res->size = 0;
    res->first = NULL;
    
    return res;
}