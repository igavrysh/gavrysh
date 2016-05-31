//
//  IDPCreature.h
//  SuperCProject
//
//  Created by Ievgen on 5/29/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    IDPCreatureGenderMale,
    IDPCreatureGenderFemale,
    IDPCreatureGenderUndefined
} IDPCreatureGender;

@interface IDPCreature : NSObject {
    NSString *_name;
    
    double _weight;
    
    uint8_t _age;
    
    @protected
    NSMutableArray *_children;
}

@property (nonatomic, assign) IDPCreatureGender gender;

@property (atomic, copy) NSString *name;

@property (nonatomic, assign) double weight;

@property (nonatomic, assign) uint8_t age;

@property (atomic, copy, readonly) NSArray *allChildren;

+ (id)creature;
+ (NSString *)randomName;

- (id)initWithRandomAttributes;

- (void)sayHi;

- (void)performGenderSpecificOperation;

- (void)addChild:(IDPCreature *)child;

- (void)removeChild:(IDPCreature *)child;

@end
