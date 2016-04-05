//
//  IDPPrintingFunctions.c
//  SuperCProject
//
//  Created by Student 104 on 4/4/16.
//  Copyright (c) 2016 1milliondollarsstartup. All rights reserved.
//

#include "IDPPrintingFunctions.h"

void IDPPrint(){
    printf("Hello worlf\n");
}

void IDPPrintTest(const char *text){
    printf("HELLO WORLD! %s\n", text);
}

void ICPrintNewLine(){
    printf("\n");
}

void ICPrintNewLineWithCount(unsigned int count){
    for (int i = 0; i < count; i++) {
        ICPrintNewLine();
    }
}

void ICPrint(){
    printf("Hello, Mama!");
}

void ICParents(){
    ICPrint();
    printf("Hello, Papa!");
}
