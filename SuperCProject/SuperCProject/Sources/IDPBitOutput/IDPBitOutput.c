//
//  IDPBitOutput.c
//  SuperCProject
//
//  Created by Student 104 on 4/11/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPBitOutput.h"

#include <stdio.h>

static const uint8_t kIDPBitCount = 8;

void IDPPrintBitsForValueWithSize(void *value, size_t size) {
    
    char *valueAddress = (char *)value;
    
    printf("{");
    for (int pos = size - 1; pos >= 0; pos--) {
        IDPPrintByteForValue(&valueAddress[pos]);
        
        pos != 0 ? printf(",") : printf("}\n");
    }
}

void IDPPrintByteForValue(char *byteAddress) {
    uint8_t var = *byteAddress;
    for (int i = kIDPBitCount; i > 0; i--) {
        uint8_t shiftedVar = var >> (i - 1);
        
        printf("%d", shiftedVar & 1);
    }
}