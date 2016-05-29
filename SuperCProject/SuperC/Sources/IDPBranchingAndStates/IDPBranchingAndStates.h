//
//  IDPDivideBy15.h
//  SuperCProject
//
//  Created by Ievgen on 4/6/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#ifndef IDPBranchingAndStates_h
#define IDPBranchingAndStates_h

#include <stdbool.h>

extern
char *IDPCreateStringForBoolValue(bool boolValue);

extern
void IDPPrintMamaPapaStdBranching(int firstNum, int secondNum);

extern
void IDPPrintMamaPapaTernaryBranching(int firstNum, int secondNum);

extern
void IDPPrintDeputyStateWithSalaryAndIncome(float salary, float income);

typedef enum {
    IDPPrintStateNone       = 0,
    IDPPrintStateMama       = 1 << 0,
    IDPPrintStatePapa       = 1 << 1,
    IDPPrintStateMamaPapa   = IDPPrintStateMama | IDPPrintStatePapa
} IDPPrintState;

extern
IDPPrintState IDPPrintStatePrintWithNumber(int num);

#endif /* IDPBranchingAndStates_h */
