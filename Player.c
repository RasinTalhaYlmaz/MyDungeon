#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Player.h"
#include "Creature.h"

Player *create_player(){
    Player *player = malloc(sizeof(Player));
    if(!player){
        printf("Failed to allocate memory. \n");
        return NULL;
    }
    player->health = 500;
    player->strength = 500;
    player->item_count = 0;

    for (int i = 0; i < 10; i++) {
        player->inventory[i] = NULL;
    }

    return player;
}