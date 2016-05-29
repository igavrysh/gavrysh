//
//  IDPObject.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/13/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>

#include "IDPObject.h"
#include "IDPAutoreleasingPool.h"

#pragma mark -
#pragma mark Private Declarations

void __IDPObjectRelease(void *object);

#pragma mark Public Implementations

void *__IDPObjectCreate(size_t objectSize, IDPObjectProcedurePointer deallocateCallback) {
    assert (0 != objectSize);
    
    IDPObject *object = calloc(1, objectSize);
    
    assert(NULL != object);
    
    object->_referenceCount = 1;
    object->_releaseFunction = __IDPObjectRelease;
    object->_deallocator = deallocateCallback;
    
    return object;
}

void *__IDPSingletonObjectCreate(void **singletonPointer, size_t objectSize, IDPObjectProcedurePointer deallocateCallBack) {
    if (*singletonPointer) {
        return *singletonPointer;
    }
    
    assert(NULL != singletonPointer);
    
    IDPObject *object = (IDPObject *)__IDPObjectCreate(objectSize, deallocateCallBack);
    object->_releaseFunction = NULL;
    
    *singletonPointer = object;
    
    return object;
}

void *IDPObjectAutorelease(void *object) {
    if (!object) {
        return NULL;
    }
    
    IDPAutoreleasingPoolAddObject(object);
    
    return object;
}

void *IDPObjectRetain(void *object) {
    if (NULL != object) {
        ((IDPObject *)object)->_referenceCount++;
    }
    
    return object;
}

void IDPObjectRelease(void *object) {
    if (!object) {
        return;
    }

    
    IDPObjectProcedurePointer releaseMethod = ((IDPObject *)object)->_releaseFunction;
    if (releaseMethod) {
        releaseMethod(object);
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
        void *tmp = retainMethod(value);
        if (*field) {
            IDPObjectRelease(*field);
        }
        
        *field = tmp;
        //*field = retainMethod(value);
    }
}

#pragma mark -
#pragma mark Private Methods

void __IDPObjectRelease(void *object) {
    if (!object) {
        return;
    }
    
    uint64_t count = ((IDPObject *)object)->_referenceCount - 1;
    ((IDPObject *)object)->_referenceCount = count;
    
    if (0 == count) {
        ((IDPObject *)object)->_deallocator(object);
    }
}

