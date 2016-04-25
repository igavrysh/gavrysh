//
//  IDPName.h
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef __SuperCProject__IDPName__
#define __SuperCProject__IDPName__

#include "IDPObject.h"

typedef struct IDPString IDPString;

struct IDPString {
    IDPObject _super;
    
    char *_string;
};

extern
void __IDPStringDeallocate(IDPString *string);

extern
IDPString *IDPStringCreateWithString(char *string);

extern
IDPString *IDPStringCreateWithIDPString(IDPString *string);

extern
void IDPStringSetString(IDPString *string, char *value);

extern
void IDPStringCopy(IDPString *string, IDPString *newValue);

extern
char *IDPStringGetString(IDPString *string);

extern
size_t IDPStringGetLength(IDPString *string);

#endif /* defined(__SuperCProject__IDPName__) */
