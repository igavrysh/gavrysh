//
//  IDPHuman.c
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include "IDPHuman.h"

#pragma mark -
#pragma mark Private Declarations


#pragma mark -
#pragma mark Public Implementations

void *IDPHumanCreate() {
    IDPHuman *result = IDPObjectCreateOfType(IDPHuman);
    
    return result;
}

void __IDPHumanDeallocate(void *object) {
    __IDPObjectDeallocate(object);
}

void IDPHumanSet(void *object, void *name) {
    
}

void IDPHumanSetAge(void *object, int age) {
    if (NULL == object) {
        return;
    }
    
    ((IDPHuman *)object)->_age = age;
}

void IDPHumanSetGender(void *object, IDPHumanGender gender) {
    if (NULL == object) {
        return;
    }
    
    ((IDPHuman *)object)->_gender = gender;
}

IDPString *IDPHumanGetName(void *object) {
    if (NULL == object) {
        return NULL;
    }
    
    return ((IDPHuman *)object)->_name;
}

uint8_t IDPHumanGetAge(void *object) {
    if (NULL == object) {
        return 0;
    }
    
    return ((IDPHuman *)object)->_age;
}

IDPHumanGender IDPHumanGetGender(void *object) {
    return ((IDPHuman *)object)->_gender;
}

bool IDPHumanIsMarried(void *object) {
    return object ?
        (((IDPHuman *)object)->_partner ? true : false) : false;
}

void IDPHumanMarryMan(void *object, void *man) {
    if (NULL == object || NULL == man || IDPHumanGenderFemale == ((IDPHuman *)man)->_gender) {
        return;
    }
    
    if (IDPHumanIsMarried(object)) {
        
    }
    
    if (IDPHumanIsMarried(man)) {
        
    }
}

#pragma mark -
#pragma mark Private Implementations

