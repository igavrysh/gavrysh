//
//  IDPHuman.c
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPHuman.h"


#pragma mark -
#pragma mark Public Implementations

void *IDPHumanCreate() {
    IDPHuman *result = IDPObjectCreateOfType(IDPHuman);
    
    return result;
}


void __IDPHumanDeallocate(void *object) {
    __IDPObjectDeallocate(object);
}

extern
void IDPHumanSetName(void *object, IDPName *name) {
    if (NULL == object) {
        return;
    }
    
    IDPNameDeepCopy(object, name);
}

extern
void IDPHumanSetAge(void *object, int age);

extern
void IDPHumanSetGender(void *object, IDPHumanGenger gender);

extern
IDPName *IDPHumanGetName(void *object);

extern
int IDPHumanGetAge(void *object);

extern
IDPHumanGenger IDPHumanGetGender(void *object);

extern
bool IDPHumanIsMarried(void *object);