//
//  IDPAutoreleasingPoolTests.c
//  SuperCProject
//
//  Created by Ievgen on 5/17/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>

#include "IDPAutoreleasingPoolTests.h"
#include "IDPAutoreleasingPool.h"
#include "IDPPrintingFunctions.h"

#pragma mark -
#pragma mark Private Declarations

static
void IDPAutoreleasingOnePoolTest(void);

static
void IDPAutoreleasingMultiplePoolsTest(void);

#pragma mark -
#pragma mark Public Implementations

void IDPAutoreleasingPoolBehaviorTests(void) {
    IDPPerformTest(IDPAutoreleasingOnePoolTest);
    
    IDPPerformTest(IDPAutoreleasingMultiplePoolsTest);
}

#pragma mark -
#pragma mark Private Implementation

void IDPAutoreleasingOnePoolTest(void) {
    IDPAutoreleasingPoolCreate();
    
    assert(1 == IDPObjectGetReferenceCount(IDPAutoreleasingPoolGet()));
    
    IDPObject *object = IDPObjectCreate(IDPObject);
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPObjectRetain(object);
    
    assert(2 == IDPObjectGetReferenceCount(object));
    
    IDPAutoreleasingPoolDrain();
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPObjectRelease(object);
}

void IDPAutoreleasingMultiplePoolsTest(void) {
    IDPAutoreleasingPoolCreate();
    
    uint64_t count = 2024;
    
    assert(1 == IDPObjectGetReferenceCount(IDPAutoreleasingPoolGet()));
    
    
    IDPObject *object = IDPObjectCreate(IDPObject);
    
    for (uint64_t index = 0; index < count; index++) {
        IDPAutoreleasingPoolCreate();
        
        IDPObject *object2 = IDPObjectCreate(IDPObject);
        
        for (uint64_t index2 = 0; index2 < count; index2++) {
            IDPAutoreleasingPoolCreate();
            
            IDPObject *object3 = IDPObjectCreate(IDPObject);
            
            assert(1 == IDPObjectGetReferenceCount(object3));
            
            assert(1 == IDPObjectGetReferenceCount(object2));
            
            assert(1 == IDPObjectGetReferenceCount(object));
            
            IDPAutoreleasingPoolDrain();
        }
        assert(1 == IDPObjectGetReferenceCount(object2));
        
        assert(1 == IDPObjectGetReferenceCount(object));
        
        IDPAutoreleasingPoolDrain();
    }
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPAutoreleasingPoolDrain();
}
