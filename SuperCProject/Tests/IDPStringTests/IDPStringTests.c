//
//  IDPNameTests.c
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <assert.h>
#include <string.h>

#include "IDPString.h"
#include "IDPStringTests.h"
#include "IDPPrintingFunctions.h"

#pragma mark -
#pragma mark Private Declarations
void IDPSimpleStringTest();

#pragma mark -
#pragma mark Public Implementations
void IDPStringTestPerform() {
    performTest(IDPSimpleStringTest);
}

#pragma mark -
#pragma mark Private Implementations
void IDPSimpleStringTest() {
    //  after IDPString was created
    //      object should not be NULL
    //      object reference count equals to 1
    //  after setting IDPString value to string "Hellow"
    //      object should not be NULL
    //      object reference count equals to 1
    //      getter should return string "Hellow"
    //  after object retaining
    //      ratained object must be equal to object
    //      object reference count must be equal to 2
    //  after releasing retained equals 1
    
    
    char *testString = "Hellow";
    
    IDPString *string = IDPStringCreateWithString(testString);
    assert(NULL != string);
    assert(1 == IDPObjectGetReferenceCount(string));
    
    assert(0 == strcmp(IDPStringGetString(string), testString));
    
    string = IDPObjectRetain(string);
    assert(2 == IDPObjectGetReferenceCount(string));
    
    assert(0 == strcmp(IDPStringGetString(string), testString));
    
    IDPObjectRelease(string);
    assert(1 == IDPObjectGetReferenceCount(string));
    
    char *testString2 = "Hellow new world!!!";
    
    IDPStringSetString(string,  testString2);
    assert(1 == IDPObjectGetReferenceCount(string));
    assert(0 == strcmp(IDPStringGetString(string), testString2));

    IDPObjectRelease(string);
    assert(0 == IDPObjectGetReferenceCount(string));
}

