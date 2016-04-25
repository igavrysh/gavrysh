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

static
void IDPHumanBornChildTest();

static
void IDPHumanBornChildrenTest();

#pragma mark -
#pragma mark Public Implementation

void IDPHumanBehaviorTests(void) {
    /*
    performTest(IDPHumanCreationTest);
    
    performTest(IDPHumanGettersAndSettersTest);
    
    performTest(IDPHumanMarriageTest);
    
    performTest(IDPHumanMarriageReversedReleasingTest);
    */
    
    performTest(IDPHumanBornChildTest);
    
    performTest(IDPHumanBornChildrenTest);
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
    
    IDPHumanGetMarriedWithPartner(fiance1, bride1);
    assert(2 == IDPObjectGetReferenceCount(bride1));
    assert(1 == IDPObjectGetReferenceCount(fiance1));
    assert(IDPHumanIsMarried(bride1));
    assert(IDPHumanIsMarried(fiance1));
    
    IDPHuman *bride2 = IDPHumanCreate();
    IDPHumanSetGender(bride2, IDPHumanGenderFemale);
    IDPHuman *fiance2 = IDPHumanCreate();
    IDPHumanSetGender(fiance2, IDPHumanGenderMale);
    IDPHuman *bride3 = IDPHumanCreate();
    IDPHumanSetGender(bride3, IDPHumanGenderFemale);
    IDPHuman *fiance3 = IDPHumanCreate();
    IDPHumanSetGender(fiance3, IDPHumanGenderMale);
    
    IDPHumanGetMarriedWithPartner(fiance1, bride2);
    assert(1 == IDPObjectGetReferenceCount(bride1));
    assert(2 == IDPObjectGetReferenceCount(bride2));
    assert(1 == IDPObjectGetReferenceCount(fiance1));
    assert(!IDPHumanIsMarried(bride1));
    assert(IDPHumanIsMarried(fiance1));
    assert(IDPHumanIsMarried(bride2));
    
    
    IDPHumanGetMarriedWithPartner(bride2, fiance2);
    assert(1 == IDPObjectGetReferenceCount(bride1));
    assert(1 == IDPObjectGetReferenceCount(fiance2));
    assert(2 == IDPObjectGetReferenceCount(bride2));
    assert(1 == IDPObjectGetReferenceCount(fiance1));
    assert(!IDPHumanIsMarried(bride1));
    assert(!IDPHumanIsMarried(fiance1));
    assert(IDPHumanIsMarried(bride2));
    assert(IDPHumanIsMarried(fiance2));
    
    
    IDPObjectRelease(fiance3);
    
    IDPObjectRelease(fiance2);
    IDPObjectRelease(bride2);
    

    IDPObjectRelease(bride1);
    IDPObjectRelease(fiance1);
    
    IDPObjectRelease(bride3);
    
    assert(0 == IDPObjectGetReferenceCount(bride1));
    assert(0 == IDPObjectGetReferenceCount(fiance1));
    assert(0 == IDPObjectGetReferenceCount(bride2));
    assert(0 == IDPObjectGetReferenceCount(fiance2));
    assert(0 == IDPObjectGetReferenceCount(bride3));
    assert(0 == IDPObjectGetReferenceCount(fiance3));
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
    
    IDPHumanGetMarriedWithPartner(fiance1, bride1);
    assert(2 == IDPObjectGetReferenceCount(bride1));
    assert(1 == IDPObjectGetReferenceCount(fiance1));
    
    IDPObjectRelease(fiance1);
    IDPObjectRelease(bride1);
    
    assert(0 == IDPObjectGetReferenceCount(bride1));
    assert(0 == IDPObjectGetReferenceCount(fiance1));
}

void IDPHumanBornChildTest() {
    //  after man and woman were created and married
    //      born a child
    //      check that child reference count is equal to 2, mother and futher referes to the newly created child
    //
    IDPHuman *male = IDPHumanCreate();
    IDPHuman *female = IDPHumanCreate();
    IDPHumanSetGender(male, IDPHumanGenderMale);
    IDPHumanSetGender(female, IDPHumanGenderFemale);

    IDPHumanGetMarriedWithPartner(male, female);
    IDPHuman *child = IDPHumanGetBirthChild(female);
    assert(2 == IDPObjectGetReferenceCount(child));
    
    IDPObjectRelease(child);
    IDPObjectRelease(child);
    
    //assert(0 == IDPObjectGetReferenceCount(child));
    
    assert(0 == IDPHumanGetChildrenCount(male));
    
    assert(0 == IDPHumanGetChildrenCount(female));
}


void IDPHumanBornChildrenTest() {
    IDPHuman *male = IDPHumanCreate();
    IDPHuman *female = IDPHumanCreate();
    IDPHumanSetGender(male, IDPHumanGenderMale);
    IDPHumanSetGender(female, IDPHumanGenderFemale);
    
    IDPHumanGetMarriedWithPartner(male, female);
    
    IDPHuman *child1 = IDPHumanGetBirthChild(female);
    assert(2 == IDPObjectGetReferenceCount(child1));
    
    IDPHuman *child2 = IDPHumanGetBirthChild(female);
    assert(2 == IDPObjectGetReferenceCount(child2));
    
    IDPHuman *child3 = IDPHumanGetBirthChild(female);
    assert(2 == IDPObjectGetReferenceCount(child3));
    
    IDPObjectRelease(child2);
    IDPObjectRelease(child2);
    
    assert(2 == IDPHumanGetChildrenCount(male));
    assert(2 == IDPHumanGetChildrenCount(female));
    
    assert(2 == IDPObjectGetReferenceCount(child1));
    assert(2 == IDPObjectGetReferenceCount(child3));
}



