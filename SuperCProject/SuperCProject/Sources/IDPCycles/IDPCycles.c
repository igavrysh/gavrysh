//
//  IDPCycles.c
//  SuperCProject
//
//  Created by Ievgen on 4/10/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

#include "IDPCycles.h"

void IDPPrintNumberNTimes(int value, unsigned nTimes) {
    for (int i = 0; i < nTimes; i++) {
        if (i + 1 == 20) {
            break;
        }
        printf("%d ", value);
    }
    
    printf("\n");
}

bool IDPCyclesIsReturnWithValue(int value) {
    if (value == 50) {
        return true;
    }
    
    return false;
}

bool IDPCyclesIsContinueWithCurrentValueAndRangeStart(int value, int moreThan) {
    if ((value - moreThan + 1) % 3 == 0) {
        return true;
    }
    
    return false;
}

void IDPPrintNumberNTimesWithinRangeWithForCycle(unsigned int nTimes, int moreThan, int lessThan) {
    for (int value = moreThan; value <= lessThan; value++) {
        if (IDPCyclesIsReturnWithValue(value)) {
            return;
        }
        
        if (IDPCyclesIsContinueWithCurrentValueAndRangeStart(value, moreThan)) {
            continue;
        }
        
        IDPPrintNumberNTimes(value, nTimes);
    }
}

void IDPPrintNumberNTimesWithinRangeWithWhileCycle(unsigned int nTimes, int moreThan, int lessThan) {
    int value = moreThan;
    while (value <= lessThan) {
        if (IDPCyclesIsReturnWithValue(value)) {
            return;
        }
        
        if (IDPCyclesIsContinueWithCurrentValueAndRangeStart(value, moreThan)) {
            value++;
            continue;
        }
        
        IDPPrintNumberNTimes(value, nTimes);
        
        value++;
    }
}
