//
//  IDPName.c
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <string.h>

#include "IDPName.h"

#pragma mark -
#pragma mark Public Implementations

void *IDPNameCreateWithString(char *name) {
    IDPName *result = IDPObjectCreateOfType(IDPName);
    IDPNameSetName(result, name);
    return result;
}

void __IDPNameDeallocate(void *object) {
    if (NULL != object && NULL != ((IDPName *)object)->name) {
        free(((IDPName *)object)->name);
    }
    
    __IDPObjectDeallocate(object);
}

void IDPNameSetName(void *object, char *name) {
    if (NULL == object) {
        return;
    }
    
    strcpy(((IDPName *)object)->name, name);
}

void IDPNameDeepCopy(void *object, IDPName *name) {
    if (NULL == object || NULL == name->name) {
        return;
    }

    IDPNameSetName(object, name->name);
}

char *IDPNameGetName(void *object) {
    if (NULL == object) {
        return NULL;
    }
    
    return ((IDPName *)object)->name;
}
