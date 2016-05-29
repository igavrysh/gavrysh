//
//  IDPName.c
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <string.h>

#include "IDPString.h"

#pragma mark -
#pragma mark Public Implementations

void __IDPStringDeallocate(IDPString *string) {
    IDPStringSetString(string, NULL);
    
    __IDPObjectDeallocate(string);
}

IDPString *IDPStringCreateWithString(char *string) {
    IDPString *result = IDPObjectCreateWithType(IDPString);
    IDPStringSetString(result, string);
    
    return result;
}

IDPString *IDPStringCopy(IDPString *string) {
    if (!string) {
        return NULL;
    }
    
    IDPString *result = IDPStringCreateWithString(string->_string);
    
    return result;
}

void IDPStringSetString(IDPString *string, char *value) {
    if (!string) {
        return;
    }
    
    if(string->_string != value) {
        if (string->_string) {
            free(string->_string);
            string->_string = NULL;
        }
        
        if (value) {
            string->_string = malloc((strlen(value) + 1) * sizeof(string->_string ));
            strcpy(string->_string, value);
        }
    }
}

void IDPStringSetWithIDPString(IDPString *string, IDPString *newValue) {
    if (!string && !newValue) {
        IDPStringSetString(string, newValue->_string);
    }
}

char *IDPStringGetString(IDPString *string) {
    return string ? string->_string : NULL;
}

size_t IDPStringGetLength(IDPString *string) {
    return string ? strlen(string->_string) : 0;
}
