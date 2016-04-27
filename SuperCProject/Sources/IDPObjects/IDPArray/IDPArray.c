//
//  IDPArray.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/17/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "IDPArray.h"

static const uint64_t kIDPArrayMaximumCapacity = UINT64_MAX - 1;

#pragma mark -
#pragma mark Private Methods

static
void IDPArraySetCapacity(IDPArray *array, uint64_t capacity);

static
uint64_t IDPArrayGetCapacity(IDPArray *array);

static
void IDPArrayResizeIfNeeded(IDPArray *array);

static
bool IDPArrayShouldResize(IDPArray *array);

static
uint64_t IDPArrayPrefferedCapacity(IDPArray *array);

static
void IDPArrayResize(IDPArray *array, uint64_t requiredCapacity);

static
void IDPArraySetCount(IDPArray *array, uint64_t count);

static
void IDPArraySetObjectAtIndex(IDPArray *array, void *object, uint64_t index);


#pragma mark -
#pragma mark Public Methods

void *IDPArrayCreateWithCapacity(uint64_t capacity) {
    IDPArray *result = IDPObjectCreateWithType(IDPArray);
    IDPArraySetCapacity(result, capacity);
    
    return result;
}

void __IDPArrayDeallocate(void *object) {
    IDPArray *array = object;
    
    IDPArrayRemoveAllObjects(array);
//  IDPArraySetCapacity(object, 0);
    
    if (array->_data) {
        free(array->_data);
        array->_data = NULL;
    }

    __IDPObjectDeallocate(object);
}

void IDPArrayAddObject(IDPArray *array, void *object) {
    if (!array || !object) {
        return;
    }
    
    uint64_t count = IDPArrayGetCount(array);
    
    IDPArraySetCount(array, count + 1);
    IDPArraySetObjectAtIndex(array, object, count);
}

uint64_t IDPArrayGetCount(IDPArray *array) {
    return array ? array->_count : 0;
}

bool IDPArrayContainsObject(IDPArray *array, void *object) {
    return array && kIDPNotFound != IDPArrayGetIndexOfObject(array, object);
}

uint64_t IDPArrayGetIndexOfObject(IDPArray *array, void *object) {
    if (!array) {
        return 0;
    }
    
    if (NULL == object) {
        return kIDPNotFound;
    }
    
    uint64_t count = IDPArrayGetCount(array);
    for (uint64_t index = 0; index < count; index++) {
        if (IDPArrayGetObjectAtIndex(array, index) == object) {
            return index;
        }
    }
    
    return kIDPNotFound;
}

void *IDPArrayGetObjectAtIndex(IDPArray *array, uint64_t index) {
    if (!array) {
        return NULL;
    }
    
    assert(IDPArrayGetCount(array) > index);
    
    return array->_data[index];
}

void IDPArrayRemoveObjectAtIndex(IDPArray *array, uint64_t index) {
    if (!array) {
        return;
    }
    
    IDPArraySetObjectAtIndex(array, NULL, index);
    uint64_t count = IDPArrayGetCount(array);
    
    void **data = array->_data;
    if (index < count - 1) {
        uint64_t elementCount = count - (index - 1);
        
        memmove(&data[index], &data[index + 1], elementCount * sizeof(*data));
    }
    data[count - 1] = NULL;
    
    IDPArraySetCount(array, count - 1);
}

void IDPArrayRemoveAllObjects(IDPArray *array) {
    if (!array) {
        return;
    }
    
    uint64_t count = IDPArrayGetCount(array);
    for (uint64_t index = 0; index < count; index++) {
        IDPArraySetObjectAtIndex(array, NULL, index);
    }
        
    IDPArraySetCount(array, 0);
}

#pragma mark -
#pragma mark Private Implementations

uint64_t IDPArrayGetCapacity(IDPArray *array) {
    return array ? array->_capacity : 0;
}

void IDPArraySetCapacity(IDPArray *array, uint64_t capacity) {
    if (!array || array->_capacity == capacity) {
        return;
    }
    
    assert(kIDPArrayMaximumCapacity >= capacity);
        
    size_t size = capacity * sizeof(*array->_data);
    if (0 == size && array->_data) {
        free(array->_data);
        array->_data = NULL;
    } else {
        array->_data = realloc(array->_data, size);
        
        assert(NULL != array->_data);
    }
    
    if (capacity > array->_capacity) {
        void *startPointer = array->_data + array->_capacity;
        size_t numberOfBytes = (capacity - array->_capacity) * sizeof(*array->_data);
            
        memset(startPointer, 0, numberOfBytes);
    }
        
    array->_capacity = capacity;
}

void IDPArrayResizeIfNeeded(IDPArray *array) {
    if (IDPArrayShouldResize(array)) {
        IDPArraySetCapacity(array, IDPArrayPrefferedCapacity(array));
    }
}

bool IDPArrayShouldResize(IDPArray *array) {
    return array && array->_capacity != IDPArrayPrefferedCapacity(array);
}

uint64_t IDPArrayPrefferedCapacity(IDPArray *array) {
    if (!array) {
        return 0;
    }
    
    uint64_t count = IDPArrayGetCount(array);
    uint64_t capacity = IDPArrayGetCapacity(array);
    if (count == capacity) {
        return capacity;
    }
        
    return count < capacity ? count : capacity + 2 * (count - capacity);
}

void IDPArraySetCount(IDPArray *array, uint64_t count) {
    if (!array) {
        return;
    }
    
    assert(kIDPArrayMaximumCapacity >= count);
        
    array->_count = count;
        
    IDPArrayResizeIfNeeded(array);
}

void IDPArraySetObjectAtIndex(IDPArray *array, void *object, uint64_t index) {
    if (!array) {
        return;
    }
    
    assert(index < IDPArrayGetCount(array));
    
    IDPObject *currentObject = array->_data[index];
    if (currentObject != object) {
        IDPObjectRetain(object);
        IDPObjectRelease(currentObject);
        
        array->_data[index] = object;
    }
}

