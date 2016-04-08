//
//  IDPPrintingFunctions.c
//  SuperCProject
//
//  Created by Student 104 on 4/4/16.
//  Copyright (c) 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>

#include "IDPPrintingFunctions.h"

void IDPPrintHelloWorld() {
    printf("Hello world\n");
}

void IDPPrintTest(const char *text) {
    printf("HELLO WORLD!!!! %s\n", text);
}

void ICPrintNewLine() {
    printf("\n");
}

void ICPrintNewLineWithCount(unsigned int count) {
    for (int i = 0; i < count; i++) {
        ICPrintNewLine();
    }
}

void ICPrintGreetingToMama() {
    printf("Hello, Mama!");
}

void ICPrintGreetingToPapa() {
    ICPrintNewLine();
    printf("Hello, Papa!");
}
