#ifndef _ex19_h_
#define _ex19_h_

#include "object.h"

struct monster {
    Object  proto;
    int     hit_points;
};
typedef struct monster Monster;

struct room {
    Object      proto;
    Monster*    bad_guy;

    struct room*    north;
    struct room*    south;
    struct room*    east;
    struct room*    west;
};
typedef struct room Room;

struct map {
    Object  proto;
    Room*   start;
    Room*   location;
};
typedef struct map Map;

extern Object MapProto;
extern Object RoomProto;
extern Object MonsterProto;

#endif
