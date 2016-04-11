//
//  IDPPrintRange.h
//  SuperCProject
//
//  Created by Ievgen on 4/7/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#ifndef IDPTypesAndRanges_h
#define IDPTypesAndRanges_h

#define char_ref char*
#define unsigned_int unsigned int

#define IDPValueOutput(type, specifier) \
    void output_##type(type value) { \
        printf(#type " variable = " #specifier "\n", value); \
    }\

// How to remove type below - make type inference here. Is it possible?
#define IDPTypeOutput(type, value) \
    output_##type(value); \


#define BITS_PER_BYTE 8

#define IDPGetMaxNumForType(type) \
    type get_max_num_for_##type() { \
        return (type)((1UL << (sizeof(type) * BITS_PER_BYTE - 1)) - 1); \
    } \

#define IDPPrintMaxMinNumForType(type) \
    do { \
        type num_max = get_max_num_for_##type(); \
        printf("Maximum value of %s: %llu\n", #type, (unsigned long long)num_max); \
        printf("Minimum value of %s: %ld\n", #type, (long)(-num_max - 1)); \
    } while(0); \


void IDPPrintMostCommonTypes();

#endif /* IDPTypesAndRanges_h */
