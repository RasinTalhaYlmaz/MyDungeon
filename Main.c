#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "GameCommands.h"


void parse_command(char *command, Player *player, Room **currentRoom) {
    char arg[100];

    if (strcmp(command, "move") == 0) {
        printf("Which direction? (up, down, left, right): ");
        char direction[10];
        fgets(direction, sizeof(direction), stdin);
        direction[strcspn(direction, "\n")] = 0;

        Directions d;
        if (strcmp(direction, "up") == 0) d = UP;
        else if (strcmp(direction, "down") == 0) d = DOWN;
        else if (strcmp(direction, "left") == 0) d = LEFT;
        else if (strcmp(direction, "right") == 0) d = RIGHT;
        else {
            printf("Invalid direction.\n");
            return;
        }

        handle_move(player, currentRoom, d);
    } else if (strcmp(command, "look") == 0) {
        handle_look(*currentRoom);
    } else if (strcmp(command, "inventory") == 0) {
        handle_inventory(player);
    } else if (strcmp(command, "pickup") == 0) {
        printf("Enter the item name: ");
        char item_name[10];
        fgets(item_name, sizeof(item_name), stdin);
        item_name[strcspn(item_name, "\n")] = 0;
        handle_pickup(player, *currentRoom, item_name);
    } else if (strcmp(command, "attack") == 0) {
        handle_attack(player, *currentRoom); 
    } else if (strcmp(command, "exit") == 0) {
        exit(0);
    } else if (strcmp(command, "stats") == 0) {
        handle_stats(player);  
    } else if (strcmp(command, "drop") == 0) {
    printf("Which item would you like to drop? ");
    char item_name[50];
    fgets(item_name, sizeof(item_name), stdin);
    item_name[strcspn(item_name, "\n")] = 0;

    handle_drop(player, *currentRoom, item_name);
    } else {
        printf("Unknown command.\n");
    }
}

int main() {
    srand(time(NULL)); 
    
    Player *player = create_player();
    Room *currentRoom = create_room(NULL);
    Room *r2 = create_room(NULL);
    Room *r3 = create_room(NULL);
    Room *r4 = create_room(NULL);
    Room *r5 = create_room(NULL);
    Room *final = create_final_room(NULL);

    connect_rooms(currentRoom, r2, RIGHT);
    connect_rooms(r2, r3, UP);
    connect_rooms(r3, r4, LEFT);
    connect_rooms(r4, r5, UP);
    connect_rooms(r5, final, RIGHT);

    if (!player || !currentRoom) {
        printf("Failed to initialize game.\n");
        return EXIT_FAILURE;
    }

    char command[100];
    printf("You just woke up and you have no idea where the hell are you.\n");
    printf("While you walking around, you noticed that you are in a dungeon.\n");
    printf("You have to find a way to escape from this place.\n");
    printf("More you wait, more you will be in danger.\n \n");
    printf("Type a command to start. Type 'exit' to quit.\n(Commands: move, look, inventory, pickup, drop, attack, stats, list, save, load)\n");
    printf("Your health: %d, Strength: %d\n", player->health, player->strength);
    printf("What will you do? ");

    while (1) {
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        parse_command(command, player, &currentRoom);
        
        if (strcmp(command, "exit") == 0) {
            break; 
        }
    }

    free_room(currentRoom);
    free(player);

    return 0;
}
