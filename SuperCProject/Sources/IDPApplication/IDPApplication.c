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
#include "IDPStringTests.h"
#include "IDPArrayTests.h"
#include "IDPLinkedListTests.h"
#include "IDPAutoreleasingStackTests.h"
#include "IDPAutoreleasingPoolTests.h"
#include "IDPHumanTests.h"

void IDPRunApplication() {
    /*
    IDPPerformTest(IDPMamaPapaAssignmentTestPerform);
    
    IDPPerformTest(IDPPrintBaseTypeVarsTestPerform);
    
    IDPPerformTest(IDPPrintMaxMinForDecimalVarTestPerform);
    
    IDPPerformTest(IDPStartUpStructureSizeofTest);
    
    IDPPerformTest(IDPStartUpStructureOffsetofTest);
    */
    
    /*
    IDPPerformTest(IDPStartUpStructureSizeofTest);
    
    IDPPerformTest(IDPStartUpStructureOffsetofTest);
    */ 
    
    //IDPPerformTest(IDPBitOutputTest);
    
    //IDPPerformTest(IDPBitReverseTest);
    
    IDPObjectBehaviorTests();

    IDPStringTestPerform();

    IDPHumanBehaviorTests();
     

    IDPArrayBehaviorTests();

    IDPLinkedListBehaviorTests();

    IDPLinkedListEnumeratorBehaviorTests();


    //IDPAutoreleasingStackBehaviorTests();
    
    //IDPAutoreleasingPoolBehaviorTests();
}

