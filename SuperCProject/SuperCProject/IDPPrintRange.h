//
//  IDPPrintRange.h
//  SuperCProject
//
//  Created by Ievgen on 4/7/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#ifndef IDPPrintRange_h
#define IDPPrintRange_h

#include <stdio.h>

#define BITS_PER_BYTE 8

#define IDP_PRINT_RANGE(integer_type) do {\
    integer_type num_max = (integer_type)((1UL << (sizeof(integer_type) * BITS_PER_BYTE - 1)) - 1);\
    printf("Maximum value of " #integer_type ": %lu\n", (unsigned long)num_max);\
    printf("Minimum value of " #integer_type ": %ld\n", (long)(-num_max - 1));\
} while (0)

#endif /* IDPPrintRange_h */
