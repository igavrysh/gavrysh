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
    IDPStartUp myStartUp;
    
    printf("My startup struct size %lu\n", sizeof(myStartUp));
    printf("Struct IDPStartUp size %lu\n", sizeof(IDPStartUp));
    
    printf("isAngelInvestments data size %lu\n", sizeof(myStartUp.isAngelInvestments));
    printf("startUpName data size %lu\n", sizeof(myStartUp.startUpName));
    printf("isVentureFondInverstments data size %lu\n", sizeof(myStartUp.isVentureFondInverstments));
    printf("revenueEarned data size %lu\n", sizeof(myStartUp.revenueEarned));
    printf("isGovernmetnInverstments data size %lu\n", sizeof(myStartUp.isGovernmetnInverstments));
    printf("profitEarned data size %lu\n", sizeof(myStartUp.profitEarned));
    printf("isMultipleFounders data size %lu\n", sizeof(myStartUp.isMultipleFounders));
    printf("usersCovered data size %lu\n", sizeof(myStartUp.usersCovered));
    printf("isFounderMajorStakeholder data size %lu\n", sizeof(myStartUp.isFounderMajorStakeholder));
    printf("suppliersNum data size %lu\n", sizeof(myStartUp.suppliersNum));
    printf("isCreditBorrowed data size %lu\n", sizeof(myStartUp.isCreditBorrowed));
    printf("employeesNum data size %lu\n", sizeof(myStartUp.employeesNum));
    
    IDPStartUpCompressed myStartUpCompressed;
    
    printf("My startup compressed struct size %lu\n", sizeof(myStartUpCompressed));
    printf("Struct IDPStartUp size %lu\n", sizeof(IDPStartUpCompressed));
}

void IDPStartUpStructureOffsetofTest() {
    printf("IDPStartUp offsetof\n");
    printf("isAngelInvestments %lu\n", offsetof(IDPStartUp, isAngelInvestments));
    printf("startUpName %lu\n", offsetof(IDPStartUp, startUpName));
    printf("isVentureFondInverstments %lu\n", offsetof(IDPStartUp, isVentureFondInverstments));
    printf("revenueEarned %lu\n", offsetof(IDPStartUp, revenueEarned));
    printf("isGovernmetnInverstments %lu", offsetof(IDPStartUp, isGovernmetnInverstments));
    printf("profitEarned %lu\n", offsetof(IDPStartUp, profitEarned));
    printf("isMultipleFounders %lu\n", offsetof(IDPStartUp, isMultipleFounders));
    printf("usersCovered %lu\n", offsetof(IDPStartUp, usersCovered));
    printf("isFounderMajorStakeholder %lu\n", offsetof(IDPStartUp, isFounderMajorStakeholder));
    printf("suppliersNum %lu\n", offsetof(IDPStartUp, suppliersNum));
    printf("isCreditBorrowed %lu\n", offsetof(IDPStartUp, isCreditBorrowed));
    printf("employeesNum %lu\n", offsetof(IDPStartUp, employeesNum));
}
