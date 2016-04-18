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

#define IDPPerformTest(testName) \
    printf("--- " #testName " started...\n"); \
    testName(); \
    printf("--- ..." #testName " finished\n");

extern
void IDPPrintTestMessage(char *msg);

extern
void IDPPrintTest(const char *text);

extern
void ICPrintNewLine();

extern
void ICPrintNewLineWithCount(unsigned int count);

extern
void ICPrintGreetingToMama();

extern
void ICPrintGreetingToPapa();

extern
void IDPPrintNullTerminatedString(char *str);

extern
void IDPPrintNonNullTerminatedStringWithSize(char *str, unsigned long size);

#endif /* defined(__SuperCProject__IDPPrintingFunctions__) */
