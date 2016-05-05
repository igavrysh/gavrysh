//
//  IDPArray.c
//  SuperCProject
//
//  Created by Ievgen on 5/5/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "IDPObject.h"
#include "IDPObjectMacros.h"
#include "IDPArray.h"

#pragma mark -
#pragma mark Private Declarations

static
uint64_t IDPArrayGetCapacity(IDPArray *array);

static
void IDPArraySetCapacity(IDPArray *array, uint64_t capacity);

static
void IDPArrayResizeIfNeeded(IDPArray *array);

static
bool IDPArrayShouldResize(IDPArray *array);

static
uint64_t IDPArrayGetPrefferedCapacity(IDPArray *array);

#pragma mark - 
#pragma mark Public Implementations

void __IDPArrayDeallocate(IDPArray *array) {
    IDPArrayRemoveAllObjects(array);
    
    __IDPObjectDeallocate(array);
}

IDPArray *IDPArrayCreateWithCapacity(uint64_t capacity) {
    IDPArray *array = IDPObjectCreateWithType(IDPArray);
    IDPArraySetCapacity(array, capacity);
    
    return array;
}

void IDPArrayAddObject(IDPArray *array, IDPObject *object) {
    if (!array) {
        return;
    }
    
    uint64_t size = IDPArrayGetSize(array);
    IDPArraySetSize(array, size + 1);
    IDPArraySetObjectAtIndex(array, object, size);
}

void IDPArrayRemoveObject(IDPArray *array, IDPObject *object) {
    if (!array || !object) {
        return;
    }
    
    IDPArrayRemoveObjectAtIndex(array, IDPArrayGetIndexOfObject(array, object));
}

void IDPArrayRemoveAllObjects(IDPArray *array) {
    uint64_t size = IDPArrayGetSize(array);
    
    for (uint64_t index = 0; index < size; index++) {
        IDPArrayRemoveObjectAtIndex(array, index);
    }
}

void IDPArrayRemoveObjectAtIndex(IDPArray *array, uint64_t index) {
    if (!array || index >= IDPArrayGetSize(array)) {
        return;
    }
    
    IDPArraySetObjectAtIndex(array, NULL, index);
    
    uint64_t size = IDPArrayGetSize(array);
    
    memmove(array->_data[index],
            array->_data[index + 1],
            sizeof(array->_data) * (size - index - 1));
    
    IDPArraySetSize(array, size - 1);
}

IDPObject *IDPArrayGetObjectAtIndex(IDPArray *array, uint64_t index) {
    if (!array || index >= IDPArrayGetSize(array)) {
        return NULL;
    }
    
    return array->_data[index];
}

void IDPArraySetObjectAtIndex(IDPArray *array, IDPObject *object, uint64_t index) {
    if (!array || index >= IDPArrayGetSize(array)) {
        return;
    }
    
    IDPObjectSetStrong(array, _data[index], object);
}

uint64_t IDPArrayGetIndexOfObject(IDPArray *array, IDPObject *object) {
    if (!array) {
        return 0;
    }
    
    uint64_t size = IDPArrayGetSize(array);
    for (uint64_t index = 0; index < size; index++) {
        if (object == IDPArrayGetObjectAtIndex(array, index)) {
            return index;
        }
    }
    
    return kIDPNotFonund;
}

uint64_t IDPArrayGetSize(IDPArray *array) {
    return  array ? array->_size : 0;
}

void IDPArraySetSize(IDPArray *array, uint64_t size) {
    if (!array) {
        return;
    }
    
    array->_size = size;
    IDPArrayResizeIfNeeded(array);
}

#pragma mark -
#pragma mark Private Implementations

uint64_t IDPArrayGetCapacity(IDPArray *array) {
    return array ? array->_capacity : 0;
}

void IDPArraySetCapacity(IDPArray *array, uint64_t capacity) {
    if (!array && array->_capacity == capacity) {
        return;
    }
    
    if (capacity == 0 && array->_data) {
        free(array->_data);
        array->_data = NULL;
    } else {
        uint64_t size = IDPArrayGetSize(array);
        
        array->_data = realloc(array->_data, capacity * sizeof(array->_data));
        
        memset(array->_data, 0, (capacity - size) * sizeof(array->_data));
    }
    
    array->_capacity = capacity;
}

void IDPArrayResizeIfNeeded(IDPArray *array) {
    if (IDPArrayShouldResize(array)) {
        IDPArraySetCapacity(array, IDPArrayGetPrefferedCapacity(array));
    }
}

bool IDPArrayShouldResize(IDPArray *array) {
    return IDPArrayGetCapacity(array) != IDPArrayGetPrefferedCapacity(array);
}

uint64_t IDPArrayGetPrefferedCapacity(IDPArray *array) {
    if (!array) {
        return 0;
    }
    
    uint64_t size = IDPArrayGetSize(array);
    uint64_t capacity = IDPArrayGetCapacity(array);
    
    if (size < capacity / 4) {
        return capacity / 2;
    }
    
    if (size > capacity) {
        return size * 2;
    }
    
    return capacity;
}

