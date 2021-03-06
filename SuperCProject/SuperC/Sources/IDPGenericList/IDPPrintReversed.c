//
//  IDPPrintReversed.c
//  SuperCProject
//
//  Created by Ievgen on 4/6/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>

#include "IDPGenericList.h"
#include "IDPPrintReversed.h"

#define IDP_MAX_READ_BUFFER_SIZE 1024

char *IDPCreateReversedStringForString(char *inputString) {
    IDPList *myExpGenericList = IDPCreateNewList();
    
    int currentPosition = 0;
    char currentSymbol;
    
    while ((currentSymbol = inputString[currentPosition++]) &&
           currentSymbol != '\0') {
        if (currentPosition > IDP_MAX_READ_BUFFER_SIZE) {
            return NULL;
        }
        
        IDPPopulateFrontNodeForListWithData(myExpGenericList, currentSymbol);
    }
    
    char *reversedString = malloc(IDPGetSizeForList(myExpGenericList) + 1);
    currentPosition = 0;
    currentSymbol = ' ';
    while ((currentSymbol = (char *)IDPRemoveFrontNodeForList(myExpGenericList)) &&
           currentSymbol != NULL) {
        reversedString[currentPosition++] = currentSymbol;
    }
    
    reversedString[currentPosition] = '\0';
    
    return reversedString;
}

char *IDPCreateReversedStringForStringSimple(char *inputString) {
    unsigned long size = strlen(inputString);
    char *reversedString = malloc(sizeof(char) * size);
    for (int i = 0; i < size / 2; i++) {
        reversedString[i] = inputString[size - 1 - i];
        reversedString[size - 1 - i] = inputString[i];
    }
    
    return reversedString;
}
