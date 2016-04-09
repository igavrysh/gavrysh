//
//  IDPBasicMathOperations.c
//  SuperCProject
//
//  Created by Ievgen on 4/9/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>
#include <limits.h>

#include "IDPBasicMathOperations.h"

int IDPIncrement(int var) {
    return var + 1;
}

int IDPDecrement(int var) {
    return var - 1;
}

void IDPPrintCastingOperationResults() {
    int intVar = 10;
    float floatVar = 3.3f;
    int secondIntVar = 3;
    int shortVar = 2;
    
    int smallTypeVar = 13;
    unsigned long bigTypeVar = ULONG_MAX-12321;
    smallTypeVar = bigTypeVar;
    
    printf("Integer %d over float %f, the result is %f\n", intVar, floatVar, intVar / floatVar);
    printf("Integer %d multiplied by float %f, the result is %f\n", intVar, floatVar, intVar * floatVar);
    printf("Integer %d over integer %d, the result is %d\n", intVar, secondIntVar, intVar / secondIntVar);
    printf("Integer %d mod %d, the result is %d\n", intVar, secondIntVar, intVar % secondIntVar);
    printf("Integer %d plus short %d, the result is %d\n", intVar, shortVar, intVar + shortVar);
    printf("When assigning integer to the unsigned long var = %lu, result will be var = %d\n", bigTypeVar, smallTypeVar);
}

void IDPPrintResultOfSepararedOperations() {
    double doubleResult = 3.0;
    doubleResult = (int)(doubleResult * doubleResult / 4) % 7 + 4.0 * doubleResult - 1.5 + 'A';
    double replInitialDoubleResult = 3.0;
    double replDoubleRes = 3.0;
    replDoubleRes *= replInitialDoubleResult;
    replDoubleRes /= 4;
    replDoubleRes = (int)replDoubleRes % 7;
    double secondPartOfExpression = 4.0;
    secondPartOfExpression *= replInitialDoubleResult;
    replDoubleRes += secondPartOfExpression;
    replDoubleRes -= 1.5;
    replDoubleRes += 'A';
    printf("Result of initial expression is %f\n", doubleResult);
    printf("Result of expanded expression is %f\n", replDoubleRes);
}

void IDPrintPrePosfixIncrementResult() {
    int initialNum = 777;
    printf("Initial number = %d, prefix increment result = %d, postfix increment result = %d\n", initialNum, ++initialNum, initialNum++);
    
    initialNum = 999;
    printf("Initial number = %d, prefix increment result = %d\n", initialNum, ++initialNum);
    
    initialNum = 999;
    printf("Initial number = %d, postfix increment result = %d\n", initialNum, initialNum++);
}