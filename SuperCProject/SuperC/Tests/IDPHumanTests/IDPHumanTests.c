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

static
void IDPHumanBornChildrenArrayOverflowTest();

#pragma mark -
#pragma mark Public Implementation

void IDPHumanBehaviorTests(void) {
    IDPPerformTest(IDPHumanCreationTest);
    
    IDPPerformTest(IDPHumanGettersAndSettersTest);
    
    IDPPerformTest(IDPHumanMarriageTest);
    
    IDPPerformTest(IDPHumanMarriageReversedReleasingTest);
    
    IDPPerformTest(IDPHumanBornChildTest);
    
    IDPPerformTest(IDPHumanBornChildrenTest);
    
    IDPPerformTest(IDPHumanBornChildrenArrayOverflowTest);
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
    
    IDPObjectRelease(retainedHuman);
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
    assert(NULL == pamela->_name);
    
    IDPObjectRelease(pamelaNameExt);
    IDPObjectRelease(pamela);
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

    IDPObjectRelease(fiance1);
    IDPObjectRelease(bride1);
    
    IDPObjectRelease(fiance2);
    IDPObjectRelease(bride2);
    
    IDPObjectRelease(fiance3);
    IDPObjectRelease(bride3);
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
    IDPHuman *child = IDPHumanGiveBirthToChild(female);
    assert(2 == IDPObjectGetReferenceCount(child));
    
    IDPObjectRelease(child);
    IDPObjectRelease(child);
    
    IDPObjectRelease(male);
    IDPObjectRelease(female);
}

void IDPHumanBornChildrenTest() {
    IDPHuman *male = IDPHumanCreate();
    IDPHuman *female = IDPHumanCreate();
    IDPHumanSetGender(male, IDPHumanGenderMale);
    IDPHumanSetGender(female, IDPHumanGenderFemale);
    
    IDPHumanGetMarriedWithPartner(male, female);
    
    IDPHuman *child1 = IDPHumanGiveBirthToChild(female);
    assert(2 == IDPObjectGetReferenceCount(child1));
    
    IDPHuman *child2 = IDPHumanGiveBirthToChild(female);
    assert(2 == IDPObjectGetReferenceCount(child2));
    
    IDPHuman *child3 = IDPHumanGiveBirthToChild(female);
    assert(2 == IDPObjectGetReferenceCount(child3));
    
    IDPObjectRelease(child2);
    assert(1 == IDPObjectGetReferenceCount(child2));
    IDPObjectRelease(child2);
    
    assert(2 == IDPHumanGetChildrenCount(male));
    assert(2 == IDPHumanGetChildrenCount(female));
    
    assert(2 == IDPObjectGetReferenceCount(child1));
    assert(2 == IDPObjectGetReferenceCount(child3));
    
    IDPObjectRelease(male);
    IDPObjectRelease(female);
}

void IDPHumanBornChildrenArrayOverflowTest() {
    IDPHuman *male = IDPHumanCreate();
    IDPHuman *female = IDPHumanCreate();
    IDPHumanSetGender(male, IDPHumanGenderMale);
    IDPHumanSetGender(female, IDPHumanGenderFemale);
    
    IDPHumanGetMarriedWithPartner(male, female);
    
    for (uint64_t index = 0; index < kIDPHumanMaxChildrenCount + 1; index++) {
        IDPHuman *child = IDPHumanGiveBirthToChild(female);
        char num[10];
        sprintf(num, "%llu", index);
        IDPString *str = IDPStringCreateWithString(num);
        IDPHumanSetName(child, str);
        IDPObjectRelease(str);
    }
    
    assert(kIDPHumanMaxChildrenCount == IDPHumanGetChildrenCount(male));
    
    IDPObjectRelease(male);
    IDPObjectRelease(female);
}

