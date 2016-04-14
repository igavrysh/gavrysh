//
//  IDPBranchinAndStatesTests.c
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>

#include "IDPBranchingAndStatesTests.h"
#include "IDPBranchingAndStates.h"

#pragma mark - Public Implementation

void IDPMamaPapaAssignmentTestsPerform() {
    puts("Expected result mama, actual result is ");
    IDPPrintStatePrintWithNumber(3);
    printf("\n");
    
    puts("Expected result papa, actual result is ");
    IDPPrintStatePrintWithNumber(5);
    printf("\n");
    
    puts("Expected result mamapapa, actual result is ");
    IDPPrintStatePrintWithNumber(15);
    printf("\n");
    
    puts("Iterative get state calling");
    for (int counter = 0; counter <= 1000; counter++) {
        printf("Iteration #%d :", counter + 1);
        IDPPrintStatePrintWithNumber(counter);
        printf("\n");
    }
}

