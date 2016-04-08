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


char * IDPCreateReversedStringForString(char *inputString)
{
    IDPList *myExpGenericList = IDPCreateNewList();
    
    printf("New list size = %lu\n", myExpGenericList->functions->IDPGetSizeForList(myExpGenericList));
    
    int currentPosition = 0;
    char currentSymbol;
    
    while ((currentSymbol = inputString[currentPosition++]) &&
           currentSymbol != '\0') {
        if (currentPosition > IDP_MAX_READ_BUFFER_SIZE) {
            return NULL;
        }
        myExpGenericList->functions->IDPPopulateFrontNodeForListWithData(myExpGenericList, (void*)currentSymbol);
    }
    
    char *reversedString = malloc(myExpGenericList->functions->IDPGetSizeForList(myExpGenericList) + 1);
    currentPosition = 0;
    currentSymbol = ' ';
    while ((currentSymbol = (char *)myExpGenericList->functions->IDPRemoveFrontNodeForList(myExpGenericList)) &&
           currentSymbol != NULL) {
        reversedString[currentPosition++] = currentSymbol;
    }
    reversedString[currentPosition] = '\0';
    
    return reversedString;
}
