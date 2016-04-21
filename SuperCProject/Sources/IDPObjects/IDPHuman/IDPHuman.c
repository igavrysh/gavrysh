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
bool IDPHumanIsMarriageWithPartnerValid(IDPHuman *human,  IDPHuman *partner);

static
void IDPHumanInitInternalVars(IDPHuman *human);

static
uint8_t IDPHumanGetIndexOfNextChild(IDPHuman *human);

static
void IDPHumanSetPartner(IDPHuman *human, IDPHuman *partner);

static
IDPHuman *IDPHumanGetPartner(IDPHuman *human);

static
void IDPHumanSetChild(IDPHuman *human, IDPHuman *child);

static
void IDPHumanMapPartner(IDPHuman *human, IDPHuman **male, IDPHuman **female);

static
void IDPHumanMapMaleAndFemale(IDPHuman *human, IDPHuman *partner, IDPHuman **male, IDPHuman **female);

static
void IDPHumanDropChildren(IDPHuman *human);

#pragma mark -
#pragma mark Public Implementations

void *IDPHumanCreate() {
    IDPHuman *result = IDPObjectCreateOfType(IDPHuman);
    
    IDPHumanInitInternalVars(result);
    
    return result;
}

void __IDPHumanDeallocate(IDPHuman *object) {
    IDPHuman *human = (IDPHuman *)object;
    
    IDPHumanSetName(human, NULL);

    IDPHumanSetPartner(human, NULL);
    
    IDPHumanSetChild(human, NULL);
    
    __IDPObjectDeallocate(object);
}

void IDPHumanSetName(IDPHuman *human, IDPString *name) {
    if(!human) {
        return;
    }
    
    if(human->_name != name) {
        if (human->_name) {
            IDPObjectRelease(human->_name);
            human->_name = NULL;
        }
        
        human->_name = IDPStringCreateWithIDPString(name);
    }
}

void IDPHumanSetAge(IDPHuman *human, int age) {
    if (NULL == human) {
        return;
    }
    
    human->_age = age;
}

void IDPHumanSetGender(IDPHuman *human, IDPHumanGender gender) {
    if (!human) {
        return;
    }
    
    human->_gender = gender;
}

IDPString *IDPHumanGetName(IDPHuman *human) {
    if (!human) {
        return NULL;
    }
    
    return human->_name;
}

uint8_t IDPHumanGetAge(IDPHuman *human) {
    if (!human) {
        return 0;
    }
    
    return human->_age;
}

IDPHumanGender IDPHumanGetGender(IDPHuman *human) {
    return human->_gender;
}

bool IDPHumanIsMarried(IDPHuman *human) {
    return (human && human->_partner);
}

void IDPHumanMarryWoman(IDPHuman *human, IDPHuman *partner) {
    if (human != partner) {
        // Break up old marriage
        if (human->_partner) {
            human->_partner->_partner = NULL;
            IDPObjectRelease(human->_partner);
            human->_partner = NULL;
        }
        
        //Set up a new marriage
        human->_partner = IDPObjectRetain(partner);
        if (partner) {
            partner->_partner = human;
        }
    }
}


void IDPHumanMarryMan(IDPHuman *human, IDPHuman *partner) {
    if (human != partner) {
        // Break up old marriage
        if (human->_partner) {
            IDPObjectRelease(human->_partner->_partner);
            human->_partner->_partner = NULL;
            human->_partner = NULL;
        }
        
        //Set up a new marriage
        human->_partner = partner;
        if(partner) {
            partner->_partner = IDPObjectRetain(human);
        }
    }
}

void IDPHumanSetPartner(IDPHuman *human, IDPHuman *partner) {
    if (!human)  {
        return;
    }
    
    IDPHuman *male;
    IDPHuman *female;
    
    IDPHumanMapMaleAndFemale(human, partner, &male, &female);
    
    IDPHuman *oldfiance = IDPHumanGetPartner(female);
    IDPHumanMarryWoman(male, female);
    IDPHumanMarryMan(female, male);
    if(oldfiance) {
        IDPObjectRelease(IDPHumanGetPartner(oldfiance));
        oldfiance->_partner = NULL;
    }
}

void IDPHumanDivorce(IDPHuman *human) {
    IDPHumanSetPartner(human, NULL);
}

void IDPHumanGetMarriedWithPartner(IDPHuman *human, IDPHuman *partner) {
    //IDPHumanDivorce(human);
    //IDPHumanDivorce(partner);
    IDPHumanSetPartner(human, partner);
}


void IDPHumanSetChild(IDPHuman *human, IDPHuman *child) {
    if (!NULL) {
        return;
    }
    
    IDPHuman *male;
    IDPHuman *female;
    
    IDPHumanMapPartner(human, &male, &female);

    if (NULL == child) {
        IDPHumanDropChildren(human);
    }
}

IDPHuman *IDPHumanGiveBirth(IDPHuman *human) {
    if (NULL != human || (IDPHumanGenderMale == IDPHumanGetGender(human) &&  NULL == IDPHumanGetPartner(human))) {
        return NULL;
    }
    
    if (IDPHumanGenderMale == IDPHumanGetGender(human)) {
        return IDPHumanGiveBirth(IDPHumanGetPartner(human));
    }
    
    return NULL;
}

#pragma mark -
#pragma mark Private Implementations

bool IDPHumanIsMarriageWithPartnerValid(IDPHuman *human,  IDPHuman *partner) {
    return (!human
        &&  !partner
        && ((IDPHumanGenderFemale == human->_gender
        &&   IDPHumanGenderMale == partner->_gender)
        ||  (IDPHumanGenderFemale == partner->_gender
        &&   IDPHumanGenderMale == human->_gender)));
}

void IDPHumanInitInternalVars(IDPHuman *human) {
    for(uint8_t i = 0; i < kIDPHumanMaxChildrenCount; i++) {
        human->_children[i] = NULL;
    }
    
    human->_age = 0;
    human->_gender = IDPHumanGenderMale;
    human->_name = NULL;
    
    human->_partner = NULL;
    human->_father = NULL;
    human->_partner = NULL;
}

IDPHuman *IDPHumanGetPartner(IDPHuman *human) {
    return human ? human->_partner : NULL;
}

void IDPHumanDropChildren(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    for(uint8_t i = 0; i < kIDPHumanMaxChildrenCount; i++)  {
        if (human->_children[i] != NULL) {
            IDPObjectRelease(human->_children[i]);
            human->_children[i] = NULL;
        }
    }
}

void IDPHumanMapPartner(IDPHuman *human, IDPHuman **male, IDPHuman **female) {
    IDPHumanMapMaleAndFemale(human, IDPHumanGetPartner(human), male, female);
}

void IDPHumanMapMaleAndFemale(IDPHuman *human, IDPHuman *partner, IDPHuman **male, IDPHuman **female) {
    if (!human || !partner) {
        return;
    }
    
    *male = IDPHumanGenderMale == IDPHumanGetGender(human) ? human : partner;
    *female = IDPHumanGenderFemale == IDPHumanGetGender(human) ? human : partner;
}

