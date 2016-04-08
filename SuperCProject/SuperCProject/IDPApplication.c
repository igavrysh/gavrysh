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

#include "IDPApplication.h"
#include "IDPPrintingFunctions.h"
#include "IDPBranchingAndStates.h"
#include "IDPPrintRange.h"
#include "IDPPrintReversed.h"

void IDPRunApplication() {
    IDPTestSecondAssignment();
}

void IDPTestFirstAssignment()
{
    ICPrintNewLine();
    IDPPrintTest("$1mln dollars start up");
    
    ICPrintGreetingToMama();
    ICPrintNewLineWithCount(2);
    
    ICPrintGreetingToPapa();
    ICPrintNewLineWithCount(3);
}

void IDPTestStackBasedStringReversal() {
    puts("-- Testing stack-based string reversal");
    char *inputString = "1234567890";
    char *reversedString = IDPGetReversedStringForString(inputString);
    printf("Reversed string for %s is %s\n", inputString, reversedString);
}

void IDPTestBoolToStringConversion() {
    puts("--- Testing bool to string conversion ---");
    char *strForBool = IDPCreateStringForBoolValue(true);
    printf("%s\n", strForBool);
    free(strForBool);
}

void IDPTestBranchingTypes() {
    puts("--- Testing ternary and ordinary branching ---");
    IDPPrintMamaPapaStdBranching(2, 5);
    IDPPrintMamaPapaTernaryBranching(2, 5);
}

void IDPTestStateIdentification() {
    puts("--- Testing State Identification: Deputy task ---");
    IDPPrintDeputyStateForSalaryAndIncome(12.f, 10000000.f);
    puts("--- Testing State Identification: mama, papa, mamapapa task");
    IDPDisplayStateForNumber(6);
}

void IDPTestTypeConversionAndRangeIdentification() {
    puts("--- Testing type conversion and range identification ---");
    // What is the result of the following two lines?
    int intValue = 3;
    double doubleResult = intValue * intValue / 4 % 7 + 4.0 * intValue - 1.5 + 'A';
    // {'A' = 65} -> ( 3 * 3 / 4 % 7 ) + ( 4.0 * 3 ) - 1.5 + 65 ) -> 2 + 12.0 - 1.5 + 65 -> 77.5
    printf("Ex2. Expected result 77.5f, actual result %f\n", doubleResult);
    
    // Signed Range [-X-1; +X]  ->  Unsigned Range with the same size =-> [0; 2^{log2(X+1) + 1} - 1]
    // Test size = 3bits  signed range [-4;3] -> unsigned range [0, 7]
    // 011 = 3
    // 010 = 2
    // 001 = 1
    // 000 = 0
    // 100 = -1
    // 101 = -2
    // 110 = -3
    // 111 = -4
    // ------
    // ------
    
    // Create Variables with all possible types
    IDP_PRINT_RANGE(signed char);
    IDP_PRINT_RANGE(short);
    IDP_PRINT_RANGE(int);
    IDP_PRINT_RANGE(long);
    IDP_PRINT_RANGE(unsigned long);
    char charVar = 'A';
    short shortVar = -10;
    int iVar = -100;
    long lVar = -12312312l;
    long long dLVar = -43242ll;
    float fVar = -12313.f;
    double dVar = -12312312.123123;
    long double lDVar = -2121321.12l;
    unsigned char uCharVar = 'A';
    unsigned short uShortVar = 'A';
    unsigned int uIVar = 120u;
    unsigned long uLongVar = 1231231231lu;
    unsigned long long uDLVar = 3223423llu;
}

void IDPTestSecondAssignment()
{
    IDPTestStackBasedStringReversal();
    
    IDPTestTypeConversionAndRangeIdentification();
    
    IDPTestBoolToStringConversion();
    
    IDPTestBranchingTypes();
    
    IDPTestStateIdentification();
}

