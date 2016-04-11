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
    
    printf("_isAngelInvestments data size %lu\n", sizeof(myStartUp._isAngelInvestments));
    printf("_startUpName data size %lu\n", sizeof(myStartUp._startUpName));
    printf("_isVentureFondInverstments data size %lu\n", sizeof(myStartUp._isVentureFondInverstments));
    printf("_revenueEarned data size %lu\n", sizeof(myStartUp._revenueEarned));
    printf("_isGovernmetnInverstments data size %lu\n", sizeof(myStartUp._isGovernmetnInverstments));
    printf("_profitEarned data size %lu\n", sizeof(myStartUp._profitEarned));
    printf("_isMultipleFounders data size %lu\n", sizeof(myStartUp._isMultipleFounders));
    printf("_usersCovered data size %lu\n", sizeof(myStartUp._usersCovered));
    printf("_isFounderMajorStakeholder data size %lu\n", sizeof(myStartUp._isFounderMajorStakeholder));
    printf("_suppliersNum data size %lu\n", sizeof(myStartUp._suppliersNum));
    printf("_isCreditBorrowed data size %lu\n", sizeof(myStartUp._isCreditBorrowed));
    printf("_employeesNum data size %lu\n", sizeof(myStartUp._employeesNum));
    
    IDPStartUpCompressed myStartUpCompressed;
    
    printf("My startup compressed struct size %lu\n", sizeof(myStartUpCompressed));
    printf("Struct IDPStartUp size %lu\n", sizeof(IDPStartUpCompressed));
}

void IDPStartUpStructureOffsetofTest() {
    printf("IDPStartUp offsetof\n");
    printf("_isAngelInvestments %lu\n", offsetof(IDPStartUp, _isAngelInvestments));
    printf("_startUpName %lu\n", offsetof(IDPStartUp, _startUpName));
    printf("_isVentureFondInverstments %lu\n", offsetof(IDPStartUp, _isVentureFondInverstments));
    printf("_revenueEarned %lu\n", offsetof(IDPStartUp, _revenueEarned));
    printf("_isGovernmetnInverstments %lu", offsetof(IDPStartUp, _isGovernmetnInverstments));
    printf("_profitEarned %lu\n", offsetof(IDPStartUp, _profitEarned));
    printf("_isMultipleFounders %lu\n", offsetof(IDPStartUp, _isMultipleFounders));
    printf("_usersCovered %lu\n", offsetof(IDPStartUp, _usersCovered));
    printf("_isFounderMajorStakeholder %lu\n", offsetof(IDPStartUp, _isFounderMajorStakeholder));
    printf("_suppliersNum %lu\n", offsetof(IDPStartUp, _suppliersNum));
    printf("_isCreditBorrowed %lu\n", offsetof(IDPStartUp, _isCreditBorrowed));
    printf("_employeesNum %lu\n", offsetof(IDPStartUp, _employeesNum));
}
