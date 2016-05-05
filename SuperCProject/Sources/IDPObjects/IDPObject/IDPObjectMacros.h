//
//  IDPObjectMacros.h
//  SuperCProject
//
//  Created by Ievgen on 5/5/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

#ifndef IDPObjectMacros_h
#define IDPObjectMacros_h

#define IDPObjectSetFieldValueWithMethod(object, field, value, retainMethod) \
    __IDPObjectSetFieldValueWithMethod((IDPObject *)object, (void **)&object->field, value, retainMethod)


#define IDPObjectSetStrong(object, field, value) \
    IDPObjectSetFieldValueWithMethod(object, field, value, IDPObjectRetain) \

#endif /* IDPObjectMacros_h */
