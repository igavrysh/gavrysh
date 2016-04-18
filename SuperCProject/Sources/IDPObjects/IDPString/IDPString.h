//
//  IDPName.h
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef __SuperCProject__IDPName__
#define __SuperCProject__IDPName__

#include <stdio.h>

#include "IDPObject.h"

typedef struct IDPString IDPString;

struct IDPString {
    IDPObject _super;
    
    char *_string;
};

extern
void *IDPStringCreateWithString(char *string);

extern
void __IDPStringDeallocate(void *object);

extern
void IDPStringSetString(void *object, char *value);

extern
void IDPStringSetIDPString(void *object, void *string);

extern
char *IDPStringGetString(void *object);

extern
size_t IDPStringGetLength(void *object);

#endif /* defined(__SuperCProject__IDPName__) */
