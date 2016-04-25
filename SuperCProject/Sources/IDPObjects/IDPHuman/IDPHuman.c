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
void IDPHumanRemoveFromParent(IDPHuman *human);

static
void IDPHumanRemoveAllChildren(IDPHuman *human);

static
bool IDPHumanCanGiveBirth(IDPHuman *human);

static
void IDPHumanSetChildForAdd(IDPHuman *human, IDPHuman *child);

static
void IDPHumanSetChildForDelete(IDPHuman *human, IDPHuman *child);

static
void IDPHumanSetChildIsNull(IDPHuman *human, IDPHuman *child, bool IsNull);

static
void IDPHumanRemoveAllChildren(IDPHuman *human);

static
void IDPHumanInsertChildIntoArray(IDPHuman *human, IDPHuman *child);

static
void IDPHumanRemoveChildFromArray(IDPHuman *human, IDPHuman *child);

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
    
    IDPHumanRemoveFromParent(human);
    
    IDPHumanSetName(human, NULL);
    
    IDPHumanDivorce(human);
    
    __IDPObjectDeallocate(object);
}

void *IDPHumanCreate() {
    IDPHuman *result = IDPObjectCreateOfType(IDPHuman);
    
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
    IDPHumanSetPartner(partner, human);
}

size_t IDPHumanGetChildrenCount(IDPHuman *human) {
    if (!human) {
        return 0;
    }
    
    return human->_childrenCount;
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
    
    human->_childrenCount++;
}


void IDPHumanDecrementChildrenCount(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    human->_childrenCount--;
}


#pragma mark -
#pragma mark Private Implementations

void IDPHumanInit(IDPHuman *human) {
    for(uint8_t i = 0; i < kIDPHumanMaxChildrenCount; i++) {
        human->_children[i] = NULL;
    }
    
    IDPHumanSetChildrenCount(human, 0);
    
    IDPHumanSetAge(human, 0);
    
    IDPHumanSetGender(human, IDPHumanGenderMale);
    
    IDPHumanSetName(human, NULL);
    
    IDPHumanDivorce(human);
    
    human->_father = NULL;
    human->_mother = NULL;
}

#pragma mark -
#pragma mark Private Implementations - Set Partner functionality

void IDPHumanSetWeakPartner(IDPHuman *human, IDPHuman *partner) {
    if (!human) {
        return;
    }
    
    if (human->_partner != partner) {
        human->_partner = partner;
    }
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
    }
    else {
        IDPHumanSetWeakPartner(human, partner);
    }
}

IDPHuman *IDPHumanGetPartner(IDPHuman *human) {
    return human ? human->_partner : NULL;
}

#pragma mark - 
#pragma mark Private Implementations - Give Birth functionality

IDPHuman *IDPHumanGetBirthChild(IDPHuman *human) {
    if (!human) {
        return NULL;
    }
    
    if (!IDPHumanGetPartner(human) || !IDPHumanCanGiveBirth(human)) {
        return NULL;
    }
    
    IDPHuman *child = IDPHumanCreate();
    IDPHumanAddChild(human, child);
    IDPObjectRelease(child);
    
    return child;
}

bool IDPHumanCanGiveBirth(IDPHuman *human) {
    return IDPHumanGenderFemale == IDPHumanGetGender(human) && IDPHumanGetChildrenCount(human) < kIDPHumanMaxChildrenCount;
}

void IDPHumanAddChild(IDPHuman *human, IDPHuman *child) {
    if (!human || !child) {
        return;
    }
    
    if (human != child) {
        IDPHuman *partner = IDPHumanGetPartner(human);
        IDPHumanSetChildForAdd(human, child);
        IDPHumanSetChildForAdd(partner, child);
    }
}

void IDPHumanRemoveFromParent(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    IDPHumanSetChildForDelete(human->_father, human);
    IDPHumanSetChildForDelete(human->_mother, human);
}

void IDPHumanRemoveAllChildren(IDPHuman *human) {
    if (!human) {
        return;
    }
    
    size_t childrenCount = IDPHumanGetChildrenCount(human);
    for (size_t index; index < childrenCount; index++) {
        IDPHumanSetChildForDelete(human, IDPHumanGetChildAtIndex(human, childrenCount - index - 1));
    }
}


void IDPHumanSetChildForAdd(IDPHuman *human, IDPHuman *child) {
    IDPHumanSetChildIsNull(human, child, false);
}

void IDPHumanSetChildForDelete(IDPHuman *human, IDPHuman *child) {
    IDPHumanSetChildIsNull(human, child, true);
}

void IDPHumanSetChildIsNull(IDPHuman *human, IDPHuman *child, bool isNull) {
    if (!human) {
        return;
    }
    
    if (IDPHumanGenderMale == IDPHumanGetGender(human)) {
        child->_father = !isNull ? human : NULL;
    } else {
        child->_mother = !isNull ? human : NULL;
    }
    
    if (!isNull) {
        IDPObjectRetain(child);
        IDPHumanInsertChildIntoArray(human, child);
    } else {
        IDPHumanRemoveChildFromArray(human, child);
        IDPObjectRelease(child);
    }
}

void IDPHumanInsertChildIntoArray(IDPHuman *human, IDPHuman *child) {
    IDPHumanSetChildAtIndex(human, child, IDPHumanGetChildrenCount(human));
}

void IDPHumanRemoveChildFromArray(IDPHuman *human, IDPHuman *child) {
    if (!human || !child || human == child) {
        return;
    }
    
    size_t index = IDPHumanGetChildIndex(human, child);
    if (index != kIDPHumanIndexNotFount) {
        IDPHumanSetChildAtIndex(human, NULL, index);
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
    
    IDPHuman *currentChild = IDPHumanGetChildAtIndex(human, index);
    if (!currentChild && child) {
        IDPHumanIncrementChildrenCount(human);
    } else if (currentChild && !child) {
        IDPHumanDecrementChildrenCount(human);
    }
    
    human->_children[index] = child;
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
    
    size_t internalIndex = 0;
    
    size_t childrenCount = IDPHumanGetChildrenCount(human);
    for (size_t index = 0; index < childrenCount; index++) {
        while (!IDPHumanGetChildAtIndex(human, internalIndex)
               && internalIndex < childrenCount) {
            internalIndex++;
        }
    
        human->_children[index] = human->_children[internalIndex];
        
        internalIndex++;
    }
}
