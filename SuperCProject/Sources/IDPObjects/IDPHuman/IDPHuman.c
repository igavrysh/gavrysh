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
void IDPHumanMapPartner(IDPHuman *human, IDPHuman **male, IDPHuman **female);

static
void IDPHumanMapMaleAndFemale(IDPHuman *human, IDPHuman *partner, IDPHuman **male, IDPHuman **female);

static
void IDPHumanSetChildStrongRef(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveAllChildren(IDPHuman *human);

static
void IDPHumanReleaseChildStrongRef(IDPHuman *human, IDPHuman *child);

static
IDPHuman* IDPHumanRemoveChild(IDPHuman *human, IDPHuman *child);

static
IDPHuman *IDPHumanAddChild(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveAllChildren(IDPHuman *human);

#pragma mark -
#pragma mark Public Implementations

void __IDPHumanDeallocate(IDPHuman *object) {
    IDPHuman *human = (IDPHuman *)object;
    
    IDPHumanReleaseChildStrongRef(human->_father, human);
    IDPHumanReleaseChildStrongRef(human->_mother, human);
    IDPHumanRemoveAllChildren(human);
    
    IDPHumanSetName(human, NULL);
    
    IDPHumanSetPartner(human, NULL);
    
    __IDPObjectDeallocate(object);
}

void *IDPHumanCreate() {
    IDPHuman *result = IDPObjectCreateOfType(IDPHuman);
    
    IDPHumanInitInternalVars(result);
    
    return result;
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

IDPHuman *IDPHumanBurnChild(IDPHuman *human) {
    if (!human) {
        return NULL;
    }
    
    if (IDPHumanGenderMale == IDPHumanGetGender(human)) {
        return IDPHumanBurnChild(IDPHumanGetPartner(human));
    }
    
    IDPHuman *child = IDPHumanCreate();
    IDPHumanSetChildStrongRef(human->_partner, child);
    IDPHumanSetChildStrongRef(human, child);
    IDPObjectRelease(child);
    
    return child;
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


void IDPHumanRemoveAllChildren(IDPHuman *human) {
    IDPHumanRemoveChild(human, NULL);
}

void IDPHumanReleaseChildStrongRef(IDPHuman *human, IDPHuman *child) {
    if (!human) {
        return;
    }
    
    IDPHumanRemoveChild(human, child);
    IDPHumanSetChildStrongRef(human, NULL);
}


void IDPHumanSetChildStrongRef(IDPHuman *human, IDPHuman *child) {
    if (!human) {
        return;
    }
    
    if (IDPHumanGenderMale == IDPHumanGetGender(human)) {
        child->_father = IDPHumanAddChild(human, child);
    } else {
        child->_mother = IDPHumanAddChild(human, child);
    }
}


IDPHuman *IDPHumanAddChild(IDPHuman *human, IDPHuman *child) {
    if (!human || !child) {
        return NULL;
    }
    
    for(uint8_t i = 0; i < kIDPHumanMaxChildrenCount; i++) {
        if (!human->_children[i]) {
            human->_children[i] = IDPObjectRetain(child);
            return human->_children[i];
        }
    }
    
    return NULL;
}

IDPHuman* IDPHumanRemoveChild(IDPHuman *human, IDPHuman *child) {
    bool shiftChilds = false;
    for(uint8_t i = 0; i < kIDPHumanMaxChildrenCount; i++) {
        if (human->_children[i] == child || !child) {
            
            IDPObjectRelease(child);
            shiftChilds = true;
        }
        if (shiftChilds && child) {
            human->_children[i] = (i == kIDPHumanMaxChildrenCount - 1) ? NULL : human->_children[i+1];
        }
    }
    
    return NULL;
}
