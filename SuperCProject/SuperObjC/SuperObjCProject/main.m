//
//  main.m
//  SuperObjCProject
//
//  Created by Ievgen on 5/29/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "IDPCreature.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        uint64_t count = 10;
        
        NSMutableArray *people = [[NSMutableArray alloc] init];
        
        for (uint64_t index = 0; index < count; index++) {
            IDPCreature *creature = [[IDPCreature alloc] initWithRandomAttributes];
            
            [people addObject:creature];
            
            uint64_t childrenCount = arc4random() % 10;
            
            for (uint64_t childIndex; childIndex < childrenCount; childIndex++) {
                IDPCreature *child = [creature giveBithToChildWithRandomName];
                [creature addChild:child];
            }
            
            [creature release];
        }
        
        [people enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            IDPCreature *creature = (IDPCreature *)obj;
            
            if (IDPCreatureGenderMale == creature.gender) {
                [creature goToWar];
            } else {
                IDPCreature *child = [creature giveBithToChildWithRandomName];
                [creature addChild:child];
            }
        }];
        
        NSLog(@"--- All creatures are saying hi! ---");
        [people enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            [(IDPCreature *)obj sayHi];
        }];
        
        NSLog(@"--- All children are saying hi! ---");
        [people enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            [((IDPCreature *)obj).allChildren enumerateObjectsUsingBlock:^(id  _Nonnull obj2, NSUInteger idx, BOOL * _Nonnull stop) {
                [(IDPCreature *)obj2 sayHi];
            }];
        }];
        
        [people release];
    }
    return 0;
}
