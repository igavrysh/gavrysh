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

#include "IDPApplication.h"
#include "IDPPrintingFunctions.h"
#include "IDPBranchingAndStates.h"
#include "IDPTypesAndRanges.h"
#include "IDPPrintReversed.h"
#include "IDPBasicMathOperations.h"
#include "IDPCycles.h"

#include "IDPBranchingAndStatesTests.h"
#include "IDPTypesAndRangesTests.h"
#include "IDPStructuresTests.h"
#include "IDPBitOutputTests.h"

void IDPRunApplication() {
    
    /*
    performTest(IDPMamaPapaAssignmentTestsPerform);
    
    performTest(IDPPrintBaseTypeVarsTestsPerform);
    
    performTest(IDPPrintMaxMinForDecimalVarTestsPerform);
    
    performTest(IDPStartUpStructureSizeofTest);
    
    performTest(IDPStartUpStructureOffsetofTest);
    */
    
    performTest(IDPBitOutputTests);
    
    performTest(IDPBitTransposeTests);
}

