//
//  IDPHumanTests.c
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>
#include <string.h>

#include "IDPHumanTests.h"
#include "IDPHuman.h"
#include "IDPPrintingFunctions.h"

#pragma mark -
#pragma mark Private Declaration

static
void IDPHumanCreationTest();

static
void IDPHumanGettersAndSettersTest();

#pragma mark -
#pragma mark Public Implementation

void IDPHumanBehaviorTests(void) {
    performTest(IDPHumanCreationTest);
    
    performTest(IDPHumanGettersAndSettersTest);
}

#pragma mark -
#pragma mark Private Implementation

void IDPHumanCreationTest() {
    
    //  after IDPHuman was created
    //      IDPHuman should not be NULL
    //      object reference count should be equal to 1
    //  after IDPHuman retaining
    //      retained IDPHuman must be equal to object
    //      object reference count shoul be equal to 2
    //  after releasing retained object, reference count must be equal to 1
    //  after secondly releasing retained object it must be deleted with a ??freed memory??
    
    IDPHuman *human = IDPHumanCreate();
    
    assert(NULL != human);
    
    assert(1 == IDPObjectGetReferenceCount(human));
    
    IDPHuman *retainedHuman = (IDPHuman *)IDPObjectRetain(human);
    
    assert(human == retainedHuman);
    
    assert(2 == IDPObjectGetReferenceCount(human));
    
    IDPObjectRelease(human);
    
    assert(1 == IDPObjectGetReferenceCount(human));
    
    IDPObjectRelease(human);
}

void IDPHumanGettersAndSettersTest() {
    
    //  after IDPHuman was created and name assignment, age and gender assignment was done
    //      check that _name reference count is equal to 1
    //      check getters
    char *pamelaName = "Pamela Anderson";
    IDPString *pamelaNameExt = IDPStringCreateWithString(pamelaName);

    uint8_t pamelaAge = 48;
    
    IDPHuman *pamela = IDPHumanCreate();
    
    IDPHumanSetName(pamela, pamelaNameExt);
    IDPHumanSetAge(pamela, pamelaAge);
    IDPHumanSetGender(pamela, IDPHumanGenderFemale);
    
    assert(1 == IDPObjectGetReferenceCount(pamela->_name));
    assert(0 == strcmp(IDPHumanGetName(pamela)->_string, pamelaName));
    assert(pamelaAge == IDPHumanGetAge(pamela));
    assert(IDPHumanGenderFemale == IDPHumanGetGender(pamela));
    
}
