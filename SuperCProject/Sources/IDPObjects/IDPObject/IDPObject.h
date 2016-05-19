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

typedef void (*IDPObjectProcedurePointer)(void *);

typedef void *(*IDPOwnershipMethod)(void *);

typedef struct IDPObject IDPObject;

struct IDPObject {
    uint64_t _referenceCount;
    
    IDPObjectProcedurePointer _releaseFunction;
    
    IDPObjectProcedurePointer _deallocator;
};

extern
void *__IDPObjectCreate(size_t objectSize, IDPObjectProcedurePointer deallocateCallback);

extern
void *IDPObjectAutorelease(void *object);

extern
void *__IDPSingletonObjectCreate(void **singletonPointer, size_t objectSize, IDPObjectProcedurePointer deallocateCallBack);

#define IDPObjectCreateWithType(type) \
    __IDPObjectCreate(sizeof(type), (IDPObjectProcedurePointer)__##type##Deallocate)

#define IDPObjectCreate(type) \
    IDPObjectAutorelease(__IDPObjectCreate(sizeof(type), (IDPObjectProcedurePointer)__##type##Deallocate))

#define IDPSingletonObjectCreateOfType(singletonPointer, type) \
    __IDPSingletonObjectCreate((void **)singletonPointer, sizeof(type), (IDPObjectProcedurePointer)__##type##Deallocate)

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
