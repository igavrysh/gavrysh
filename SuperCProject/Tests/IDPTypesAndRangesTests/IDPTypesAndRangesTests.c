//
//  IDPTypesAndRangesTests.c
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>

#include "IDPTypesAndRanges.h"
#include "IDPTypesAndRangesTests.h"


IDPValueOutput(int, "%d");
IDPValueOutput(float, "%f");
IDPValueOutput(char, "%c");
IDPValueOutput(char_ref, "%s");

void IDPPrintBaseTypeVarsTestsPerform() {
    IDPTypeOutput(int, 10);
    
    IDPTypeOutput(float, 3.141567);
    
    IDPTypeOutput(char, 'H');
    
    IDPTypeOutput(char_ref, "Hellow!!!");
}

IDPGetMaxNumForType(int);

IDPGetMaxNumForType(short);

IDPGetMaxNumForType(long);

IDPGetMaxNumForType(unsigned_int);

void IDPPrintMaxMinForDecimalVarTestsPerform() {
    IDPPrintMaxMinNumForType(int);
    
    IDPPrintMaxMinNumForType(short);
    
    IDPPrintMaxMinNumForType(long);
    
    IDPPrintMaxMinNumForType(unsigned_int);
}




