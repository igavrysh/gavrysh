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

IDPList * IDPCreateNewList();
bool IDPIsEmptyList(const IDPList *);
unsigned long IDPGetSizeForList(const IDPList *);
void * IDPGetFrontNodeDataForList(const IDPList *);
void IDPPopulateFrontNodeForListWithData(IDPList *, void *);
void * IDPRemoveFrontNodeForList(IDPList *);


bool IDPIsEmptyList(const struct IDPList *list) {
    return list->size == 0;
}

unsigned long IDPGetSizeForList(const struct IDPList *list) {
    return list->size;
}

void * IDPGetFrontNodeDataForList(const struct IDPList *list) {
    return list->first->data;
}

void IDPPopulateFrontNodeForListWithData(struct IDPList *list, void *data) {
    
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

/*
IDPListFunctions* idpListFunctions = {
    //&IDPCreateNewList,
    &IDPIsEmptyList,
    &IDPGetSizeForList,
    &IDPGetFrontNodeDataForList,
    &IDPPopulateFrontNodeForListWithData,
    &IDPRemoveFrontNodeForList
};
*/

IDPList * IDPCreateNewList() {
    IDPList* res = (IDPList*) malloc(sizeof(IDPList));
    res->size = 0;
    res->first = NULL;
    
    IDPListFunctions* idpListFunctions = (IDPListFunctions*) malloc(sizeof(IDPListFunctions));
    idpListFunctions->IDPIsEmptyList = &IDPIsEmptyList;
    idpListFunctions->IDPGetSizeForList = &IDPGetSizeForList;
    idpListFunctions->IDPGetFrontNodeDataForList = &IDPGetFrontNodeDataForList;
    idpListFunctions->IDPPopulateFrontNodeForListWithData = &IDPPopulateFrontNodeForListWithData;
    idpListFunctions->IDPRemoveFrontNodeForList = &IDPRemoveFrontNodeForList;
    
    res->functions = idpListFunctions;
    
    //res->functions = &idpListFunctions;
    
    /*
    res->functions->IDPPopulateFrontNodeForListWithData(res, "f");
    res->functions->IDPPopulateFrontNodeForListWithData(res, "d");
    res->functions->IDPPopulateFrontNodeForListWithData(res, "s");
    
    char* t = (char *)res->functions->IDPRemoveFrontNodeForList(res);
    t = (char *)res->functions->IDPRemoveFrontNodeForList(res);
    */
    
    return res;
}