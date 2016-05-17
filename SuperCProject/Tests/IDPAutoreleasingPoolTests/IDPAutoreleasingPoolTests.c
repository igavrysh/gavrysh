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
    
}


void IDPAutoreleasingMultiplePoolsTest(void) {
    
}