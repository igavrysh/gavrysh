//
//  IDPPrintRange.c
//  SuperCProject
//
//  Created by Ievgen on 4/8/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>

#include "IDPPrintRange.h"

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

