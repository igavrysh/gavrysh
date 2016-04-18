//
//  IDPHuman.h
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef __SuperCProject__IDPHuman__
#define __SuperCProject__IDPHuman__

#include <stdbool.h>

#include "IDPObject.h"
#include "IDPString.h"

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
    IDPHuman *_parents;
    IDPHuman *_children[20];
};

extern
void *IDPHumanCreate();

extern
void __IDPHumanDeallocate(void *object);

extern
void IDPHumanSetName(void *object, IDPString *name);

extern
void IDPHumanSetAge(void *object, int age);

extern
void IDPHumanSetGender(void *object, IDPHumanGender gender);

extern
IDPString *IDPHumanGetName(void *object);

extern
uint8_t IDPHumanGetAge(void *object);

extern
IDPHumanGender IDPHumanGetGender(void *object);

extern
bool IDPHumanIsMarried(void *object);

#endif /* defined(__SuperCProject__IDPHuman__) */
