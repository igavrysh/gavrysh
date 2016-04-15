//
//  IDPBitOutput.c
//  SuperCProject
//
//  Created by Student 104 on 4/11/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>

#include "IDPBitOutput.h"

#pragma mark -
#pragma mark Private Decl

static
const uint8_t kIDPBitCount = 8;

static
void IDPPrintByte(uint8_t byte);

#pragma mark -
#pragma mark Public Impl

void IDPPrintBits(void *value, size_t size) {
    IDPPrintBitsWithFlag(value, size, IDPGetEndianess());
}

void IDPPrintBitsWithFlag(void *value, size_t size, IDPEndianness procType) {
    uint8_t *valueAddress = (uint8_t *)value;
    
    printf("{");

    for (size_t i = 0; i < size; i++) {
        procType == IDPEndiannessBigEndian ? IDPPrintByte(valueAddress[size - i - 1]) : IDPPrintByte(valueAddress[i]);
        
        if (i != size - 1) {
            printf(",");
        }
    }
    
    printf("}\n");
}

void IDPReverseBitsWithFlag(void *value, size_t size, IDPReverseFlag changeFlag) {
    if (changeFlag != IDPReverseFlagReverse) {
        return;
    }
    
    uint8_t *valueByte = (uint8_t *)value;
    
    for (size_t i = 0; i < size / 2; i++) {
        uint8_t tmp = valueByte[i];
        valueByte[i] = valueByte[size - 1 - i];
        valueByte[size - 1 - i] = tmp;
    }
}

void IDPPrintEndianness() {
    if (IDPGetEndianess() == IDPEndiannessBigEndian) {
        printf("Big Endian ");
    } else if (IDPGetEndianess() == IDPEndiannessLittleEndian) {
        printf("Little Endian ");
    }
}

#pragma mark - 
#pragma mark Private Impl

IDPEndianness IDPGetEndianess() {
    uint16_t test = 1UL;
    return ((uint8_t *)&test)[0] == 1 ? IDPEndiannessBigEndian : IDPEndiannessLittleEndian;
}

void IDPPrintByte(uint8_t byte) {
    for (uint8_t i = kIDPBitCount; i > 0; i--) {
        uint8_t shiftedVar = byte >> (i - 1);
        
        printf("%d", shiftedVar & 1);
    }
}
