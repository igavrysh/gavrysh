//
//  IDPDivideBy15.c
//  SuperCProject
//
//  Created by Ievgen on 4/6/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>

#include "IDPDivideBy15.h"

char* IDPGetStringForBoolValue(bool boolValue) {
    char *resultStringForBool = malloc(sizeof(char) * 10);
    if (boolValue) {
        strcpy(resultStringForBool, "true\0");
    } else {
        strcpy(resultStringForBool, "false\0");
    }
    return resultStringForBool;
    
    /*
    if (boolValue) {
        return "true";
    }
    return "false";
    */
}
/*
char* IDPSimpleGetStringForBoolValue(bool boolValue){
    char result[5];
    if (boolValue) {
        result = "true";
        return result;
    }
    
    result = "false";
    return result;
}*/

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
    IDPDeputatStateThief,
    IDPDeputatStateHonest,
    IDPDeputatStateAngel,
    IDPDeputatStateDead
} IDPDeputatState;

void IDPPrintDeputatState(IDPDeputatState state) {
    switch (state) {
        case IDPDeputatStateThief:
            puts("Deputat is a thief!");
            break;
            
        case IDPDeputatStateHonest:
            puts("This is a honest deputat!");
            break;
            
        case IDPDeputatStateAngel:
            puts("OMG! He's an angel");
            break;
        
        case IDPDeputatStateDead:
            puts("Sorry, deputat is dead");
            break;
            
        default:
            puts("Deputat is dead");
            break;
    }
}

void IDPPrintDeputatStateForSalaryAndIncome(float salary, float income) {
    IDPDeputatState state = (income == salary * 1000 * 1000) ? IDPDeputatStateThief :
        (income == salary * 120) ? IDPDeputatStateHonest :
            (income == salary * 12) ? IDPDeputatStateAngel :
                IDPDeputatStateDead;
    
    IDPPrintDeputatState(state);
}



int IDPGetResStateFromDivByThreeAndFiveForTheNumber(int number) {
    char state[10];
    int stateNum = 0;
    if (0 == number % 3) {
        strcpy(state, "mama");
        stateNum = 1;
    }
    if (0 == number % 5) {
        strcat(state, "papa");
        stateNum += 2;
    }
    strcat(state, "\n");
    
    if (0 != stateNum) {
        printf("state is %s", state);
    }

    return stateNum;
}
