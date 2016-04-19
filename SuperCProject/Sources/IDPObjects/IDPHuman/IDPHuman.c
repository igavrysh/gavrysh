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

static
bool IDPHumanIsMarriageValidWithManAndWoman(IDPHuman *man,  IDPHuman *woman);

#pragma mark -
#pragma mark Public Implementations

void *IDPHumanCreate() {
    IDPHuman *result = IDPObjectCreateOfType(IDPHuman);
    
    return result;
}

void __IDPHumanDeallocate(void *object) {
    __IDPObjectDeallocate(object);
}

void IDPHumanSetName(void *object, IDPString *name) {
    if(NULL == object) {
        return;
    }
    
    IDPHuman *human = (IDPHuman *)object;
    
    if(human->_name != name) {
        if(human->_name) {
            IDPObjectRelease(human->_name);
            
            human->_name = NULL;
            
            human->_name = IDPStringCreateWithIDPString(name);
        }
    }
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

void IDPHumanDivorceWoman(void *objectMan) {
    IDPHuman *man = (IDPHuman *)objectMan;
    
    if (NULL == man || !IDPHumanIsMarried(man))  {
        return;
    }
    
    IDPObjectRelease(man->_partner);
    man->_partner = NULL;
}

void IDPHumanDivorceMan(void *objectWoman) {
    IDPHuman *woman = (IDPHuman *)objectWoman;
    
    if (NULL == woman || !IDPHumanIsMarried(woman)) {
        return;
    }
    
    IDPHumanDivorceWoman(woman->_partner);
}

void IDPHumanGetMarriedWoman(void *objectMan, void *objectWoman) {
    IDPHuman *man = (IDPHuman *)objectMan;
    IDPHuman *woman = (IDPHuman *)objectWoman;
    
    if (!IDPHumanIsMarriageValidWithManAndWoman(man, woman)) {
        return;
    }
    
    if (man->_partner != woman) {
        IDPObjectRetain(woman);
        
        IDPHumanDivorceWoman(man);
        IDPHumanDivorceMan(woman);
        
        man->_partner = woman;
    }
}

void IDPHumanGetMarriedMan(void *objectWoman, void *objectMan) {
    IDPHuman *man = (IDPHuman *)objectMan;
    IDPHuman *woman = (IDPHuman *)objectWoman;
    
    if (!IDPHumanIsMarriageValidWithManAndWoman(man, woman)) {
        return;
    }
    
    if (woman->_partner != man) {
        IDPHumanDivorceWoman(man);
        IDPHumanDivorceMan(woman);
        
        woman->_partner = man;
    }
}

#pragma mark -
#pragma mark Private Implementations

bool IDPHumanIsMarriageValidWithManAndWoman(IDPHuman *man,  IDPHuman *woman) {
    return (NULL == man ||
            NULL == woman ||
            IDPHumanGenderMale == woman->_gender ||
            IDPHumanGenderFemale == man->_gender) ? false : true;
}

