//
//  IDPCreature.m
//  SuperCProject
//
//  Created by Ievgen on 5/29/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#import "IDPCreature.h"

@interface IDPCreature ()

@property (atomic, retain) NSMutableArray *children;

- (void)printCreatureMessage:(NSString *)message;

@end

@implementation IDPCreature

static NSString *firstNames[] = {
    @"Tran", @"Lenore", @"Bud", @"Fredda", @"Katrice",
    @"Clyde", @"Hildegard", @"Vernell", @"Nellie", @"Rupert",
    @"Billie", @"Tamica", @"Crystle", @"Kandi", @"Caridad",
    @"Vanetta", @"Taylor", @"Pinkie", @"Ben", @"Rosanna",
    @"Eufemia", @"Britteny", @"Ramon", @"Jacque", @"Telma",
    @"Colton", @"Monte", @"Pam", @"Tracy", @"Tresa",
    @"Willard", @"Mireille", @"Roma", @"Elise", @"Trang",
    @"Ty", @"Pierre", @"Floyd", @"Savanna", @"Arvilla",
    @"Whitney", @"Denver", @"Norbert", @"Meghan", @"Tandra",
    @"Jenise", @"Brent", @"Elenor", @"Sha", @"Jessie"
};

static NSString *lastNames[] = {
    
    @"Farrah", @"Laviolette", @"Heal", @"Sechrest", @"Roots",
    @"Homan", @"Starns", @"Oldham", @"Yocum", @"Mancia",
    @"Prill", @"Lush", @"Piedra", @"Castenada", @"Warnock",
    @"Vanderlinden", @"Simms", @"Gilroy", @"Brann", @"Bodden",
    @"Lenz", @"Gildersleeve", @"Wimbish", @"Bello", @"Beachy",
    @"Jurado", @"William", @"Beaupre", @"Dyal", @"Doiron",
    @"Plourde", @"Bator", @"Krause", @"Odriscoll", @"Corby",
    @"Waltman", @"Michaud", @"Kobayashi", @"Sherrick", @"Woolfolk",
    @"Holladay", @"Hornback", @"Moler", @"Bowles", @"Libbey",
    @"Spano", @"Folson", @"Arguelles", @"Burke", @"Rook"
};

static int namesCount = 50;

@dynamic allChildren;

#pragma mark -
#pragma mark Class Methods

+ (id)creature {
    return [[[self alloc] init] autorelease];
}

+ (NSString *)randomName {
    return [NSString stringWithFormat:@"%@ %@", firstNames[arc4random() % namesCount], lastNames[arc4random() % namesCount]];
}

#pragma mark -
#pragma mark Initializtions and Deallocations

- (void)dealloc {
    [self setName:nil];
    [self setChildren:nil];
    
    [super dealloc];
}

- (id)initWithName:(NSString *)name
            gender:(IDPCreatureGender)gender
            weight:(float)weight
               age:(uint8_t)age
          children:(NSArray *)children
{
    self = [super init];
    if (self) {
        [self setName:name];
        [self setGender:gender];
        [self setWeight:weight];
        [self setAge:age];
    }
    
    return self;
}

- (id)init {
    return [self initWithName:nil gender:IDPCreatureGenderUndefined weight:0 age:0 children:nil];
}

- (id)initWithRandomAttributes {
    return [self initWithName:[IDPCreature randomName]
                       gender:arc4random() % 2
                       weight:0.1 + arc4random() % 200 + arc4random() % 10 / 10.0
                          age:arc4random() % 122
                     children:nil];
}

#pragma mark -
#pragma mark Accessors Methods

- (NSArray *)allChildren {
    return [[_children mutableCopy] autorelease];
}

#pragma mark -
#pragma mark Public Methods

- (void)sayHi {
    [self printCreatureMessage:@"Hi"];
    
    [self.allChildren enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        [(IDPCreature *)obj sayHi];
    }];
}

- (void)performGenderSpecificOperation {
    
}

- (void)addChild:(IDPCreature *)child {
    if (nil == self.children) {
        [self setChildren:[[[NSMutableArray alloc] init] autorelease]];
    }
    
    [self.children addObject:child];
}

- (void)removeChild:(IDPCreature *)child {
    // TODO: Check for removing null object...
    [self.children removeObject:child];
}

#pragma mark -
#pragma mark Private Methods

- (void)printCreatureMessage:(NSString *)message {
    NSLog(@"Creature %@(%@) says %@!", self.name, self, message);
}

@end
