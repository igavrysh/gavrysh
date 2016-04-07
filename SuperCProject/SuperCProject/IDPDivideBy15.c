//
//  IDPDivideBy15.c
//  SuperCProject
//
//  Created by Ievgen on 4/6/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>

#include "IDPDivideBy15.h"

int GetResStateFromDivByThreeAndFiveForTheNumber(int number) {
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