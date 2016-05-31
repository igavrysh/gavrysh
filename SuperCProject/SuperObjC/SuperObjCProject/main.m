//
//  main.m
//  SuperObjCProject
//
//  Created by Ievgen on 5/29/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "IDPCreature.h"
#import "IDPFemaleCreature.h"
#import "IDPMaleCreature.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        uint64_t count = 10;
        
        NSMutableArray *creatures = [[NSMutableArray alloc] init];
        
        for (uint64_t index = 0; index < count; index++) {
            IDPCreature *creature = nil;
            
            if (IDPCreatureGenderFemale == arc4random() % 2) {
                creature = [[IDPFemaleCreature alloc] initWithRandomAttributes];
            } else {
                creature = [[IDPMaleCreature alloc] initWithRandomAttributes];
            }
            
            [creature release];
        }
        
        for (IDPCreature *creature in creatures) {
            [creature performGenderSpecificOperation];
        }
        
        NSLog(@"--- All creatures are saying hi! ---");
        [creatures enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            [(IDPCreature *)obj sayHi];
        }];
        
        NSLog(@"--- All children are saying hi! ---");
        [creatures enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            [((IDPCreature *)obj).allChildren enumerateObjectsUsingBlock:^(id  _Nonnull obj2, NSUInteger idx, BOOL * _Nonnull stop) {
                [(IDPCreature *)obj2 sayHi];
            }];
        }];
        
        [creatures release];
    }
    return 0;
}
