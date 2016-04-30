//
//  IDPArray.h
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/17/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPArray_h
#define IDPArray_h

#include <stdbool.h>

#include "IDPObject.h"

static const uint64_t kIDPNotFound = UINT64_MAX;

typedef struct IDPArray IDPArray;

struct IDPArray {
    IDPObject _super;
    
    void **_data;
    uint64_t _count;
    uint64_t _capacity;
};

extern
void *IDPArrayCreateWithCapacity(uint64_t capacity);

extern
void __IDPArrayDeallocate(void *object);

//// return index of added object. Otherwide kIDPNotFound
extern
void IDPArrayAddObject(IDPArray *array, void *object);

extern
uint64_t IDPArrayGetCount(IDPArray *array);

extern
bool IDPArrayContainsObject(IDPArray *array, void *object);

extern
uint64_t IDPArrayGetIndexOfObject(IDPArray *array, void *object);

extern
void *IDPArrayGetObjectAtIndex(IDPArray *array, uint64_t index);

extern
void IDPArrayRemoveObjectAtIndex(IDPArray *array, uint64_t index);

extern
void IDPArrayRemoveAllObjects(IDPArray *array);

extern
void IDPArrayReorderArray(IDPArray * array);

#endif /* IDPArray_h */
