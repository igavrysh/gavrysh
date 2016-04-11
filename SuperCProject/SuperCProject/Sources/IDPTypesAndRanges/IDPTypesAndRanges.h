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

#define IDPValueOutput(type, specifier) \
    void output_##type(type value) { \
        printf(#type " variable = " #specifier "\n", value); \
    }\

// How to remove type below - make type inference here. Is it possible?
#define IDPTypeOutput(type, value) \
    output_##type(value); \


int IDPPrintRangeForType(char *type);

void IDPPrintMostCommonTypes();

#endif /* IDPTypesAndRanges_h */
