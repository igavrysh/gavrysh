//
//  main.c
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#include <stdio.h>

#include "IDPApplication.h"
#include "IDPAutoreleasingPool.h"

int main(int argc, const char * argv[]) {
    //IDPAutoreleasingPoolCreate();
    
    IDPRunApplication();
    
    //IDPAutoreleasingPoolDrain();
    
    return 0;
}
