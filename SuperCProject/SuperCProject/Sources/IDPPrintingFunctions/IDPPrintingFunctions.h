//
//  IDPPrintingFunctions.h
//  SuperCProject
//
//  Created by Student 104 on 4/4/16.
//  Copyright (c) 2016 1milliondollarsstartup. All rights reserved.
//

#ifndef __SuperCProject__IDPPrintingFunctions__
#define __SuperCProject__IDPPrintingFunctions__

void IDPPrintHelloWorld();

#define performTest(testName) \
    printf("--- " #testName " started...\n"); \
    testName(); \
    printf("--- " #testName " finished\n");


void IDPPrintTestMessage(char *msg);

void IDPPrintTest(const char *text);

void ICPrintNewLine();

void ICPrintNewLineWithCount(unsigned int count);

void ICPrintGreetingToMama();

void ICPrintGreetingToPapa();

void IDPPrintNullTerminatedString(char *str);

void IDPPrintNoneNullTerminatedStringWithSize(char *str, unsigned long size);

#endif /* defined(__SuperCProject__IDPPrintingFunctions__) */
