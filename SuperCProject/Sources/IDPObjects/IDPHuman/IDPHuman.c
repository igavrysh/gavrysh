//
//  IDPHuman.c
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <limits.h>

#include "IDPHuman.h"

#pragma mark -
#pragma mark Private Declarations

static const size_t kIDPHumanIndexNotFound = SIZE_T_MAX;

static
void IDPHumanInit(IDPHuman *human);

static
void IDPHumanSetWeakPartner(IDPHuman *human, IDPHuman *partner);

static
void IDPHumanSetStrongPartner(IDPHuman *human, IDPHuman *partner);

static
void IDPHumanSetPartner(IDPHuman *human, IDPHuman *partner);

static
IDPHuman *IDPHumanGetPartner(IDPHuman *human);

static
void IDPHumanAddChild(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveChild(IDPHuman *human);

static
void IDPHumanAddChildToParent(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveChildFromParent(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveAllChildren(IDPHuman *human);

static
void IDPHumanSetChildWithNewValue(IDPHuman *human, IDPHuman *child, IDPHuman *newChild);

static
void IDPHumanSetParentWithNewValue(IDPHuman *human, IDPHuman *parent, IDPHuman *newParent);

static
void IDPHumanRemoveAllChildren(IDPHuman *human);

static
bool IDPHumanCanGiveBirth(IDPHuman *human);

static
void IDPHumanSetChildAtIndex(IDPHuman *human, IDPHuman *child, size_t index);

static
void IDPHumanReorderChildrenArray(IDPHuman *human);

#pragma mark -
#pragma mark Public Implementations

void __IDPHumanDeallocate(IDPHuman *object) {
    IDPHuman *human = (IDPHuman *)object;
    
    IDPHumanRemoveAllChildren(human);
    
    IDPHumanRemoveChild(human);
    
    IDPHumanDivorce(human);
    
    IDPHumanSetName(human, NULL);
    
    __IDPObjectDeallocate(object);
}

void *IDPHumanCreate() {
    IDPHuman *result = IDPObjectCreateWithType(IDPHuman);
    
    IDPHumanInit(result);
    
    return result;
}

void IDPHumanSetName(IDPHuman *human, IDPString *name) {
    IDPObjectSetStrong((IDPObject *)human, (void **)&human->_name, name, &IDPStringCopy);
}

IDPString *IDPHumanGetName(IDPHuman *human) {
    return human ? human->_name : NULL;
}

void IDPHumanSetAge(IDPHuman *human, int age) {
    if (!human) {
        return;
    }
    
    human->_age = age;
}

uint8_t IDPHumanGetAge(IDPHuman *human) {
    return human ? human->_age : 0;
}

void IDPHumanSetGender(IDPHuman *human, IDPHumanGender gender) {
    if (!human) {
        return;
    }
    
    human->_gender = gender;
}

IDPHumanGender IDPHumanGetGender(IDPHuman *human) {
    return human ? human->_gender : IDPHumanGenderMale;
}

IDPArray *IDPHumanGetChildrenArray(IDPHuman *human) {
    return human ? human->_children : NULL;
}

bool IDPHumanIsMarried(IDPHuman *human) {
    return human && human->_partner;
}

void IDPHumanDivorce(IDPHuman *human) {
    IDPHumanSetPartner(human->_partner, NULL);
    IDPHumanSetPartner(human, NULL);
}

void IDPHumanGetMarriedWithPartner(IDPHuman *human, IDPHuman *partner) {
    IDPHumanDivorce(human);
    IDPHumanDivorce(partner);
    
    IDPHumanSetPartner(human, partner);
    IDPHumanSetPartner(partner, human);
}

uint64_t IDPHumanGetChildrenCount(IDPHuman *human) {
    return human ? IDPArrayGetCount(IDPHumanGetChildrenArray(human)) : 0;
}


#pragma mark -
#pragma mark Private Implementations

void IDPHumanInit(IDPHuman *human) {
    human->_name = IDPStringCreateWithString("");
}

#pragma mark -
#pragma mark Private Implementations - Set Partner functionality

void IDPHumanSetWeakPartner(IDPHuman *human, IDPHuman *partner) {
    if (!human) {
        return;
    }
    
    human->_partner = partner;
}

void IDPHumanSetStrongPartner(IDPHuman *human, IDPHuman *partner) {
    IDPObjectSetStrong((IDPObject *)human, (void **)&human->_partner, partner, NULL);
}

void IDPHumanSetPartner(IDPHuman *human, IDPHuman *partner) {
    if (!human)  {
        return;
    }
    
    if (IDPHumanGenderMale == IDPHumanGetGender(human)) {
        IDPHumanSetStrongPartner(human, partner);
    } else {
        IDPHumanSetWeakPartner(human, partner);
    }
}

IDPHuman *IDPHumanGetPartner(IDPHuman *human) {
    return human ? human->_partner : NULL;
}

#pragma mark - 
#pragma mark Private Implementations - Give Birth functionality

IDPHuman *IDPHumanGiveBirthToChild(IDPHuman *human) {
    if (!human) {
        return NULL;
    }
    
    if (!IDPHumanCanGiveBirth(human)) {
        return NULL;
    }
    
    if (IDPHumanGenderMale == IDPHumanGetGender(human)) {
        return IDPHumanGiveBirthToChild(IDPHumanGetPartner(human));
    }
    
    IDPHuman *child = IDPHumanCreate();
    IDPHumanAddChild(human, child);
    IDPObjectRelease(child);
    
    return child;
}

bool IDPHumanCanGiveBirth(IDPHuman *human) {
    return IDPHumanGetPartner(human)
        && IDPHumanGetChildrenCount(human) < kIDPHumanMaxChildrenCount
        && IDPHumanGetChildrenCount(IDPHumanGetPartner(human)) < kIDPHumanMaxChildrenCount;
}

void IDPHumanAddChild(IDPHuman *human, IDPHuman *child) {
    if (!human || !child) {
        return;
    }
    
    if (human != child) {
        IDPHuman *partner = IDPHumanGetPartner(human);
        IDPHumanAddChildToParent(human, child);
        IDPHumanAddChildToParent(partner, child);
    }
}

void IDPHumanAddChildToParent(IDPHuman *human, IDPHuman *child) {
    if (!human) {
        return;
    }
    
    IDPHumanSetChildWithNewValue(human, NULL, child);
    IDPHumanSetParentWithNewValue(child, human, human);
}

void IDPHumanRemoveChild(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    IDPHumanRemoveChildFromParent(human->_father, human);
    IDPHumanRemoveChildFromParent(human->_mother, human);
}

void IDPHumanRemoveChildFromParent(IDPHuman *human, IDPHuman *child) {
    if (!human || !child) {
        return;
    }

    IDPHumanSetChildWithNewValue(human, child, NULL);
    IDPHumanSetParentWithNewValue(child, human, NULL);
}

void IDPHumanRemoveAllChildren(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    uint64_t childrenCount = IDPHumanGetChildrenCount(human);
    for (uint64_t index = 0; index < childrenCount; index++) {
        IDPHumanRemoveChild(IDPHumanGetChildAtIndex(human, childrenCount - index - 1));
    }
}

void IDPHumanSetChildWithNewValue(IDPHuman *human, IDPHuman *child, IDPHuman *newChild) {
    if (!human) {
        return;
    }

    if (!IDPHumanGetChildrenArray(human)) {
        human->_children = IDPObjectCreateWithType(IDPArray);
    }
    
    if (!child) {
        IDPArrayAddObject(IDPHumanGetChildrenArray(human), newChild);
    } else {
        uint64_t index = IDPArrayGetIndexOfObject(IDPHumanGetChildrenArray(human), child);
        if (kIDPNotFound != index) {
            IDPArrayRemoveObjectAtIndex(IDPHumanGetChildrenArray(human), index);
        }
    }
}

void IDPHumanSetParentWithNewValue(IDPHuman *human, IDPHuman *parent, IDPHuman *newParent) {
    if (IDPHumanGenderMale == IDPHumanGetGender(parent)) {
        human->_father = newParent;
    } else if (IDPHumanGenderFemale == IDPHumanGetGender(parent)){
        human->_mother = newParent;
    }
}

IDPHuman *IDPHumanGetChildAtIndex(IDPHuman *human, size_t index) {
    if (!human) {
        return NULL;
    }
    
    return IDPArrayGetObjectAtIndex(IDPHumanGetChildrenArray(human), index);
}

uint64_t IDPHumanGetChildIndex(IDPHuman *human, IDPHuman *child) {
    if (!human) {
        return 0;
    }
    
    uint64_t result = IDPArrayGetIndexOfObject(IDPHumanGetChildrenArray(human), child);
    
    if (result == kIDPNotFound) {
        return kIDPHumanIndexNotFound;
    }
    
    return result;
}

void IDPHumanReorderChildrenArray(IDPHuman *human) {
    return;
}
