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

void IDPPrintNumberNTimes(int value, unsigned count) {
    for (int i = 0; i < count; i++) {
        if (i + 1 == 20) {
            break;
        }
        printf("%d ", value);
    }
    
    printf("\n");
}

bool IDPCyclesIsReturnWithValue(int value) {
    return value == 50;
}

bool IDPCyclesIsContinueWithCurrentValueAndRangeStart(int value, int moreThan) {
    return (value - moreThan + 1) % 3 == 0;
}

void IDPPrintNumberNTimesWithinRangeWithForCycle(unsigned int count, int moreThan, int lessThan) {
    for (int value = moreThan; value <= lessThan; value++) {
        if (IDPCyclesIsReturnWithValue(value)) {
            return;
        }
        
        if (IDPCyclesIsContinueWithCurrentValueAndRangeStart(value, moreThan)) {
            continue;
        }
        
        IDPPrintNumberNTimes(value, count);
    }
}

void IDPPrintNumberNTimesWithinRangeWithWhileCycle(unsigned int count, int moreThan, int lessThan) {
    int value = moreThan;
    while (value <= lessThan) {
        if (IDPCyclesIsReturnWithValue(value)) {
            return;
        }
        
        if (IDPCyclesIsContinueWithCurrentValueAndRangeStart(value, moreThan)) {
            value++;
            continue;
        }
        
        IDPPrintNumberNTimes(value, count
                             );
        
        value++;
    }
}
