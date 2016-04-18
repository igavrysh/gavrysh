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
//#include


#pragma mark -
#pragma mark Private Declaration

static
void IDPObjectCreationTest();

#pragma mark -
#pragma mark Public Implementation

void IDPObjectBehaviorTests(void) {
    
}

#pragma mark -
#pragma mark Private Implementation

void IDPObjectOneObjectCreationTest() {
    // after IDPObject was created
    IDPObject *object = IDPObjectCreateOfType(IDPObject);
    
    //  object should not be NULL
    assert(NULL != object);
    
    //  object reference count must be equalt to 1
    assert(1 == IDPObjectGerReferenceCount(object));
    
    //  after object retaining
    IDPObject *retainedObject = IDPObjectRetain(object);
    
    //      ratained object must be equal to object
    assert(object == retainedObject);
    
    //      object reference count must be equal to 2
    assert(2 == IDPObjectGerReferenceCount(object));
    
    //  after releasing retained object equalt ot 1
    IDPObjectRelease(object);
    
    assert(1 == IDPObjectGerReferenceCount(object));
    
    IDPObjectRelease(object);
}
