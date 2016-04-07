//
//  IDPGenericDefineList.h
//  SuperCProject
//
//  Created by Ievgen on 4/6/16.
//  Copyright © 2016 1milliondollarsstartup. All rights reserved.
//

#ifndef IDPGenericDefineList_h

#define IDPGenericDefineList_h

#include <stdio.h>
#include <stdbool.h>

#define define_list(type) \
\
struct _list_##type; \
\
typedef struct {\
    int (*is_empty)(const struct _list_##type*); \
    size_t (*size)(const struct _list_##type*); \
    const type (*front)(const struct _list_##type*); \
    void (*push_front)(struct _list_##type*, type); \
    type (*pop_front)(struct _list_##type*); \
} _list_functions_##type; \
\
typedef struct _list_elem_##type { \
    type _data; \
    struct _list_elem_##type* _next; \
} list_elem_##type; \
\
typedef struct _list_##type { \
    size_t _size; \
    list_elem_##type* _first; \
    list_elem_##type* _last; \
    _list_functions_##type* _functions; \
} List_##type; \
\
List_##type* new_list_##type(); \
\
bool list_is_empty_##type(const List_##type* list); \
\
size_t list_size_##type(const List_##type* list); \
\
const type list_front_##type(const List_##type* list); \
\
void list_push_front_##type(List_##type* list, type elem); \
\
bool list_is_empty_##type(const List_##type* list) { \
    return list->_size == 0; \
} \
\
size_t list_size_##type(const List_##type* list) { \
    return list->_size; \
} \
\
const type list_front_##type(const List_##type* list) { \
    return list->_first->_data; \
} \
\
void list_push_front_##type(List_##type *list, type elem) { \
    \
    list_elem_##type *new_list_elem = (list_elem_##type *) malloc(sizeof(list_elem_##type)); \
    new_list_elem->_data = elem; \
    new_list_elem->_next = list->_first; \
    list->_first = new_list_elem; \
    list->_size++; \
} \
\
type list_pop_front_##type(List_##type *list) { \
\
    if (list->_size == 0) { \
        return NULL; \
    } \
    list_elem_##type *list_elem_to_delete = list->_first; \
    list->_first = list->_first->_next; \
    list->_size--; \
    type poped_data = list_elem_to_delete->_data; \
    /*free(list_elem_to_delete);*/ \
    return poped_data; \
} \
\
_list_functions_##type _list_funcs_##type = { \
    &list_is_empty_##type, \
    &list_size_##type, \
    &list_front_##type, \
    &list_push_front_##type, \
    &list_pop_front_##type, \
}; \
\
List_##type* new_list_##type() { \
    List_##type* res = (List_##type*) malloc(sizeof(List_##type)); \
    res->_size = 0; \
    res->_first = NULL; \
    res->_functions = &_list_funcs_##type; \
    \
    return res; \
}

#define List(type) \
List_##type

#define new_list(type) \
new_list_##type()

#define is_empty(collection) \
collection->_functions->is_empty(collection)

#define size(collection) \
collection->_functions->size(collection)

#define front(collection) \
collection->_functions->front(collection)

#define push_front(collection, elem) \
collection->_functions->push_front(collection, elem)

#define pop_front(collection) \
collection->_functions->pop_front(collection)

typedef char* char_ptr;
typedef unsigned long ulong;

#endif /* IDPGenericDefineList_h */
