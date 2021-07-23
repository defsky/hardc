#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "global.h"
#include "game.h"

static int monster_attack(void* self, int damage)
{
    assert(self != NULL);

    Monster* monster = self;
    
    printf("You attack %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if(monster->hit_points > 0){
        printf("It is still alive.\n");
        return 0;
    } else {
        printf("It is dead!\n");
        return 1;
    }
}

static int monster_init(void* self)
{
    assert(self != NULL);

    Monster* monster = self;
    monster->hit_points = 10;
    return 1;
}

Object MonsterProto = {
    .init = monster_init,
    .attack = monster_attack
};

static void*   room_move(void* self, Direction direction)
{
    assert(self != NULL);

    Room* room = self;
    Room* next = NULL;

    switch(direction) {
        case NORTH:
            if (room->north){
                printf("You go north, into:\n");
                next = room->north;
            }
            break;
        case SOUTH:
            if (room->south) {
                printf("You go south, into:\n");
                next = room->south;
            }
            break;
        case WEST:
            if (room->west) {
                printf("You go west, into:\n");
                next = room->west;
            }
            break;
        case EAST:
            if (room->east) {
                printf("You go east, into:\n");
                next = room->east;
            }
            break;
        default:
            printf("You can not go that direction.");
            next = NULL;
    }

    if (next) {
        next->_(describe)(next);
    }

    return next;
}

static int     room_attack(void* self, int damage)
{
    assert(self != NULL);

    Room*       room = self;
    Monster*    monster = room->bad_guy;

    if (monster) {
        monster->_(attack)(monster, damage);
        return 1;
    } else {
        printf("You flail in the air at nothing. Idiot.\n");
        return 0;
    }
}

Object  RoomProto = {
    .move = room_move,
    .attack = room_attack
};

static void*   map_move(void* self, Direction direction)
{
    assert(self != NULL);

    Map*    map = self;
    Room*   location = map->location;
    Room*   next = NULL;

    next = location->_(move)(location, direction);

    if (next) {
        map->location = next;
    }

    return next;
}
static int     map_attack(void* self, int damage)
{
    assert(self != NULL);

    Map*    map = self;
    Room*   location = map->location;

    return location->_(attack)(location, damage);
}

static int     map_init(void* self)
{
    assert(self != NULL);

    Map*    map = self;

    Room*   hall = NEW(Room, "The great Hall");
    Room*   throne = NEW(Room, "The throne room");
    Room*   arena = NEW(Room, "The arena, with the minotaur");
    Room*   kitchen = NEW(Room, "Kitchen, you have the knife now");

    arena->bad_guy = NEW(Monster, "The evil minotaur");

    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;
    kitchen->west = throne;

    map->start = hall;
    map->location = hall;

    return 1;
}

Object MapProto = {
    .init = map_init,
    .move = map_move,
    .attack = map_attack
};

