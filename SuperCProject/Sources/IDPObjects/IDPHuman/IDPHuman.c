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

void IDPHumanSetName(void *object, IDPName *name) {
    if (NULL == object) {
        return;
    }
    
    IDPNameDeepCopy(object, name);
}

void IDPHumanSetAge(void *object, int age) {
    if (NULL == object) {
        return;
    }
    
    ((IDPHuman *)object)->age = age;
}

void IDPHumanSetGender(void *object, IDPHumanGendegr gender) {
    if (NULL == object) {
        return;
    }
    
    ((IDPHuman *)object)->_gender = gender;
}

IDPName *IDPHumanGetName(void *object) {
    if (NULL == object) {
        return NULL;
    }
    
    return ((IDPHuman *)object)->_name;
}

int IDPHumanGetAge(void *object) {
    if (NULL == object) {
        return 0;
    }
    
    return ((IDPHuman *)object)->age;
}

IDPHumanGendegr IDPHumanGetGender(void *object) {
    if (NULL == object) {
        return 0;
    }
    
    return ((IDPHuman *)object)->_gender;
}

bool IDPHumanIsMarried(void *object) {
    if (NULL == object) {
        return false;
    }
    
    return ((IDPHuman *)object)->isMarried;
}

void IDPHumanMarryMan(void *object, void *man) {
   // if (NULL == object || NULL == man || IDPHumanGenderFemale == ((IDPHuman)man)->gender) {
    //    return;
    //}
    
    if (((IDPHuman *)object)->isMarried) {
        
    }
    
    if (((IDPHuman *)man)->isMarried) {
        
    }
    
    ((IDPHuman*)object)->isMarried = true;
}

#pragma mark -
#pragma mark Private Implementations

