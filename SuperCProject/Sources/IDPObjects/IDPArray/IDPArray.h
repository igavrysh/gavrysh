//
//  IDPArray.h
//  SuperCProject
//
//  Created by Ievgen on 5/5/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPArray_h
#define IDPArray_h

#include <limits.h>

#include "IDPObject.h"

typedef struct IDPArray IDPArray;

static const uint64_t kIDPNotFonund = UINT64_MAX;

struct IDPArray {
    IDPObject _super;
    
    void **_data;
    
    uint64_t _size;
    uint64_t _capacity;
};

extern
void __IDPArrayDeallocate(IDPArray *array);

extern
IDPArray *IDPArrayCreateWithSize(uint64_t size);

extern
void IDPArrayAddObject(IDPArray *array, IDPObject *object);

extern
void IDPArrayRemoveObject(IDPArray *array, IDPObject *object);

extern
void IDPArrayRemoveAllObjects(IDPArray *array);

extern
void IDPArrayRemoveObjectAtIndex(IDPArray *array, uint64_t index);

extern
IDPObject *IDPArrayGetObjectAtIndex(IDPArray *array, uint64_t index);

extern
void IDPArraySetObjectAtIndex(IDPArray *array, IDPObject *object, uint64_t index);

extern
uint64_t IDPArrayGetIndexOfObject(IDPArray *array, IDPObject *object);

extern
uint64_t IDPArrayGetSize(IDPArray *array);

extern
void IDPArraySetSize(IDPArray *array, uint64_t size);


#endif /* IDPArray_h */
