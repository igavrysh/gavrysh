//
//  IDPFemaleCreature.m
//  SuperCProject
//
//  Created by Ievgen on 5/31/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#import "IDPFemaleCreature.h"

@interface IDPFemaleCreature ()

- (IDPCreature *)giveBithToChildWithName:(NSString *)name;

- (IDPCreature *)giveBithToChildWithRandomName;

@end

@implementation IDPFemaleCreature

#pragma mark -
#pragma mark Public Methods

- (void)performGenderSpecificOperation {
    [self giveBirthAndAddToChildren];
}

- (void)giveBirthAndAddToChildren {
    [self addChild:[self giveBithToChildWithRandomName]];
}

#pragma mark -
#pragma mark Private Methods

- (IDPCreature *)giveBithToChildWithName:(NSString *)name {
    IDPCreatureGender gender = arc4random() % 2;
    double weight = 2 + arc4random() % 200 / 100.0;
    
    [self printCreatureMessage:[NSString stringWithFormat:@"I gave a birth to %@!!!", name]];
    
    return [[[IDPCreature alloc] initWithName:name gender:gender weight:weight age:0 children:nil] autorelease];
}

- (IDPCreature *)giveBithToChildWithRandomName {
    return [self giveBithToChildWithName:[IDPCreature randomName]];
}

@end
