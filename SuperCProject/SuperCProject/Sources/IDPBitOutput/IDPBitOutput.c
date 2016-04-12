//
//  IDPBitOutput.c
//  SuperCProject
//
//  Created by Student 104 on 4/11/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>

#include "IDPBitOutput.h"

#define BIG_ENDIAN_PROC 1
//#define LITTLE_ENDIAN_PROC 1

static const uint8_t kIDPBitCount = 8;

void IDPPrintBitsForValueWithSize(void *value, size_t size) {
    
    char *valueAddress = (char *)value;
    
    printf("{");

#ifdef BIG_ENDIAN_PROC
    
    for (size_t pos = size; pos >= 1; pos--) {
        IDPPrintByteForValue(&valueAddress[pos-1]);
        
        printf(",");
    }
    printf("}\n");
    
#endif /* BIG_ENDIAN_PROC */

#ifdef LITTLE_ENDIAN_PROC
    
    for (size_t pos = 0; pos < size; pos++) {
        IDPPrintByteForValue(&valueAddress[pos]);
        
        printf(",");
    }
    printf("}\n");
    
#endif /* LITTLE_ENDIAN_PROC */
    
}

void IDPPrintByteForValue(char *byteAddress) {
    uint8_t var = *byteAddress;
    
#ifdef BIG_ENDIAN_PROC
    
    for (uint8_t i = kIDPBitCount; i > 0; i--) {
        uint8_t shiftedVar = var >> (i - 1);
        
        printf("%d", shiftedVar & 1);
    }
    
#endif /* BIG_ENDIAN_PROC */
    
#ifdef LITTLE_ENDIAN_PROC
    
    for (uint8_t i = 0; i < kIDPBitCount; i++) {
        uint8_t shiftedVar = var >> i;
        
        printf("%d", shiftedVar & 1);
    }
    
#endif /* LITTLE_ENDIAN_PROC */
}

void IDPTransposedValueWithSizeAndFlag(void *value, size_t size, IDPTransposeFlag changeFlag) {
    if (changeFlag == IDPTransposeFlagDoNothing) {
        return;
    }
    
    char *valueAddress = (char *)value;
    
    for (size_t i = 0; i < size / 2; i++) {
        char tmp = valueAddress[i];
        valueAddress[i] = valueAddress[size - 1 - i];
        valueAddress[size - 1 - i] = tmp;
        
        IDPTransposeByteForValue(&valueAddress[i]);
        IDPTransposeByteForValue(&valueAddress[size - 1 - i]);
    }
    
}

void IDPTransposedByteForValue(char *byteAddress) {
    uint8_t var = *byteAddress;
    for (uint8_t i = kIDPBitCount; i > 0; i--) {
        uint8_t shiftedVar = var >> (i - 1);
        
        printf("%d", shiftedVar & 1);
    }
}