//
//  IDPNameTests.c
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPStringTests.h"

#include "IDPString.h"

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
    IDPString *string = IDPStringCreateWithString("Hellow");
    
    string = IDPObjectRetain(string);
    
    printf("%s\n", IDPStringGetString(string));
    
    IDPStringSetString(string, "Hellow new world!!!");
    
    printf("%s\n", IDPStringGetString(string));
    
    IDPObjectRelease(string);
}

