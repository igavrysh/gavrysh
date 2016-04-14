//
//  IDPPrintingFunctionsTests.c
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "IDPPrintingFunctions.h"
#include "IDPPrintingFunctionsTests.h"
#include "IDPPrintReversed.h"

#pragma mark - Public Implementation

void IDPPrintingTestPerform() {
    IDPPrintTestMessage("Testing console output");
    ICPrintNewLine();
    IDPPrintTest("$1mln dollars start up");
    
    ICPrintGreetingToMama();
    ICPrintNewLineWithCount(2);
    
    ICPrintGreetingToPapa();
    ICPrintNewLineWithCount(3);
}

void IDPTestStackBasedStringReversalTestPerform() {
    IDPPrintTestMessage("Testing stack-based string reversal");
    
    char *inputString = "1234567890";
    
    char *reversedString = IDPCreateReversedStringForString(inputString);
    printf("Reversed string for %s is %s\n", inputString, reversedString);
    free(reversedString);
    
    IDPPrintTestMessage("Testing simple string reversal");
    reversedString = IDPCreateReversedStringForStringSimple(inputString);
    
    printf("Reversed string for %s is %s\n", inputString, reversedString);
    free(reversedString);
}

void IDPPrintNullNoneNullTerminatedStringTestPerform() {
    IDPPrintTestMessage("Testing null-none null terminating sting printing");
    
    char *nullTerminatedStr = "Hello, zhenya!";
    char noneNullTerminatedStr[5] = {'H', 'e', 'l', 'l', 'o'};
    
    puts("Null terminated string: ");
    IDPPrintNullTerminatedString(nullTerminatedStr);
    
    puts("None null terminated string: ");
    IDPPrintNonNullTerminatedStringWithSize(noneNullTerminatedStr, 5);
}
