//
//  main.c
//  SuperCProject
//
//  Created by Student 104 on 4/4/16.
//  Copyright (c) 2016 1milliondollarsstartup. All rights reserved.
//

//???#include <Foundation/Foundation.h>

#include <stdbool.h>

#include "IDPPrintingFunctions.h"
#include "IDPGenericDefineList.h"
#include "IDPPrintRange.h"

void ExecuteFirstAssignmentLines()
{
    ICPrintNewLine();
    IDPPrintTest("$1mln dollars start up");
    
    ICPrintGreatingToMama();
    ICPrintNewLineWithCount(2);
    
    ICPrintGreatingToPapa();
    ICPrintNewLineWithCount(3);
}

void ExecuteSecondAssignmentLines()
{
    // Print "1234567890" and after that print "0987654321"
    char *inputString = "1234567890";
    char *reversedString = IDPGetReversedStringForString(inputString);
    printf("Ex1. Reversed string for %s is %s\n", inputString, reversedString);
    
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
    // ---
    
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
    
    
    
    // If input number is divided by by 3 print papa, if divided by 5 print mama, if it is divided by 15 print papamama
    int stateNum = GetResStateFromDivByThreeAndFiveForTheNumber(6);
    printf("Ex3. state number is %d\n", stateNum);
}

int main(int argc, const char * argv[])
{
    ExecuteSecondAssignmentLines();
}
