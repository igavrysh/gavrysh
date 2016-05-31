//
//  IDPMaleCreature.m
//  SuperCProject
//
//  Created by Ievgen on 5/31/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#import "IDPMaleCreature.h"

@implementation IDPMaleCreature

#pragma mark -
#pragma mark Public Methods

- (void)performGenderSpecificOperation {
    [self goToWar];
}

- (void)goToWar {
    if (IDPCreatureGenderMale == self.gender) {
        [self printCreatureMessage:@"I am going to war!"];
    }
}


@end
