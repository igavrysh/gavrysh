//
//  IDPHuman.h
//  SuperCProject
//
//  Created by Student 104 on 4/14/16.
//  Copyright (c) 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef __SuperCProject__IDPHuman__
#define __SuperCProject__IDPHuman__

#include <stdbool.h>

#include "IDPName.h"
#include "IDPPartner.h"
#include "IDPParents.h"
#include "IDPChildren.h"

#define IDP_HUMAN_MAX_CHILDREN_COUNT 20

typedef enum {
    IDPHumanSexMale     = 1 << 0,
    IDPHumanSexFemale   = 0
} IDPHumanSex;

typedef struct IDPHuman IDPHuman;

struct IDPHuman {
    IDPName *_name;
    
    int age;
    
    IDPHumanSex _sex;
    
    bool isMarried;
    IDPPartner *_partner;
    
    IDPParents *_parents;
    
    IDPChildren *_children;
};

#endif /* defined(__SuperCProject__IDPHuman__) */
