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

void *IDPStringCreateWithString(char *string) {
    IDPString *result = IDPObjectCreateOfType(IDPString);
    IDPStringSetString(result, string);
    
    return result;
}

void *IDPStringCreateWithIDPString(IDPString *string) {
    if (NULL == string) {
        return NULL;
    }
    
    IDPString *result = IDPStringCreateWithString(string->_string);
    
    return result;
}

void __IDPStringDeallocate(void *object) {
    IDPStringSetString(object, NULL);
    
    __IDPObjectDeallocate(object);
}

void IDPStringSetString(void *object, char *value) {
    if (NULL == object) {
        return;
    }
    
    IDPString *string = object;
    
    if(string->_string != value) {
        if (string ->_string) {
            free(string->_string);
            string->_string = NULL;
        }
        
        if (value) {
            string->_string = malloc((strlen(value) + 1) * sizeof(string->_string));
            strcpy(string->_string, value);
        }
    }
}

void IDPStringSetIDPString(void *object, void *string) {
    if (NULL != object && NULL != ((IDPString *)object)->_string &&
        NULL != string && NULL != ((IDPString *)string)->_string) {
        IDPStringSetString(object, ((IDPString *)string)->_string);
    }
}

char *IDPStringGetString(void *object) {
    return object ? ((IDPString *)object)->_string : NULL;
}

size_t IDPStringGetLength(void *object) {
    return object ? strlen(((IDPString *)object)->_string) : 0;
}
