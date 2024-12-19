#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "Room.h"

typedef struct Player {
    int health;
    int strength;
    Item *inventory[3];
    int item_count;
}Player;

Player *create_player();

#endif