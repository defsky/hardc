#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "object.h"

static int object_init(void* self)
{
    assert(self != NULL);

    // do nothing really
 
    return 1;
}

static void object_destroy(void* self)
{
    Object* obj = self;

    if(obj){
        if(obj->description)
            free(obj->description);

        free(obj);
    }
}

static void object_describe(void* self)
{
    Object* obj = self;
    printf("%s.\n", obj->description);
}

static void* object_move(void* self, Direction direction)
{
    printf("You can not go that dirction.\n");
    return NULL;
}

static int object_attack(void* self, int damage)
{
    printf("You can not attack that.\n");
    return 0;
}


void* object_new(size_t size, Object proto, char* description)
{
    assert(description != NULL);
    assert(size >= sizeof(proto));

    // setup the default function in case they are not set
    
    if(!proto.init)
        proto.init = object_init;

    if(!proto.describe)
        proto.describe = object_describe;

    if(!proto.destroy)
        proto.destroy = object_destroy;

    if(!proto.attack)
        proto.attack = object_attack;
    
    if(!proto.move)
        proto.move = object_move;

    Object *el = calloc(1, size);

    assert(el != NULL);

    *el = proto;

    el->description = strdup(description);

    if(!el->init(el)){
        // looks like it did not initialize properly
        el->destroy(el);
        return NULL;
    }else{
        // all done
        return el;
    }
}
