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

typedef struct IDPName IDPName;

struct IDPName {
    IDPObject _super;
    
    char *name;
    char *nameSize;
};

extern
void *IDPNameCreateWithString(char *name);

extern
void __IDPNameDeallocate(void *object);

extern
void IDPNameSetName(void *object, char *name);

extern
void IDPNameDeepCopy(void *object, IDPName *name);

extern
char *IDPNameGetName(void *object);

#endif /* defined(__SuperCProject__IDPName__) */
