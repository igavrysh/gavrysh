//
//  IDPPrintReversed.c
//  SuperCProject
//
//  Created by Ievgen on 4/6/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>

#include "IDPGenericDefineList.h"
#include "IDPPrintReversed.h"

#define IDP_MAX_READ_BUFFER_SIZE 1024

define_list(char)

char* IDPGetReversedStringForString(char *inputString)
{
    List(char)* myExpGenericList = new_list(char);
    
    int currentPosition = 0;
    char currentSymbol;
    
    while ((currentSymbol = inputString[currentPosition++]) &&
           currentSymbol != '\0') {
        if (currentPosition > IDP_MAX_READ_BUFFER_SIZE) {
            return NULL;
        }
        push_front(myExpGenericList, currentSymbol);
    }
    
    char *reversedString = malloc(size(myExpGenericList) + 1);
    currentPosition = 0;
    currentSymbol = ' ';
    while ((currentSymbol = pop_front(myExpGenericList)) &&
           currentSymbol != NULL) {
        reversedString[currentPosition++] = currentSymbol;
    }
    reversedString[currentPosition] = '\0';
    
    return reversedString;
}
