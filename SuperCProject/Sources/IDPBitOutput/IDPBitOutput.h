//
//  IDPBitOutput.h
//  SuperCProject
//
//  Created by Student 104 on 4/11/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef __SuperCProject__IDPBitOutput__
#define __SuperCProject__IDPBitOutput__

#include <stdio.h>

typedef enum {
    IDPEndiannessBigEndian,
    IDPEndiannessLittleEndian
} IDPEndianness;

extern
void IDPPrintBits(void *value, size_t size);

extern
void IDPPrintBitsWithFlag(void *value, size_t size, IDPEndianness endianness);

extern
IDPEndianness IDPGetEndianness();

extern
void IDPPrintEndianness();

typedef enum {
    IDPReverseFlagReverse,
    IDPReverseFlagDoNothing
} IDPReverseFlag;

extern
void IDPReverseBitsWithFlag(void *value, size_t size, IDPReverseFlag flag);

#endif /* defined(__SuperCProject__IDPBitOutput__) */
