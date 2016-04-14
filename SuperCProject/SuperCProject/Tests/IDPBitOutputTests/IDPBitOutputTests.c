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

void IDPBitTransposeTests() {
    int t = 3453245;
    
    printf("Big Endian for %d: \n", t);
    IDPPrintBitsWithValueSizeAndType(&t, sizeof(t), IDPProcessorTypeBigEndian);
    
    IDPTransposedValueWithSizeAndFlag(&t, sizeof(t), IDPTransposeFlagTranspose);
    
    printf("Transposed Big Endian for %d: \n", t);
    IDPPrintBitsWithValueSizeAndType(&t, sizeof(t), IDPProcessorTypeBigEndian);
}


void IDPBitOutputTests() {
    long valueMax = LONG_MAX;
    printf("Big Endian for %ld: \t", valueMax);
    IDPPrintBitsWithValueSizeAndType(&valueMax, sizeof(valueMax), IDPProcessorTypeBigEndian);
    printf("Little Endian for %ld:\t", valueMax);
    IDPPrintBitsWithValueSizeAndType(&valueMax, sizeof(valueMax), IDPProcessorTypeLittleEndian);
    
    long valueMin = LONG_MAX + 1;
    printf("Big Endian for %ld:\t", valueMin);
    IDPPrintBitsWithValueSizeAndType(&valueMin, sizeof(valueMin), IDPProcessorTypeBigEndian);
    printf("Little Endian for %ld:\t", valueMin);
    IDPPrintBitsWithValueSizeAndType(&valueMin, sizeof(valueMin), IDPProcessorTypeLittleEndian);
    
    long valueOne = 1;
    printf("Big Endian for %ld:\t", valueOne);
    IDPPrintBitsWithValueSizeAndType(&valueOne, sizeof(valueOne), IDPProcessorTypeBigEndian);
    printf("Little Endian for %ld:\t", valueOne);
    IDPPrintBitsWithValueSizeAndType(&valueOne, sizeof(valueOne), IDPProcessorTypeLittleEndian);
    
    char charVar = 'A';
    printf("Big Endian for %c:\t", charVar);
    IDPPrintBitsWithValueSizeAndType(&charVar, sizeof(charVar), IDPProcessorTypeBigEndian);
    printf("Little Endian for %c:\t", charVar);
    IDPPrintBitsWithValueSizeAndType(&charVar, sizeof(charVar), IDPProcessorTypeLittleEndian);
}