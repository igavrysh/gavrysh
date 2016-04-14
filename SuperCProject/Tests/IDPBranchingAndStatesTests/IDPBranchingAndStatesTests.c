//
//  IDPBranchinAndStatesTests.c
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "IDPBranchingAndStatesTests.h"
#include "IDPBranchingAndStates.h"
#include "IDPPrintingFunctions.h"
#include "IDPBasicMathOperations.h"
#include "IDPCycles.h"
#include "IDPTypesAndRanges.h"

#pragma mark - Public Implementation

void IDPMamaPapaAssignmentTestPerform() {
    puts("Expected result mama, actual result is ");
    IDPPrintStatePrintWithNumber(3);
    printf("\n");
    
    puts("Expected result papa, actual result is ");
    IDPPrintStatePrintWithNumber(5);
    printf("\n");
    
    puts("Expected result mamapapa, actual result is ");
    IDPPrintStatePrintWithNumber(15);
    printf("\n");
    
    puts("Iterative get state calling");
    for (int counter = 0; counter <= 1000; counter++) {
        printf("Iteration #%d :", counter + 1);
        IDPPrintStatePrintWithNumber(counter);
        printf("\n");
    }
}

void IDPBoolToStringConversionTestPerform() {
    IDPPrintTestMessage("Testing bool to string conversion");
    
    char *strForBool = IDPCreateStringForBoolValue(true);
    
    printf("%s\n", strForBool);
    
    free(strForBool);
}

void IDPBranchingTypesTestPerform() {
    IDPPrintTestMessage("Testing ternary and ordinary branching");
    IDPPrintMamaPapaStdBranching(2, 5);
    IDPPrintMamaPapaTernaryBranching(2, 5);
}

void IDPStateIdentificationTestPerform() {
    IDPPrintTestMessage("Testing State Identification: Deputy task");
    IDPPrintDeputyStateWithSalaryAndIncome(12.f, 10000000.f);
    
    IDPPrintTestMessage("Testing State Identification: mama, papa, mamapapa task");
    IDPPrintStatePrintWithNumber(15);
}

void IDPDifferentTypesPrintingTestPerform() {
    IDPPrintTestMessage("Testing different data types printing");
    IDPPrintMostCommonTypes();
}

void IDPBasicMathOperationsTestPerform() {
    IDPPrintTestMessage("Testing incremental/decremental operations");
    
    int initialVar = 10;
    
    int incrementedVar = IDPIncrement(initialVar);
    int decrementedVar = IDPDecrement(initialVar);
    
    printf("Initial var = %d, its value decremented = %d, and incremented = %d\n",
           initialVar,
           decrementedVar,
           incrementedVar);
}

void IDPPrintValuesWithinRangeTestPerform() {
    unsigned int nTimes = 2;
    int moreThan = 2;
    int lessThan = 9;
    
    char *headerMsg;
    asprintf(&headerMsg, "Print every value, but less than 50, every 3rd is dropped, max output 20 in a row, from the range[%d, %d], %d times", moreThan, lessThan, nTimes);
    IDPPrintTestMessage(headerMsg);
    
    IDPPrintTestMessage("Testing For cycle impelementation");
    IDPPrintNumberNTimesWithinRangeWithForCycle(2, 2, 9);
    
    IDPPrintTestMessage("Testing While cycle impelementation");
    IDPPrintNumberNTimesWithinRangeWithWhileCycle(2, 2, 9);
}

void IDPExpressionExpansionTestPerform() {
    IDPPrintTestMessage("Testing formula expansion");
    IDPPrintResultOfSepararedOperations();
}

void IDPPrePostFixIncrementTestPerform() {
    IDPPrintTestMessage("Testing pre/postfix increment");
    IDPPrintPrePosfixIncrementResult();
}
