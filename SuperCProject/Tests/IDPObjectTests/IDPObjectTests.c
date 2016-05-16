//
//  IDPObjectTests.c
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 4/13/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>

#include "IDPObjectTests.h"
#include "IDPObject.h"
#include "IDPPrintingFunctions.h"


#pragma mark -
#pragma mark Private Declaration

static
void IDPObjectOneObjectCreationTest();

static
void IDPSingletonObjectTest();

#pragma mark -
#pragma mark Public Implementation

void IDPObjectBehaviorTests(void) {
    IDPPerformTest(IDPObjectOneObjectCreationTest);
    
    IDPPerformTest(IDPSingletonObjectTest);
}

#pragma mark -
#pragma mark Private Implementation

void IDPObjectOneObjectCreationTest() {
    // after IDPObject was created
    IDPObject *object = IDPObjectCreateWithType(IDPObject);
    
    //  object should not be NULL
    assert(NULL != object);
    
    //  object reference count must be equalt to 1
    assert(1 == IDPObjectGetReferenceCount(object));
    
    //  after object retaining
    IDPObject *retainedObject = IDPObjectRetain(object);
    
    //      ratained object must be equal to object
    assert(object == retainedObject);
    
    //      object reference count must be equal to 2
    assert(2 == IDPObjectGetReferenceCount(object));
    
    //  after releasing retained object equalt ot 1
    IDPObjectRelease(object);
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPObjectRelease(object);
}

void IDPSingletonObjectTest() {
    static IDPObject *sharedObject;
    //  after singleton object was created
    IDPObject *object = IDPSingletonObjectCreateOfType(&sharedObject, IDPObject);

    //      it should not be NULL
    assert(NULL != object);
    
    //      its reference count must be 1
    assert(1 == IDPObjectGetReferenceCount(object));
    
    //      shated Object must be equal to object
    assert(sharedObject == object);
    
    //  after singleton object was released
    IDPObjectRelease(object);
    
    //      reference count must not change
    assert(1 == IDPObjectGetReferenceCount(object));
    
    // while singleton created 5 times
    //      it must be equal to shared object
    for (uint8_t iterator = 0; iterator < 5; iterator++) {
        void *object2 = IDPSingletonObjectCreateOfType(&sharedObject, IDPObject);
        assert(sharedObject == object2);
    }
}
