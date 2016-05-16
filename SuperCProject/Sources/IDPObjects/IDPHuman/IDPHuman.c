//
//  IDPHuman.c
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#include <limits.h>

#include "IDPHuman.h"
#include "IDPObjectMacros.h"

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
IDPHuman *IDPHumanGetFather(IDPHuman *human);

static
void IDPHumanSetFather(IDPHuman *human, IDPHuman *father);

static
IDPHuman *IDPHumanGetMother(IDPHuman *human);

static
void IDPHumanSetMother(IDPHuman *human, IDPHuman *mother);

static
void IDPHumanAddChildToParents(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveChildFromParents(IDPHuman *human);

static
void IDPHumanAddChildToParent(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveChildFromParent(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveAllChildren(IDPHuman *human);

static
void IDPHumanSetParentWithNewValue(IDPHuman *human, IDPHuman *parent, IDPHuman *newParent);

static
void IDPHumanRemoveAllChildren(IDPHuman *human);

static
bool IDPHumanCanGiveBirth(IDPHuman *human);

static
void IDPHumanAppendChildrenWithChild(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveChildAtIndex(IDPHuman *human, size_t index);

static
void IDPHumanSetChildAtIndex(IDPHuman *human, IDPHuman *child, size_t index);

static
void IDPHumanReorderChildrenArray(IDPHuman *human);

static
void IDPHumanSetChildrenCount(IDPHuman *human, size_t count);

static
void IDPHumanChildrenCountAddValue(IDPHuman *human, size_t value);

#pragma mark -
#pragma mark Public Implementations

void __IDPHumanDeallocate(IDPHuman *human) {
    IDPHumanRemoveAllChildren(human);
    
    IDPHumanRemoveChildFromParents(human);
    
    IDPHumanDivorce(human);
    
    IDPHumanSetName(human, NULL);
    
    __IDPObjectDeallocate(human);
}

void *IDPHumanCreate() {
    IDPHuman *result = IDPObjectCreateWithType(IDPHuman);
    
    IDPHumanInit(result);
    
    return result;
}

void IDPHumanSetName(IDPHuman *human, IDPString *name) {
    IDPObjectSetFieldValueWithMethod(human, _name, name, IDPStringCopy);
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

void IDPHumanChildrenCountAddValue(IDPHuman *human, size_t value) {
    if (!human) {
        return;
    }
    
    IDPHumanSetChildrenCount(human, IDPHumanGetChildrenCount(human) + value);
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
    IDPObjectSetStrong(human, _partner, partner);
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

IDPHuman *IDPHumanGetFather(IDPHuman *human) {
    return human ? human->_father : NULL;
}

void IDPHumanSetFather(IDPHuman *human, IDPHuman *father) {
    if (!human) {
        return;
    }
    
    human->_father = father;
}

IDPHuman *IDPHumanGetMother(IDPHuman *human) {
    return human ? human->_mother : NULL;
}

void IDPHumanSetMother(IDPHuman *human, IDPHuman *mother) {
    if (!human) {
        return;
    }
    
    human->_mother = mother;
}

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
    IDPHumanAddChildToParents(human, child);
    IDPObjectRelease(child);
    
    return child;
}

bool IDPHumanCanGiveBirth(IDPHuman *human) {
    uint64_t maxChildrenCount = kIDPHumanMaxChildrenCount;
    
    return IDPHumanGetPartner(human)
        && IDPHumanGetChildrenCount(human) < maxChildrenCount
        && IDPHumanGetChildrenCount(IDPHumanGetPartner(human)) < maxChildrenCount;
}

void IDPHumanAddChildToParents(IDPHuman *human, IDPHuman *child) {
    if (!human || !child) {
        return;
    }
    
    if (human != child) {
        IDPHumanAddChildToParent(human, child);
        IDPHumanAddChildToParent(IDPHumanGetPartner(human), child);
    }
}

void IDPHumanAddChildToParent(IDPHuman *human, IDPHuman *child) {
    if (!human) {
        return;
    }
    
    IDPHumanAppendChildrenWithChild(human, child);
    
    IDPHumanSetParentWithNewValue(child, human, human);
    
    IDPHumanChildrenCountAddValue(human, 1);
}

void IDPHumanRemoveChildFromParents(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    IDPHumanRemoveChildFromParent(IDPHumanGetFather(human), human);
    IDPHumanRemoveChildFromParent(IDPHumanGetMother(human), human);
}

void IDPHumanRemoveChildFromParent(IDPHuman *human, IDPHuman *child) {
    if (!human || !child) {
        return;
    }
    
    size_t childIndex = IDPHumanGetChildIndex(human, child);
    
    if (kIDPHumanIndexNotFound == childIndex) {
        return;
    }
    
    IDPHumanRemoveChildAtIndex(human, childIndex);
    IDPHumanSetParentWithNewValue(child, human, NULL);
    
    if (kIDPHumanIndexNotFound != childIndex
        && kIDPHumanIndexNotFound == IDPHumanGetChildIndex(human, child))
    {
        IDPHumanChildrenCountAddValue(human, -1);
        
        IDPHumanReorderChildrenArray(human);
    }
}

void IDPHumanRemoveAllChildren(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    size_t childrenCount = IDPHumanGetChildrenCount(human);
    for (size_t index = 0; index < childrenCount; index++) {
        IDPHumanRemoveChildFromParent(human, IDPHumanGetChildAtIndex(human, childrenCount - index - 1));
        //IDPHumanRemoveChildAtIndex(human, childrenCount - index - 1);
    }
}

void IDPHumanSetParentWithNewValue(IDPHuman *human, IDPHuman *parent, IDPHuman *newParent) {
    if (IDPHumanGenderMale == IDPHumanGetGender(parent)) {
        IDPHumanSetFather(human, newParent);
    } else if (IDPHumanGenderFemale == IDPHumanGetGender(parent)){
        IDPHumanSetMother(human, newParent);
    }
}

void IDPHumanAppendChildrenWithChild(IDPHuman *human, IDPHuman *child) {
    IDPHumanSetChildAtIndex(human, child, IDPHumanGetChildrenCount(human));
}

void IDPHumanRemoveChildAtIndex(IDPHuman *human, size_t index) {
    IDPHumanSetChildAtIndex(human, NULL, index);
}

IDPHuman *IDPHumanGetChildAtIndex(IDPHuman *human, size_t index) {
    if (!human) {
        return NULL;
    }
    
    return human->_children[index];
}

void IDPHumanSetChildAtIndex(IDPHuman *human, IDPHuman *child, size_t index) {
    IDPObjectSetStrong(human, _children[index], child);
}

size_t IDPHumanGetChildIndex(IDPHuman *human, IDPHuman *child) {
    for(size_t index = 0; index < IDPHumanGetChildrenCount(human); index++) {
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
    
    uint64_t childrenCount = IDPHumanGetChildrenCount(human);
    
    uint64_t index = IDPHumanGetChildIndex(human, NULL);
    
    if (index != kIDPHumanIndexNotFound
        && !IDPHumanGetChildAtIndex(human, index)
        && IDPHumanGetChildAtIndex(human, childrenCount))
    {
        human->_children[index] = human->_children[childrenCount];
        human->_children[childrenCount] = NULL;
    }
}
