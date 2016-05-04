//
//  IDPHuman.h
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef __SuperCProject__IDPHuman__
#define __SuperCProject__IDPHuman__

#include <limits.h>
#include <stdbool.h>

#include "IDPObject.h"
#include "IDPString.h"
#include "IDPArray.h"

static const size_t kIDPHumanMaxChildrenCount = SIZE_T_MAX - 1;

typedef enum {
    IDPHumanGenderMale,
    IDPHumanGenderFemale
} IDPHumanGender;

typedef struct IDPHuman IDPHuman;

struct IDPHuman {
    IDPObject _super;
    
    IDPString *_name;
    int _age;
    IDPHumanGender _gender;

    IDPHuman *_partner;
    
    IDPHuman *_father;
    IDPHuman *_mother;
    
    IDPArray *_children;
};

extern
void __IDPHumanDeallocate(IDPHuman *human);

extern
void *IDPHumanCreate();

extern
void IDPHumanSetName(IDPHuman *human, IDPString *name);

extern
void IDPHumanSetAge(IDPHuman *human, int age);

extern
void IDPHumanSetGender(IDPHuman *human, IDPHumanGender gender);

extern
IDPString *IDPHumanGetName(IDPHuman *human);

extern
uint8_t IDPHumanGetAge(IDPHuman *human);

extern
IDPHumanGender IDPHumanGetGender(IDPHuman *human);

extern
IDPArray *IDPHumanGetChildrenArray(IDPHuman *human);

extern
bool IDPHumanIsMarried(IDPHuman *human);

extern
void IDPHumanDivorce(IDPHuman *human);

extern
void IDPHumanGetMarriedWithPartner(IDPHuman *human, IDPHuman *partner);

extern
IDPHuman *IDPHumanGiveBirthToChild(IDPHuman *human);

extern
uint64_t IDPHumanGetChildrenCount(IDPHuman *human);

extern
uint64_t IDPHumanGetChildIndex(IDPHuman *human, IDPHuman *child);

extern
IDPHuman *IDPHumanGetChildAtIndex(IDPHuman *human, size_t index);

#endif /* defined(__SuperCProject__IDPHuman__) */
