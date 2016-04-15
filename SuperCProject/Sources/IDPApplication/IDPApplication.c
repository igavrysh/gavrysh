//
//  IDPApplication.c
//  SuperCProject
//
//  Created by Ievgen on 4/8/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "IDPPrintingFunctions.h"
#include "IDPBranchingAndStatesTests.h"
#include "IDPTypesAndRangesTests.h"
#include "IDPStructuresTests.h"
#include "IDPBitOutputTests.h"

void IDPRunApplication() {
    /*
    performTest(IDPMamaPapaAssignmentTestPerform);
    
    performTest(IDPPrintBaseTypeVarsTestPerform);
    
    performTest(IDPPrintMaxMinForDecimalVarTestPerform);
    
    performTest(IDPStartUpStructureSizeofTest);
    
    performTest(IDPStartUpStructureOffsetofTest);
    */
     
    performTest(IDPBitOutputTest);
    
    performTest(IDPBitReverseTest);
}

