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

static const size_t kIDPHumanIndexNotFount = SIZE_T_MAX;

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
IDPHuman *IDPHumanGetChildAtIndex(IDPHuman *human, size_t index);

static
size_t IDPHumanGetChildIndex(IDPHuman *human, IDPHuman *child);

static
void IDPHumanReorderChildrenArray(IDPHuman *human);

static
void IDPHumanSetChildrenCount(IDPHuman *human, size_t count);

static
void IDPHumanIncrementChildrenCount(IDPHuman *human);

static
void IDPHumanDecrementChildrenCount(IDPHuman *human);

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

size_t IDPHumanGetChildrenCount(IDPHuman *human) {
    return human ? human->_childrenCount : 0;
}

void IDPHumanSetChildrenCount(IDPHuman *human, size_t count) {
    if (!human) {
        return;
    }
    
    human->_childrenCount = count;
}

void IDPHumanIncrementChildrenCount(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    human->_childrenCount += 1;
}


void IDPHumanDecrementChildrenCount(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    human->_childrenCount -= 1;
}

#pragma mark -
#pragma mark Private Implementations

void IDPHumanInit(IDPHuman *human) {
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
        && IDPHumanGetChildrenCount(human->_partner) < kIDPHumanMaxChildrenCount;
}

void IDPHumanAddChild(IDPHuman *human, IDPHuman *child) {
    if (!human || !child) {
        return;
    }
    
    if (human != child) {
        IDPHuman *partner = IDPHumanGetPartner(human);
        
        IDPHumanSetChildWithNewValue(human, NULL, child);
        IDPHumanSetChildWithNewValue(partner, NULL, child);
        
        IDPHumanSetParentWithNewValue(child, human, human);
        IDPHumanSetParentWithNewValue(child, partner, partner);
    }
}

void IDPHumanRemoveChild(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    IDPHumanSetChildWithNewValue(human->_father, human, NULL);
    IDPHumanSetChildWithNewValue(human->_mother, human, NULL);
    
    IDPHumanSetParentWithNewValue(human, human->_father, NULL);
    IDPHumanSetParentWithNewValue(human, human->_mother, NULL);
}

void IDPHumanRemoveAllChildren(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    size_t childrenCount = IDPHumanGetChildrenCount(human);
    for (size_t index = 0; index < childrenCount; index++) {
        IDPHumanRemoveChild(IDPHumanGetChildAtIndex(human, childrenCount - index - 1));
    }
}

void IDPHumanSetChildWithNewValue(IDPHuman *human, IDPHuman *child, IDPHuman *newChild) {
    if (!child) {
        IDPHumanSetChildAtIndex(human, newChild, IDPHumanGetChildrenCount(human));
    } else {
        size_t index = IDPHumanGetChildIndex(human, child);
        IDPHumanSetChildAtIndex(human, NULL, index);
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
    
    return human->_children[index];
}

void IDPHumanSetChildAtIndex(IDPHuman *human, IDPHuman *child, size_t index) {
    if (!human) {
        return;
    }
    
    IDPHuman *prevChildAtIndex = IDPHumanGetChildAtIndex(human, index);
    
    if (child) {
        human->_children[index] = IDPObjectRetain(child);
        if (!prevChildAtIndex) {
            IDPHumanIncrementChildrenCount(human);
        }
    } else {
        IDPObjectRelease(human->_children[index]);
        human->_children[index] = NULL;
        if (prevChildAtIndex) {
            IDPHumanDecrementChildrenCount(human);
        }
    }
    
    IDPHumanReorderChildrenArray(human);
}

size_t IDPHumanGetChildIndex(IDPHuman *human, IDPHuman *child) {
    for(size_t index = 0; index < kIDPHumanMaxChildrenCount; index++) {
        IDPHuman *currentChild = IDPHumanGetChildAtIndex(human, index);
        if (child == currentChild) {
            return index;
        }
    }
    
    return kIDPHumanIndexNotFount;
}

void IDPHumanReorderChildrenArray(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    size_t outerIndex = IDPHumanGetChildrenCount(human);
    
    size_t childrenCount = IDPHumanGetChildrenCount(human);
    for (size_t index = 0; index < childrenCount; index++) {
        if (!IDPHumanGetChildAtIndex(human, index)) {
            while (!IDPHumanGetChildAtIndex(human, outerIndex)
                   && outerIndex < kIDPHumanMaxChildrenCount) {
                outerIndex++;
            }
            
            if (outerIndex < kIDPHumanMaxChildrenCount) {
                human->_children[index] = human->_children[outerIndex];
            }
        }
    }
}
