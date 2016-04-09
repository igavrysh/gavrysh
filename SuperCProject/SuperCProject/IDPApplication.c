//
//  IDPApplication.c
//  SuperCProject
//
//  Created by Ievgen on 4/8/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "IDPApplication.h"
#include "IDPPrintingFunctions.h"
#include "IDPBranchingAndStates.h"
#include "IDPTypesAndRanges.h"
#include "IDPPrintReversed.h"
#include "IDPBasicMathOperations.h"

void IDPRunApplication() {
    IDPTestSecondAssignment();
}

void IDPTestFirstAssignment() {
    IDPPrintTestMessage("Testing console output");
    ICPrintNewLine();
    IDPPrintTest("$1mln dollars start up");
    
    ICPrintGreetingToMama();
    ICPrintNewLineWithCount(2);
    
    ICPrintGreetingToPapa();
    ICPrintNewLineWithCount(3);
}

void IDPTestStackBasedStringReversal() {
    IDPPrintTestMessage("Testing stack-based string reversal");
    char *inputString = "1234567890";
    char *reversedString = IDPCreateReversedStringForString(inputString);
    printf("Reversed string for %s is %s\n", inputString, reversedString);
    free(reversedString);
}

void IDPTestBoolToStringConversion() {
    IDPPrintTestMessage("Testing bool to string conversion");
    char *strForBool = IDPCreateStringForBoolValue(true);
    printf("%s\n", strForBool);
    free(strForBool);
}

void IDPTestBranchingTypes() {
    IDPPrintTestMessage("Testing ternary and ordinary branching");
    IDPPrintMamaPapaStdBranching(2, 5);
    IDPPrintMamaPapaTernaryBranching(2, 5);
}

void IDPTestStateIdentification() {
    IDPPrintTestMessage("Testing State Identification: Deputy task");
    IDPPrintDeputyStateForSalaryAndIncome(12.f, 10000000.f);
    IDPPrintTestMessage("Testing State Identification: mama, papa, mamapapa task");
    IDPDisplayStateForNumber(15);
}

void IDPTestTypeConversionAndRangeIdentification() {
    IDPPrintTestMessage("Testing type conversion and range identification");
    IDPPrintRangeForType("char");
    IDPPrintRangeForType("short");
    IDPPrintRangeForType("int");
    IDPPrintRangeForType("long");
    IDPPrintRangeForType("unsigned long");
}

void IDPTestDifferentTypesPrinting() {
    IDPPrintTestMessage("Testing different data types printing");
    IDPPrintMostCommonTypes();
}

void IDPTestBasicMathOperations() {
    IDPPrintTestMessage("Testing incremental/decremental operations");
    int initialVar = 10;
    int incrementedVar = IDPIncrement(initialVar);
    int decrementedVar = IDPDecrement(initialVar);
    printf("Initial var = %d, its value decremented = %d, and incremented = %d\n",
           initialVar,
           decrementedVar,
           incrementedVar);
    
}

void IDPTestCastingOperations() {
    IDPPrintTestMessage("Testing casting operations");
    IDPPrintCastingOperationResults();
}

void IDPTestExpressionExpansion() {
    IDPPrintTestMessage("Testing formula expansion");
    IDPPrintResultOfSepararedOperations();
}

void IDPTestPrePostFixIncrement() {
    IDPPrintTestMessage("Testing pre/postfix increment");
    IDPrintPrePosfixIncrementResult();
}

void IDPTestSecondAssignment() {
    IDPTestStackBasedStringReversal();
    
    IDPTestTypeConversionAndRangeIdentification();
    
    IDPTestDifferentTypesPrinting();
    
    IDPTestBoolToStringConversion();
    
    IDPTestBranchingTypes();
    
    IDPTestBasicMathOperations();
    
    IDPTestCastingOperations();
    
    IDPTestExpressionExpansion();
    
    IDPTestStateIdentification();
    
    IDPTestPrePostFixIncrement();
}

