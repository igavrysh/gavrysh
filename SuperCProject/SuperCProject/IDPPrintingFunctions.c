//
//  IDPPrintingFunctions.c
//  SuperCProject
//
//  Created by Student 104 on 4/4/16.
//  Copyright (c) 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>
#include <string.h>

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

void IDPPrintTestMessage(char *msg) {
    printf("--- %s ---\n", msg);
}

void IDPPrintNullTerminatedString(char *str) {
    unsigned long size = strlen(str);
    IDPPrintNoneNullTerminatedStringWithSize(str, size);
    
}

void IDPPrintNoneNullTerminatedStringWithSize(char *str, unsigned long size) {
    for(int i = 0; i < size; i++) {
        printf("%c", str[i]);
    }
    
    printf("\n");
}