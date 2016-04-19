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

static
void IDPHumanMarriageTest();

static
void IDPHumanMarriageReversedReleasingTest();

#pragma mark -
#pragma mark Public Implementation

void IDPHumanBehaviorTests(void) {
    performTest(IDPHumanCreationTest);
    
    performTest(IDPHumanGettersAndSettersTest);
    
    performTest(IDPHumanMarriageTest);
    
    performTest(IDPHumanMarriageReversedReleasingTest);
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
    
    IDPHumanSetName(pamela, NULL);
    assert(0 == IDPObjectGetReferenceCount(pamela->_name));
}

void IDPHumanMarriageTest() {
    //  after bride and fiance were created
    //      bride is not married
    //      fiance is not married
    //  after bride and fiance created and they are married
    //      bride is strongly referenced from fiance's partner
    //      fiance is weakly referenced as bride's partner
    IDPHuman *bride1 = IDPHumanCreate();
    IDPHumanSetGender(bride1, IDPHumanGenderFemale);
    IDPHuman *fiance1 = IDPHumanCreate();
    IDPHumanSetGender(fiance1, IDPHumanGenderMale);
    
    assert(1 == IDPObjectGetReferenceCount(bride1));
    assert(1 == IDPObjectGetReferenceCount(fiance1));
    
    assert(false == IDPHumanIsMarried(bride1));
    assert(false == IDPHumanIsMarried(bride1));
    
    IDPHumanGetMarriedWoman(fiance1, bride1);
    assert(2 == IDPObjectGetReferenceCount(bride1));
    assert(1 == IDPObjectGetReferenceCount(fiance1));
    
    IDPObjectRelease(bride1);
    IDPObjectRelease(fiance1);
    
    assert(0 == IDPObjectGetReferenceCount(bride1));
    assert(0 == IDPObjectGetReferenceCount(fiance1));
}

void IDPHumanMarriageReversedReleasingTest() {
    //  after bride and fiance were created and married
    //  after fiance releasing and bride releasing
    //      fiance and bride reference count is equal to 0
    IDPHuman *bride1 = IDPHumanCreate();
    IDPHumanSetGender(bride1, IDPHumanGenderFemale);
    IDPHuman *fiance1 = IDPHumanCreate();
    IDPHumanSetGender(fiance1, IDPHumanGenderMale);
    
    assert(1 == IDPObjectGetReferenceCount(bride1));
    assert(1 == IDPObjectGetReferenceCount(fiance1));
    
    IDPHumanGetMarriedWoman(fiance1, bride1);
    assert(2 == IDPObjectGetReferenceCount(bride1));
    assert(1 == IDPObjectGetReferenceCount(fiance1));
    
    IDPObjectRelease(fiance1);
    IDPObjectRelease(bride1);
    
    assert(0 == IDPObjectGetReferenceCount(bride1));
    assert(0 == IDPObjectGetReferenceCount(fiance1));
}