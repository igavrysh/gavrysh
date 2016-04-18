//
//  IDPStructures.h
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPStructures_h
#define IDPStructures_h

#include <stdbool.h>

typedef struct IDPStartUp IDPStartUp;

struct IDPStartUp {
    bool isAngelInvestments;
    char *startUpName;
    bool isVentureFondInverstments;
    float revenueEarned;
    bool isGovernmetnInverstments;
    double profitEarned;
    bool isMultipleFounders;
    long long usersCovered;
    bool isFounderMajorStakeholder;
    int suppliersNum;
    bool isCreditBorrowed;
    short employeesNum;
};

typedef struct IDPStartUpCompressed IDPStartUpCompressed;

struct IDPStartUpCompressed {
    char *startUpName;
    //
    float revenueEarned;
    int suppliersNum;
    //
    double profitEarned;
    //
    long long usersCovered;
    //
    short employeesNum;
    bool isAngelInvestments;
    bool isVentureFondInverstments;
    bool isGovernmetnInverstments;
    bool isMultipleFounders;
    bool isFounderMajorStakeholder;
    bool isCreditBorrowed;
};

typedef struct IDPStartUpUnionized IDPStartUpUnionized;

struct IDPStartUpUnionized {
    char *startUpName;
    //
    float revenueEarned;
    //
    int suppliersNum;
    //
    double profitEarned;
    //
    long long usersCovered;
    //
    union {
        struct {
            bool isAngelInvestments         : 1;
            bool isVentureFondInverstments  : 1;
            bool isGovernmetnInverstments   : 1;
            bool isMultipleFounders         : 1;
            bool isFounderMajorStakeholder  : 1;
            bool isCreditBorrowed            : 1;
        } flags;
        char bitfield;
    };
    short employeesNum;
};

#endif /* IDPStructures_h */

