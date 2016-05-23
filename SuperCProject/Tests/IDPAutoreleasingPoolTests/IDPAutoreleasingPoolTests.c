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
void IDPAutoreleasingPoolFlatTest(void);

static
void IDPAutoreleasingPoolHierarchyFlatTest(void);

static
void IDPAutoreleasingMultiplePoolsTest(void);

#pragma mark -
#pragma mark Public Implementations

void IDPAutoreleasingPoolBehaviorTests(void) {
    IDPPerformTest(IDPAutoreleasingOnePoolTest);
    
    IDPPerformTest(IDPAutoreleasingPoolHierarchyFlatTest);
    
    IDPPerformTest(IDPAutoreleasingMultiplePoolsTest);
    
    IDPPerformTest(IDPAutoreleasingPoolFlatTest);
    
    IDPPerformTest(IDPAutoreleasingPoolFlatTest);
    
    IDPPerformTest(IDPAutoreleasingPoolFlatTest);
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

void IDPAutoreleasingPoolFlatTest(void) {
    uint64_t count = 500000;
    
    IDPObject *array[count];
    
    IDPAutoreleasingPoolCreate();
    
    for (uint64_t index = 0; index < count; index++) {
        IDPObject *object = IDPObjectCreate(IDPObject);
        array[index] = IDPObjectRetain(object);
        assert(2 == IDPObjectGetReferenceCount(object));
    }
    
    IDPAutoreleasingPoolDrain();
    
    for (uint64_t index = 0; index < count; index++) {
        assert(1 == IDPObjectGetReferenceCount(array[index]));
        IDPObjectRelease(array[index]);
    }
}

void IDPAutoreleasingPoolHierarchyFlatTest(void) {
    uint64_t count = 7000;
    
    IDPObject *array[count];
    
    IDPAutoreleasingPoolCreate();
    IDPAutoreleasingPoolCreate();
    IDPAutoreleasingPoolCreate();
    for (uint64_t index = 0; index < count; index++) {
        
        IDPObject *object = IDPObjectCreate(IDPObject);
        
        array[index] = IDPObjectRetain(object);
        
        assert(2 == IDPObjectGetReferenceCount(object));
        
    }
    
    IDPAutoreleasingPoolDrain();
    IDPAutoreleasingPoolDrain();
    IDPAutoreleasingPoolDrain();
    
    for (uint64_t index = 0; index < count; index++) {
        assert(1 == IDPObjectGetReferenceCount(array[index]));
        IDPObjectRelease(array[index]);
    }
}


void IDPAutoreleasingMultiplePoolsTest(void) {
    IDPAutoreleasingPoolCreate();
    
    uint64_t count = 500;
    
    assert(1 == IDPObjectGetReferenceCount(IDPAutoreleasingPoolGet()));
    
    IDPObject *object = IDPObjectCreate(IDPObject);
    
    for (uint64_t index = 0; index < count; index++) {
        IDPAutoreleasingPoolCreate();
        
        IDPObject *object2 = IDPObjectCreate(IDPObject);
        
        IDPObjectRetain(object2);
        
        for (uint64_t index2 = 0; index2 < count; index2++) {
            IDPAutoreleasingPoolCreate();
            
            IDPObject *object3 = IDPObjectCreate(IDPObject);
            
            IDPObjectRetain(object3);
            
            assert(2 == IDPObjectGetReferenceCount(object3));
            
            assert(2 == IDPObjectGetReferenceCount(object2));
            
            assert(1 == IDPObjectGetReferenceCount(object));
            
            IDPAutoreleasingPoolDrain();
            
            assert(1 == IDPObjectGetReferenceCount(object3));
            
            IDPObjectRelease(object3);
        }
        assert(2 == IDPObjectGetReferenceCount(object2));
        
        assert(1 == IDPObjectGetReferenceCount(object));
        
        IDPAutoreleasingPoolDrain();
        
        assert(1 == IDPObjectGetReferenceCount(object2));
        
        IDPObjectRelease(object2);
    }
    
    assert(1 == IDPObjectGetReferenceCount(object));
    
    IDPAutoreleasingPoolDrain();
}
