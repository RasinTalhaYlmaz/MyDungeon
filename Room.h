#ifndef ROOM_H
#define ROOM_H

#include "Item.h"
#include "Creature.h"

typedef enum Directions {UP,DOWN,RIGHT,LEFT} Directions;

typedef struct Room{
    char *description;
    int visited;
    Item **items;
    int num_items;
    Creature *creature;
    struct Room *up, *down, *left, *right;
}Room;

Room *create_room(Item **items);
void connect_rooms(Room *r1, Room *r2, Directions d);
void free_room(Room *room);
void describe_room(Room *room);
Room *create_final_room(Item **items);


#endif