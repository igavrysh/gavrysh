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
    IDPPrintBitsWithFlag(value, size, IDPGetEndianness());
}

void IDPPrintBitsWithFlag(void *value, size_t size, IDPEndianness procType) {
    uint8_t *valueAddress = (uint8_t *)value;
    
    printf("{");

    for (size_t i = 0, j = 0; i < size; i++, j = size - i - 1) {
        size_t pos = procType == IDPEndiannessBigEndian ? j : i;
        IDPPrintByte(valueAddress[pos]);
        
        if (i != size - 1) {
            printf(",");
        }
    }
    
    printf("}\n");
}

void IDPReverseBitsWithFlag(void *value, size_t size, IDPReverseFlag flag) {
    if (flag != IDPReverseFlagReverse) {
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
    if (IDPGetEndianness() == IDPEndiannessBigEndian) {
        printf("Big Endian ");
    } else if (IDPGetEndianness() == IDPEndiannessLittleEndian) {
        printf("Little Endian ");
    }
}

#pragma mark - 
#pragma mark Private Impl

IDPEndianness IDPGetEndianness() {
    uint16_t indicator = 1UL;
    return ((uint8_t *)&indicator)[0] == 1 ? IDPEndiannessBigEndian : IDPEndiannessLittleEndian;
}

void IDPPrintByte(uint8_t byte) {
    for (uint8_t i = 0; i < kIDPBitCount; i++) {
        uint8_t shiftedVar = byte >> (kIDPBitCount - i - 1);
        
        printf("%d", shiftedVar & 1U);
    }
}
