//
//  main.c
//  SuperCProject
//
//  Created by Student 104 on 4/4/16.
//  Copyright (c) 2016 1milliondollarsstartup. All rights reserved.
//

#include "IDPPrintingFunctions.h"

int main(int argc, const char * argv[]) {
    ICPrintNewLine();
    IDPPrintTest("$1mln dollars start up");
    
    ICPrintGreatingToMama();
    ICPrintNewLineWithCount(2);
    
    ICPrintGreatingToPapa();
    ICPrintNewLineWithCount(3);
    
    return 0;
}
