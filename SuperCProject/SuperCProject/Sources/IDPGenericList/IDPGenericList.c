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
    return list->_size == 0;
}

unsigned long IDPGetSizeForList(const IDPList *list) {
    return list->_size;
}

void * IDPGetFrontNodeDataForList(const IDPList *list) {
    return list->_first->_data;
}

void IDPPopulateFrontNodeForListWithData(IDPList *list, void *data) {
    
    IDPListNode *newNode = (IDPListNode *) malloc(sizeof(IDPListNode));
    newNode->_data = data;
    newNode->_next = list->_first;
    list->_first = newNode;
    list->_size++;
}

void * IDPRemoveFrontNodeForList(IDPList *list) {
    if (list->_size == 0) {
        return NULL;
    }
    
    IDPListNode *listNodeToDrop = list->_first;
    list->_first = list->_first->_next;
    list->_size--;
    void *data = listNodeToDrop->_data;
    free(listNodeToDrop);
    
    return data;
}

IDPList * IDPCreateNewList() {
    IDPList *res = (IDPList *)malloc(sizeof(IDPList));
    res->_size = 0;
    res->_first = NULL;
    
    return res;
}
