//
//  IDPStructuresTest.c
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>
#include <stddef.h>

#include "IDPStructures.h"
#include "IDPStructuresTests.h"

void IDPStartUpStructureSizeofTest() {
    #define IDPPrintStructFieldsSizeof(value) \
        printf(#value " data size %lu\n", sizeof(value))
    
    IDPStartUp myStartUp;
    
    printf("IDPStartUp sizeof:\n");
    
    IDPPrintStructFieldsSizeof(myStartUp);
    IDPPrintStructFieldsSizeof(IDPStartUp);
    IDPPrintStructFieldsSizeof(myStartUp.isAngelInvestments);
    IDPPrintStructFieldsSizeof(myStartUp.startUpName);
    IDPPrintStructFieldsSizeof(myStartUp.isVentureFondInverstments);
    IDPPrintStructFieldsSizeof(myStartUp.revenueEarned);
    IDPPrintStructFieldsSizeof(myStartUp.isGovernmetnInverstments);
    IDPPrintStructFieldsSizeof(myStartUp.profitEarned);
    IDPPrintStructFieldsSizeof(myStartUp.isMultipleFounders);
    IDPPrintStructFieldsSizeof(myStartUp.usersCovered);
    IDPPrintStructFieldsSizeof(myStartUp.isFounderMajorStakeholder);
    IDPPrintStructFieldsSizeof(myStartUp.suppliersNum);
    IDPPrintStructFieldsSizeof(myStartUp.isCreditBorrowed);
    IDPPrintStructFieldsSizeof(myStartUp.employeesNum);
    
    IDPStartUpCompressed myStartUpCompressed;
    
    IDPPrintStructFieldsSizeof(myStartUpCompressed);
    IDPPrintStructFieldsSizeof(IDPStartUpCompressed);
    
    #undef IDPPrintStructFieldsSizeof
}

void IDPStartUpStructureOffsetofTest() {
    #define IDPPrintStructFieldsOffsetof(data, value) \
        printf(#value " offsetof %lu\n", offsetof(data, value))
    
    printf("IDPStartUp offsetof:\n");
    
    IDPPrintStructFieldsOffsetof(IDPStartUp, isAngelInvestments);
    IDPPrintStructFieldsOffsetof(IDPStartUp, startUpName);
    IDPPrintStructFieldsOffsetof(IDPStartUp, isVentureFondInverstments);
    IDPPrintStructFieldsOffsetof(IDPStartUp, revenueEarned);
    IDPPrintStructFieldsOffsetof(IDPStartUp, isGovernmetnInverstments);
    IDPPrintStructFieldsOffsetof(IDPStartUp, profitEarned);
    IDPPrintStructFieldsOffsetof(IDPStartUp, isMultipleFounders);
    IDPPrintStructFieldsOffsetof(IDPStartUp, usersCovered);
    IDPPrintStructFieldsOffsetof(IDPStartUp, isFounderMajorStakeholder);
    IDPPrintStructFieldsOffsetof(IDPStartUp, suppliersNum);
    IDPPrintStructFieldsOffsetof(IDPStartUp, isCreditBorrowed);
    IDPPrintStructFieldsOffsetof(IDPStartUp, employeesNum);
    
    #undef IDPPrintStructFieldsOffsetof
}
