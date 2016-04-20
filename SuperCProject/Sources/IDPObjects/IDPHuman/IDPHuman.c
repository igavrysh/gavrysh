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

#pragma mark -
#pragma mark Public Implementations

void *IDPHumanCreate() {
    IDPHuman *result = IDPObjectCreateOfType(IDPHuman);
    
    return result;
}

void __IDPHumanDeallocate(IDPHuman *object) {
    IDPHuman *human = (IDPHuman *)object;
    
    IDPHumanSetName(human, NULL);

    IDPHumanSetPartner(human, NULL);
    
    __IDPObjectDeallocate(object);
}

void IDPHumanSetName(IDPHuman *human, IDPString *name) {
    if(NULL == human) {
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
    if (NULL == human) {
        return;
    }
    
    human->_gender = gender;
}

IDPString *IDPHumanGetName(IDPHuman *human) {
    if (NULL == human) {
        return NULL;
    }
    
    return human->_name;
}

uint8_t IDPHumanGetAge(IDPHuman *human) {
    if (NULL == human) {
        return 0;
    }
    
    return human->_age;
}

IDPHumanGender IDPHumanGetGender(IDPHuman *human) {
    return human->_gender;
}

bool IDPHumanIsMarried(IDPHuman *human) {
    return (NULL != human && NULL != human->_partner);
}

void IDPHumanSetPartner(IDPHuman *human, IDPHuman *partner) {
    if (NULL == human)  {
        return;
    }
    
    if (human->_gender == IDPHumanGenderMale) {
        if (human != partner) {
            if (partner == NULL || IDPHumanIsMarriageWithPartnerValid(human, partner)) {
                if (human->_partner != NULL) {
                    human->_partner->_partner = NULL;
                    IDPObjectRelease(human->_partner);
                }
                
                human->_partner = IDPObjectRetain(partner);
                
                if (partner != NULL) {
                    partner->_partner = human;
                }
            }
        }
        
    } else if (human ->_gender == IDPHumanGenderFemale) {
        if (human != partner) {
            if(partner == NULL || IDPHumanIsMarriageWithPartnerValid(human, partner)) {
                 if (human->_partner != NULL) {
                    IDPObjectRelease(human->_partner->_partner);
                    human->_partner->_partner = NULL;
                }
                
                human->_partner = partner;
                
                if(partner == NULL) {
                    return;
                }
                
                if(partner->_partner != NULL) {
                    IDPObjectRelease(partner->_partner);
                }
            
                partner->_partner = IDPObjectRetain(human);
            }
        }
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

void IDPHumanGiveBirth(void *object) {
    IDPHuman *human = (IDPHuman *)object;
    
    if (NULL != human || (IDPHumanGenderMale == human->_gender &&  NULL == human->_partner)) {
        return;
    }
    
    if (IDPHumanGenderMale == human->_gender) {
        IDPHumanGiveBirth(human->_partner);
    }

}

#pragma mark -
#pragma mark Private Implementations

bool IDPHumanIsMarriageWithPartnerValid(IDPHuman *human,  IDPHuman *partner) {
    return (NULL != human
        &&  NULL != partner
        && ((IDPHumanGenderFemale == human->_gender
        &&   IDPHumanGenderMale == partner->_gender)
        ||  (IDPHumanGenderFemale == partner->_gender
        &&   IDPHumanGenderMale == human->_gender)));
}

