#ifndef _object_h_
#define _object_h_

#include "global.h"

typedef struct {
    char*   description;
    int     (*init)(void* self);
    void    (*describe)(void* self);
    void    (*destroy)(void* self);
    void*   (*move)(void* self, Direction direction);
    int     (*attack)(void* self, int damage);
} Object;

void*   object_new(size_t size, Object proto, char* description);

#define NEW(T, N) object_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

#endif
