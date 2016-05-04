//
//  IDPObjectMacros.h
//  IDPSeptemberGroupCode
//
//  Created by Ievgen on 5/2/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPObjectMacros_h
#define IDPObjectMacros_h

#define IDPAssignSetter(object, ivar, newIvar) \
    if (NULL != object) { \
        object->ivar = newIvar; \
    } \

#define IDPRetainSetter(object, ivar, newIvar) \
    if (NULL != object && object->ivar != newIvar) { \
        IDPObjectRetain(newIvar); \
        IDPObjectRelease(object->ivar); \
        object->ivar = newIvar; \
    } \

#endif /* IDPObjectMacros_h */
