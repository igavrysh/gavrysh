//
//  IDPPrintRange.c
//  SuperCProject
//
//  Created by Ievgen on 4/8/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>

#include "IDPTypesAndRanges.h"

#define BITS_PER_BYTE 8

int IDPPrintRangeForType(char *type) {
    return 0;
}
/*
 #define IDP_PRINT_RANGE(integer_type) do {\
 integer_type num_max = (integer_type)((1UL << (sizeof(integer_type) * BITS_PER_BYTE - 1)) - 1);\
 printf("Maximum value of " #integer_type ": %lu\n", (unsigned long)num_max);\
 printf("Minimum value of " #integer_type ": %ld\n", (long)(-num_max - 1));\
 } while (0)*/


void IDPPrintMostCommonTypes() {
    char charVar = 'A';
    short shortVar = -10;
    int iVar = -100;
    long lVar = -12312312l;
    long long dLVar = -43242ll;
    float fVar = -12313.f;
    double dVar = -12312312.123123;
    long double lDVar = -2121321.12l;
    unsigned char uCharVar = 'A';
    unsigned short uShortVar = 'A';
    unsigned int uIVar = 120u;
    unsigned long uLongVar = 1231231231lu;
    unsigned long long uDLVar = 3223423llu;
    printf("char var = %c, short var = %i, int var = %d\n, long var = %ld, long long var = %lld,\n float var = %f, double var = %f, long double var = %Lf, unsigned char = %uc,\n unsigned short = %ud, unsigned int = %ud, unsigned long var = %lu, unsigned long long var = %llu\n",
           charVar,
           shortVar,
           iVar,
           lVar,
           dLVar,
           fVar,
           dVar,
           lDVar,
           uCharVar,
           uShortVar,
           uIVar,
           uLongVar,
           uDLVar);
}
