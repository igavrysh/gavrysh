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
void IDPHumanInitInternalVars(IDPHuman *human);

static
void IDPHumanSetWeakRefToPartner(IDPHuman *human, IDPHuman *partner);

static
void IDPHumanSetStrongRefToPartner(IDPHuman *human, IDPHuman *partner);

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

void IDPHumanDivorce(IDPHuman *human) {
    IDPHumanSetPartner(human->_partner, NULL);
    IDPHumanSetPartner(human, NULL);
}

void IDPHumanGetMarriedWithPartner(IDPHuman *human, IDPHuman *partner) {
    IDPHumanDivorce(human);
    IDPHumanDivorce(partner);
    
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

void IDPHumanSetWeakRefToPartner(IDPHuman *human, IDPHuman *partner) {
    if (!human) {
        return;
    }
    
    if (human->_partner != partner) {
        human->_partner = partner;
    }
}

void IDPHumanSetStrongRefToPartner(IDPHuman *human, IDPHuman *partner) {
    if (!human) {
        return;
    }
    
    if (human->_partner != partner) {
        if (human->_partner) {
            IDPObjectRelease(human->_partner);
            human->_partner = NULL;
        }
        
        human->_partner = IDPObjectRetain(partner);
    }
}

void IDPHumanSetPartner(IDPHuman *human, IDPHuman *partner) {
    if (!human)  {
        return;
    }
    
    if (IDPHumanGenderMale == IDPHumanGetGender(human)) {
        IDPHumanSetStrongRefToPartner(human, partner);
        IDPHumanSetWeakRefToPartner(partner, human);
    }
    else {
        IDPHumanSetStrongRefToPartner(partner, human);
        IDPHumanSetWeakRefToPartner(human, partner);
    }
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

