//
//  IDPObject.h
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/13/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPObject_h
#define IDPObject_h

#include <stdlib.h>

typedef void (*IDPObjectDeallocatorCallback)(void *);

typedef void *(*IDPOwnershipMethod)(void *);

typedef struct {
    uint64_t _referenceCount;
    
    IDPObjectDeallocatorCallback _deallocator;
} IDPObject;

extern
void *__IDPObjectCreate(size_t objectSize, IDPObjectDeallocatorCallback deallocateCallback);

#define IDPObjectCreateWithType(type) \
__IDPObjectCreate(sizeof(type), (IDPObjectDeallocatorCallback)__##type##Deallocate)

extern
void *IDPObjectRetain(void *object);

extern
void IDPObjectRelease(void *object);

extern
void __IDPObjectDeallocate(void *object);

extern
uint64_t IDPObjectGetReferenceCount(void *object);

extern
void __IDPObjectSetFieldValueWithMethod(void *object, void **field, void *value, IDPOwnershipMethod retainMethod);

#endif /* IDPObject_h */
