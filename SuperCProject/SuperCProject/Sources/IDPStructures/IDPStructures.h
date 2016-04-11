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
    bool _isAngelInvestments;
    char *_startUpName;
    bool _isVentureFondInverstments;
    float _revenueEarned;
    bool _isGovernmetnInverstments;
    double _profitEarned;
    bool _isMultipleFounders;
    long long _usersCovered;
    bool _isFounderMajorStakeholder;
    int _suppliersNum;
    bool _isCreditBorrowed;
    short _employeesNum;
};

typedef struct IDPStartUpCompressed IDPStartUpCompressed;

struct IDPStartUpCompressed {
    char *_startUpName;
    //
    float _revenueEarned;
    int _suppliersNum;
    //
    double _profitEarned;
    //
    long long _usersCovered;
    //
    short _employeesNum;
    bool _isAngelInvestments;
    bool _isVentureFondInverstments;
    bool _isGovernmetnInverstments;
    bool _isMultipleFounders;
    bool _isFounderMajorStakeholder;
    bool _isCreditBorrowed;
};

typedef struct IDPStartUpUnionized IDPStartUpUnionized;

struct IDPStartUpUnionized {
    char *_startUpName;
    //
    float _revenueEarned;
    int _suppliersNum;
    //
    double _profitEarned;
    //
    long long _usersCovered;
    //
    union {
        struct {
            bool _isAngelInvestments;
            bool _isVentureFondInverstments;
            bool _isGovernmetnInverstments;
            bool _isMultipleFounders;
            bool _isFounderMajorStakeholder;
            bool _isCreditBorrowed;
        } flags;
        char bitFields;
    };
    short _employeesNum;
};

#endif /* IDPStructures_h */

