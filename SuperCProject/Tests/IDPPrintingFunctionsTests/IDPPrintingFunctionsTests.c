//
//  IDPPrintingFunctionsTests.c
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>

#include "IDPPrintingFunctions.h"
#include "IDPPrintingFunctionsTests.h"

#pragma mark - Public Implementation

void IDPPrintingTestsPerform() {
    IDPPrintTestMessage("Testing console output");
    ICPrintNewLine();
    IDPPrintTest("$1mln dollars start up");
    
    ICPrintGreetingToMama();
    ICPrintNewLineWithCount(2);
    
    ICPrintGreetingToPapa();
    ICPrintNewLineWithCount(3);
}