#ifndef GAME_COMMANDS_H
#define GAME_COMMANDS_H

#include "Player.h"
#include "Room.h"

void handle_move(Player *player, Room **currentRoom, Directions d);
void handle_look(Room *current_room);
void handle_inventory(Player *player);
void handle_pickup(Player *player, Room *current_room, const char *item_name);
void handle_attack(Player *player, Room *current_room);
void handle_stats(Player *player);
void handle_drop(Player *player, Room *currentRoom, const char *item_name);

#endif
