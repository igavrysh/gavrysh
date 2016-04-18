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
#include "IDPName.h"

typedef enum {
    IDPHumanGenderMale,
    IDPHumanGenderFemale
} IDPHumanGendegr;

typedef struct IDPHuman IDPHuman;

struct IDPHuman {
    IDPObject _super;
    
    IDPName *_name;
    
    int age;
    
    IDPHumanGendegr _gender;
    
    bool isMarried;
    IDPHuman *_partner;
    
    IDPHuman *_parents;
    
    IDPHuman *_children[20];
};

extern
void *IDPHumanCreate();

extern
void __IDPHumanDeallocate(void *object);

extern
void IDPHumanSetName(void *object, IDPName *name);

extern
void IDPHumanSetAge(void *object, int age);

extern
void IDPHumanSetGender(void *object, IDPHumanGendegr gender);

extern
IDPName *IDPHumanGetName(void *object);

extern
int IDPHumanGetAge(void *object);

extern
IDPHumanGendegr IDPHumanGetGender(void *object);

extern
bool IDPHumanIsMarried(void *object);

#endif /* defined(__SuperCProject__IDPHuman__) */
