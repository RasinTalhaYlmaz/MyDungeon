#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gameCommands.h"

void handle_move(Player *player, Room **currentRoom, Directions d) {
    Room *nextRoom = NULL;  

    switch(d) {
        case UP:
            nextRoom = (*currentRoom)->up;
            break;
        case DOWN:
            nextRoom = (*currentRoom)->down;
            break;
        case RIGHT:
            nextRoom = (*currentRoom)->right;
            break;
        case LEFT:
            nextRoom = (*currentRoom)->left;
            break;
        default:
            printf("Invalid direction.\n");
            return;
    }

    if (nextRoom) {
        *currentRoom = nextRoom; 
        printf("You are going ");
        switch (d) {
            case UP:    printf("up.\n"); break;
            case DOWN:  printf("down.\n"); break;
            case LEFT:  printf("left.\n"); break;
            case RIGHT: printf("right.\n"); break;
        }
    } else {
        printf("You can't go that way.\n");
    }

    player->health += 50;
}



void handle_look(Room *current_room) {
    printf("Room description: %s\n", current_room->description);
    if (current_room->creature) {
        if (strcmp(current_room->creature->name, "BALROG") == 0) {
            printf("This creature is beyond you! THIS. IS. BALROG!!!\n");
            return;
        }
        printf("Creature: %s (Health: %d, Strength: %d)\n", current_room->creature->name, current_room->creature->health, current_room->creature->strength);
        
    }

    for (int i = 0; i < current_room->num_items; i++) {
        describe_item(current_room->items[i]);
    }
}

void handle_inventory(Player *player) {
    if(player->item_count == 0){
        printf("Your inventory is empty.\n");
        return;
    }
    printf("Your inventory contains:\n");
    for (int i = 0; i < player->item_count; i++) {
        describe_item(player->inventory[i]);
    }
}

void handle_pickup(Player *player, Room *current_room, const char *item_name) {
    for (int i = 0; i < current_room->num_items; i++) {
        if (strcmp(current_room->items[i]->name, item_name) == 0) {
            if (player->item_count < 3) {
                player->inventory[player->item_count++] = current_room->items[i];
                if(current_room->items[i]->isAttack){
                    player->strength += current_room->items[i]->a.damage;
                }
                else if(current_room->items[i]->isDefense){
                    player->health += current_room->items[i]->d.shield;
                }
                else{
                    player->health += current_room->items[i]->s.shield;
                    player->strength += current_room->items[i]->s.damage;
                }

                printf("You picked up the %s.\n", item_name);
                
                
                free(current_room->items[i]);  
                
                
                for (int j = i; j < current_room->num_items - 1; j++) {
                    current_room->items[j] = current_room->items[j + 1];
                }
                
                current_room->items[current_room->num_items - 1] = NULL;

            
                current_room->num_items--;
                return;
            } else {
                printf("Your inventory is full.\n");
                return;
            }
        }
    }
    printf("Item not found in the room.\n");
}


void handle_attack(Player *player, Room *current_room) {
    if (!current_room->creature) {
        printf("There's no creature here to attack.\n");
        return;
    }

    current_room->creature->health -= player->strength;
    if (current_room->creature->health <= 0) {
        printf("You defeated the %s!\n", current_room->creature->name);
        if(strcmp(current_room->creature->name, "BALROG") == 0){
            printf("You escaped from the dungeons!!! \n");
            printf("Congratulations! You have won the game.\n");
            exit(0);
        }
        free(current_room->creature); 
        current_room->creature = NULL;
    } else {
        printf("The %s has %d health remaining.\n", current_room->creature->name, current_room->creature->health);
        player->health -= current_room->creature->strength;
        printf("Your health: %d\n", player->health);
        if (player->health <= 0) {
            printf("You died. Game over.\n");
            exit(0);
        }
    }
}

void handle_stats(Player *player) {
    printf("Player Stats:\n");
    printf("Health: %d\n", player->health);
    printf("Damage: %d\n", player->strength);
}

void handle_drop(Player *player, Room *currentRoom, const char *item_name) {
    if (player->item_count == 0) {
        printf("Your inventory is empty. There's nothing to drop.\n");
        return;
    }

    int item = -1;
    for (int i = 0; i < player->item_count; i++) {
        if (strcmp(player->inventory[i]->name, item_name) == 0) {
            item = i;
            break;
        }
    }

    if (item == -1) {
        printf("Item '%s' not found in your inventory.\n", item_name);
        return;
    }

    if (currentRoom->num_items >= 3) {
        printf("The room is full. You can't drop any items here.\n");
        return;
    }


    Item *item_to_drop = player->inventory[item];

    printf("You dropped the %s.\n", item_name);

    if (item_to_drop->isAttack) {
        player->strength -= item_to_drop->a.damage;
    } else if (item_to_drop->isDefense) {
        player->health -= item_to_drop->d.shield;
    } else {
        player->health -= item_to_drop->s.shield;
        player->strength -= item_to_drop->s.damage;
    }

    currentRoom->items[currentRoom->num_items] = item_to_drop;
    currentRoom->num_items++;

    for (int i = item; i < player->item_count - 1; i++) {
        player->inventory[i] = player->inventory[i + 1];
    }
    player->inventory[player->item_count - 1] = NULL;
    player->item_count--;
}
