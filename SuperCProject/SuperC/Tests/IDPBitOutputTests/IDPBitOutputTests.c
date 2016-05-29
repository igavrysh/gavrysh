//
//  IDPBitOutputTests.c
//  SuperCProject
//
//  Created by Student 104 on 4/11/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>
#include <limits.h>

#include "IDPBitOutput.h"
#include "IDPBitOutputTests.h"

void IDPBitReverseTest() {
    int t = 3453245;
    
    IDPPrintEndianness();
    printf(" for %d: \n", t);
    IDPPrintBits(&t, sizeof(t));
    
    IDPReverseBitsWithFlag(&t, sizeof(t), IDPReverseFlagReverse);
    
    printf("Revesed to ");
    IDPPrintEndianness();
    printf(": \n");
    IDPPrintBits(&t, sizeof(t));
}

void IDPBitOutputTest() {
    uint16_t valueMax = UINT16_MAX;
    printf("Big Endian for %hu: \n", valueMax);
    IDPPrintBits(&valueMax, sizeof(valueMax));
    printf("Little Endian:\n");
    IDPPrintBitsWithFlag(&valueMax, sizeof(valueMax), IDPEndiannessLittleEndian);
    
    puts("---------------------");
    
    uint32_t valueOne = 1UL;
    printf("Big Endian for %u:\n", valueOne);
    IDPPrintBits(&valueOne, sizeof(valueOne));
    printf("Little Endian:\n");
    IDPPrintBitsWithFlag(&valueOne, sizeof(valueOne), IDPEndiannessLittleEndian);
    
    puts("---------------------");
    
    long valueMin = LONG_MAX + 1;
    printf("Big Endian for %ld:\n", valueMin);
    IDPPrintBits(&valueMin, sizeof(valueMin));
    printf("Little Endian:\n");
    IDPPrintBitsWithFlag(&valueMin, sizeof(valueMin), IDPEndiannessLittleEndian);
    
    puts("---------------------");
    
    char charVar = 'A';
    printf("Big Endian for %c:\n", charVar);
    IDPPrintBits(&charVar, sizeof(charVar));
    printf("Little Endian:\n");
    IDPPrintBitsWithFlag(&charVar, sizeof(charVar), IDPEndiannessLittleEndian);
}
