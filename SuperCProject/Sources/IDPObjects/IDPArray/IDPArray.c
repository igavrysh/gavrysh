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
    
    uint64_t count = IDPArrayGetCount(array);
    IDPArraySetCount(array, count + 1);
    IDPArraySetObjectAtIndex(array, object, count);
}

void IDPArrayRemoveObject(IDPArray *array, IDPObject *object) {
    if (!array || !object) {
        return;
    }
    
    IDPArrayRemoveObjectAtIndex(array, IDPArrayGetIndexOfObject(array, object));
}

void IDPArrayRemoveAllObjects(IDPArray *array) {
    uint64_t count = IDPArrayGetCount(array);
    
    for (uint64_t index = 0; index < count; index++) {
        IDPArrayRemoveObjectAtIndex(array, count - index - 1);
    }
}

void IDPArrayRemoveObjectAtIndex(IDPArray *array, uint64_t index) {
    if (!array || index >= IDPArrayGetCount(array)) {
        return;
    }
    
    IDPArraySetObjectAtIndex(array, NULL, index);
    
    uint64_t count = IDPArrayGetCount(array);
    
    memmove(array->_data + index,
            array->_data + index + 1,
            sizeof(array->_data[0]) * (count - index - 1));
    
    IDPArraySetCount(array, count - 1);
}

IDPObject *IDPArrayGetObjectAtIndex(IDPArray *array, uint64_t index) {
    if (!array || index >= IDPArrayGetCount(array)) {
        return NULL;
    }
    
    return array->_data[index];
}

void IDPArraySetObjectAtIndex(IDPArray *array, IDPObject *object, uint64_t index) {
    if (!array || index >= IDPArrayGetCount(array)) {
        return;
    }
    
    IDPObjectSetStrong(array, _data[index], object);
}

uint64_t IDPArrayGetIndexOfObject(IDPArray *array, IDPObject *object) {
    if (!array) {
        return 0;
    }
    
    uint64_t count = IDPArrayGetCount(array);
    for (uint64_t index = 0; index < count; index++) {
        if (object == IDPArrayGetObjectAtIndex(array, index)) {
            return index;
        }
    }
    
    return kIDPNotFonund;
}

uint64_t IDPArrayGetCount(IDPArray *array) {
    return  array ? array->_count : 0;
}

void IDPArraySetCount(IDPArray *array, uint64_t count) {
    if (!array) {
        return;
    }
    
    array->_count = count;
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
    
    uint64_t count = IDPArrayGetCount(array);
    uint64_t unit_size = sizeof(array->_data[0]);
    
    if (count == 0 && array->_data) {
        free(array->_data);
        array->_data = NULL;
    } else {
        array->_data = realloc(array->_data, capacity * unit_size);
        
        if (capacity > count) {
            uint64_t deltaCount = capacity - count;
            
            memset(array->_data + count, 0, deltaCount * unit_size);
        }
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
    
    uint64_t count = IDPArrayGetCount(array);
    uint64_t capacity = IDPArrayGetCapacity(array);
    
    if (count < capacity / 4) {
        return capacity / 2;
    }
    
    if (count > capacity) {
        return count * 2;
    }
    
    return capacity;
}

