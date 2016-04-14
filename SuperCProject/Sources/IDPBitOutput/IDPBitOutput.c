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
void IDPPrintByteWithValueAndType(char *byteAddress, IDPProcessorType procType);

static
void IDPReversedByteWithValue(char *byteAddress);

#pragma mark -
#pragma mark Public Impl

void IDPPrintBitsWithValueSizeAndType(void *value, size_t size, IDPProcessorType procType) {
    
    char *valueAddress = (char *)value;
    
    printf("{");

    if (procType == IDPProcessorTypeBigEndian) {
        for (size_t pos = size; pos >= 1; pos--) {
            IDPPrintByteWithValueAndType(&valueAddress[pos-1], procType);
        
            if (pos != 1) {
                printf(",");
            }
        }
    }
    
    if (procType == IDPProcessorTypeLittleEndian) {
        for (size_t pos = 0; pos < size; pos++) {
            IDPPrintByteWithValueAndType(&valueAddress[pos], procType);
            
            if (pos != size-1) {
                printf(",");
            }
        }
    }
    
    printf("}\n");
}

void IDPReversedValueWithSizeAndFlag(void *value, size_t size, IDPTransposeFlag changeFlag) {
    if (changeFlag != IDPTransposeFlagTranspose) {
        return;
    }
    
    char *valueByte = (char *)value;
    
    for (size_t i = 0; i < size / 2; i++) {
        char tmp = valueByte[i];
        valueByte[i] = valueByte[size - 1 - i];
        valueByte[size - 1 - i] = tmp;
        
        IDPReversedByteWithValue(&valueByte[i]);
        IDPReversedByteWithValue(&valueByte[size - 1 - i]);
    }
}

#pragma mark - 
#pragma mark Private Impl

void IDPPrintByteWithValueAndType(char *byteAddress, IDPProcessorType procType) {
    uint8_t var = *byteAddress;
    
    if (procType == IDPProcessorTypeBigEndian) {
        for (uint8_t i = kIDPBitCount; i > 0; i--) {
            uint8_t shiftedVar = var >> (i - 1);
            
            printf("%d", shiftedVar & 1);
        }
    }
    
    if (procType == IDPProcessorTypeLittleEndian) {
        for (uint8_t i = 0; i < kIDPBitCount; i++) {
            uint8_t shiftedVar = var >> i;
            
            printf("%d", shiftedVar & 1);
        }
    }
}

void IDPReversedByteWithValue(char *byteAddress) {
    uint8_t var = *byteAddress;
    uint8_t newVar = 0;
    
    for (int i = 1; i <= kIDPBitCount; i++) {
        uint8_t shiftedByteForDataBit = var & (((uint8_t)1UL) << (i-1));
        
        shiftedByteForDataBit <<= (kIDPBitCount-i);
        shiftedByteForDataBit >>= (kIDPBitCount-1);
        shiftedByteForDataBit <<= (kIDPBitCount-i);
        
        newVar |= shiftedByteForDataBit;
    }
    
    *byteAddress = newVar;
}
