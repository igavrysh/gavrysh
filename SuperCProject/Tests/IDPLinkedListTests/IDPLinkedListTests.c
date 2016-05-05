//
//  IDPLinkedListTests.c
//  SuperCProject
//
//  Created by Ievgen on 5/6/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>
#include <string.h>

#include "IDPLinkedList.h"
#include "IDPLinkedListTests.h"

#include "IDPPrintingFunctions.h"

#pragma mark -
#pragma mark Private Declaration

static
void IDPLinkedListOneNodeTest();

#pragma mark -
#pragma mark Public Implementation

void IDPLinkedListBehaviorTests(void) {
    
    IDPPerformTest(IDPLinkedListOneNodeTest);
}

#pragma mark -
#pragma mark Private Implementation

void IDPLinkedListOneNodeTest() {
    
}
