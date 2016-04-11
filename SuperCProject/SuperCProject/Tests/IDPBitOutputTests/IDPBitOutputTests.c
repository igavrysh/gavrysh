//
//  IDPBitOutputTests.c
//  SuperCProject
//
//  Created by Student 104 on 4/11/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <limits.h>

#include "IDPBitOutput.h"
#include "IDPBitOutputTests.h"

void IDPBitOutputTests() {
    long valueMax = LONG_MAX;
    IDPPrintBitsForValueWithSize(&valueMax, sizeof(valueMax));
    
    long valueMin = LONG_MAX + 1;
    IDPPrintBitsForValueWithSize(&valueMin, sizeof(valueMin));
    
    long valueZero = 0;
    IDPPrintBitsForValueWithSize(&valueZero, sizeof(valueZero));
    
    char charVar = 'A';
    IDPPrintBitsForValueWithSize(&charVar, sizeof(charVar));
}