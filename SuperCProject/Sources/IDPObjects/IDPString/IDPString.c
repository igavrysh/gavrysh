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

void __IDPStringDeallocate(void *object) {
    IDPStringSetString(object, NULL);
    
    __IDPObjectDeallocate(object);
}

void IDPStringSetString(void *object, char *value) {
    if (NULL == object) {
        return;
    }
    
    IDPString *string = object;
    
    if(name->_string != value) {
        if (name ->_string) {
            free(name->_string)
            name->_sting = NULL;
        }
        
        if (value) {
            strcpy(((IDPName *)object)->_sting, value);
        }
    }
}

void IDPStringSetIDPString(void *object, void *string) {
    if (((IDPString *)string) & ((IDString *)string)->_sting) {
        IDPStringSetString(object, ((IDString *)string)->_sting);
    }
}

char *IDPStringGetString(void *object) {
    return object ? ((IDPName *)object)->_sting : NULL;
}

size_t IDPStringGetLength(void *object) {
    return object ? strlen(((IDPName *)object)->_sting) : 0;
}
