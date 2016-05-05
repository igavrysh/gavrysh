//
//  IDPObject.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/13/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>

#include "IDPObject.h"

void *__IDPObjectCreate(size_t objectSize, IDPObjectDeallocatorCallback deallocateCallback) {
    assert (0 != objectSize);
    
    IDPObject *object = calloc(1, objectSize);
    
    assert(NULL != object);
    
    object->_referenceCount = 1;
    object->_deallocator = deallocateCallback;
    
    return object;
}

void *IDPObjectRetain(void *object) {
    if (NULL != object) {
        ((IDPObject *)object)->_referenceCount++;
    }
    
    return object;
}

void IDPObjectRelease(void *arg) {
    if (!arg) {
        return;
    }
    
    IDPObject *object = (IDPObject *)arg;
    
    uint64_t count = object->_referenceCount - 1;
    object->_referenceCount = count;
    
    if (0 == count) {
        object->_deallocator(object);
    }
}

uint64_t IDPObjectGetReferenceCount(void *object) {
    return object ? ((IDPObject *)object)->_referenceCount : 0;
}

void __IDPObjectDeallocate(void *object) {
    free(object);
}

void __IDPObjectSetFieldValueWithMethod(void *object, void **field, void *value, IDPOwnershipMethod retainMethod) {
    if (!object) {
        return;
    }
    
    if (*field != value) {
        if (*field) {
            IDPObjectRelease(*field);
        }
        
        *field = retainMethod(value);
    }
}

