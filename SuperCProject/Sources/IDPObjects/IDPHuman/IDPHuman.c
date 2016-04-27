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
    IDPObjectStrongRefSetter((IDPObject *)human, (void **)&human->_name, name, &IDPStringCopy);
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
    
    IDPHumanSetChildrenCount(human, IDPHumanGetChildrenCount(human) + 1);
}


void IDPHumanDecrementChildrenCount(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    IDPHumanSetChildrenCount(human, IDPHumanGetChildrenCount(human) - 1);
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
    IDPObjectStrongRefSetter((IDPObject *)human, (void **)&human->_partner, partner, NULL);
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
    
    IDPHumanIncrementChildrenCount(human);
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
    
    if (kIDPHumanIndexNotFound == IDPHumanGetChildIndex(human, child)) {
        IDPHumanDecrementChildrenCount(human);
        
        IDPHumanReorderChildrenArray(human);
    }
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
    IDPObjectStrongRefSetter((IDPObject *)human, (void **)(&(human->_children[index])), child, NULL);
}

size_t IDPHumanGetChildIndex(IDPHuman *human, IDPHuman *child) {
    for(size_t index = 0; index < kIDPHumanMaxChildrenCount; index++) {
        IDPHuman *currentChild = IDPHumanGetChildAtIndex(human, index);
        if (child == currentChild) {
            return index;
        }
    }
    
    return kIDPHumanIndexNotFound;
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
