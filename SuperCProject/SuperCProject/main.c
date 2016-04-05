//
//  main.c
//  SuperCProject
//
//  Created by Student 104 on 4/4/16.
//  Copyright (c) 2016 1milliondollarsstartup. All rights reserved.
//

#include "IDPPrintingFunctions.h"

int main(int argc, const char * argv[]) {
    IDPPrint();
    IDPPrintTest("$1mln dollars start up");
    
    ICParents();
    ICPrintNewLineWithCount(2);
    
    ICParents();
    ICPrintNewLineWithCount(3);
    
    return 0;
}
