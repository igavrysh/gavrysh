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
        strcpy(resultStringForBool, "true\0");
    } else {
        strcpy(resultStringForBool, "false\0");
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
        (income == salary * 1000 * 1000) ? IDPDeputyStateThief :
            (income == salary * 120) ? IDPDeputyStateHonest :
                (income == salary * 12) ? IDPDeputyStateAngel : IDPDeputyStateDead;
    
    IDPPrintDeputyState(state);
}

typedef enum {
    IDPPrintStateMama,
    IDPPrintStatePapa,
    IDPPrintStateMamaPapa,
    IDPPrintStateNone
} IDPPrintState;

void IDPDisplayPrintState(IDPPrintState state) {
    switch (state) {
        case IDPPrintStateMama:
            puts("mama");
            break;
            
        case IDPPrintStatePapa:
            puts("papa");
            break;
            
        case IDPPrintStateMamaPapa:
            puts("mamapapa");
            break;
            
        default:
            puts("No valid state selected");
            break;
    }
}

void IDPDisplayStateForNumber(int num) {
    IDPPrintState state = (num % 15 == 0) ? IDPPrintStateMamaPapa : (
        (num % 3 == 0) ? IDPPrintStateMama : (
            (num % 5 == 0) ? IDPPrintStatePapa : IDPPrintStateNone));
    
    IDPDisplayPrintState(state);
}
