//
//  IDPTypesAndRangesTests.c
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPTypesAndRanges.h"
#include "IDPTypesAndRangesTests.h"

void IDPTestTypeConversionAndRangeIdentification() {
    IDPPrintRangeForType("char");
    IDPPrintRangeForType("short");
    IDPPrintRangeForType("int");
    IDPPrintRangeForType("long");
    IDPPrintRangeForType("unsigned long");
}