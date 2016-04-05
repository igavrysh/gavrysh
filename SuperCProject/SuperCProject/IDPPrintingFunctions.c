//
//  IDPPrintingFunctions.c
//  SuperCProject
//
//  Created by Student 104 on 4/4/16.
//  Copyright (c) 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>

#include "IDPPrintingFunctions.h"

void IDPPrintHellowWorld() {
    printf("Hello worlf\n");
}

void IDPPrintTest(const char *text) {
    printf("HELLO WORLD! %s\n", text);
}

void ICPrintNewLine() {
    printf("\n");
}

void ICPrintNewLineWithCount(unsigned int count) {
    for (int i = 0; i < count; i++) {
        ICPrintNewLine();
    }
}

void ICPrintGreatingToMama() {
    printf("Hello, Mama!");
}

void ICPrintGreatingToPapa() {
    ICPrintNewLine();
    printf("Hello, Papa!");
}
