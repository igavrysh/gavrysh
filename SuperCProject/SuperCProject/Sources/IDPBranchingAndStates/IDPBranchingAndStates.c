//
//  IDPDivideBy15.c
//  SuperCProject
//
//  Created by Ievgen on 4/6/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>

#include "IDPBranchingAndStates.h"

char * IDPCreateStringForBoolValue(bool boolValue) {
    char *resultStringForBool = malloc(sizeof(char) * 10);
    if (boolValue) {
        strcpy(resultStringForBool, "true");
    } else {
        strcpy(resultStringForBool, "false");
    }
    
    return resultStringForBool;
}

void IDPPrintMamaPapaStdBranching(int firstNum, int secondNum) {
    if (firstNum > secondNum) {
        printf("papa\n");
    } else {
        printf("mama\n");
    }
}

void IDPPrintMamaPapaTernaryBranching(int firstNum, int secondNum) {
    firstNum > secondNum ? printf("papa\n") : printf("mama\n");
}

typedef enum  {
    IDPDeputyStateThief,
    IDPDeputyStateHonest,
    IDPDeputyStateAngel,
    IDPDeputyStateDead
} IDPDeputyState;

void IDPPrintDeputyState(IDPDeputyState state) {
    switch (state) {
        case IDPDeputyStateThief:
            puts("Deputy is a thief!");
            break;
            
        case IDPDeputyStateHonest:
            puts("This is a honest deputy!");
            break;
            
        case IDPDeputyStateAngel:
            puts("OMG! He's an angel");
            break;
        
        case IDPDeputyStateDead:
            puts("Sorry, deputy is dead");
            break;
            
        default:
            puts("Deputy is dead");
            break;
    }
}

void IDPPrintDeputyStateForSalaryAndIncome(float salary, float income) {
    IDPDeputyState state =
        (income >= salary * 1000 * 1000) ? IDPDeputyStateThief :
            (income >= salary * 120) ? IDPDeputyStateHonest :
                (income >= salary * 12) ? IDPDeputyStateAngel : IDPDeputyStateDead;
    
    IDPPrintDeputyState(state);
}

IDPPrintState IDPDisplayAndGetStateForNumber(int num) {
    
    IDPPrintState state = IDPPrintStateNone;
    
    if (0 == num % 3) {
        printf("mama");
        state |= IDPPrintStateMama;
    }
    
    if (0 == num % 5) {
        printf("papa");
        state |= IDPPrintStatePapa;
    }
    
    printf("\n");
    
    return state;
}

