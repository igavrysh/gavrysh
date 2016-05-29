//
//  IDPObjectMacros.h
//  SuperCProject
//
//  Created by Ievgen on 5/5/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPObjectMacros_h
#define IDPObjectMacros_h

#define IDPObjectAssign(object, field, value) \
    if (object) { \
        object->field = value; \
    } \

#define IDPObjectSetFieldValueWithMethod(object, field, value, retainMethod) \
    __IDPObjectSetFieldValueWithMethod((IDPObject *)object, (void **)&object->field, value, (void *(*)(void *))retainMethod)

#define IDPObjectSetStrong(object, field, value) \
    IDPObjectSetFieldValueWithMethod(object, field, value, IDPObjectRetain) \

#endif /* IDPObjectMacros_h */
