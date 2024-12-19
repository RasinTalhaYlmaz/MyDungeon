#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Room.h"

char *room_descriptions[] = {
    "A dark and gloomy room.",
    "A bright and shiny hall.",
    "An abandoned storage area.",
    "A dusty library filled with old books.",
    "A narrow corridor with torch-lit walls.",
    "A cavern with echoes of water drops.",
    "A mysterious chamber full of secrets.",
    "An ancient temple with stone carvings.",
    "A room with flickering shadows on the walls.",
    "A garden filled with poisonous plants."
};


Room *create_room(Item **items) {

    Room *room = malloc(sizeof(Room));
    if (!room) {
        printf("Failed to allocate memory for room.\n");
        return NULL;
    }

    room->description = strdup(room_descriptions[rand() % 10]);
    if (!room->description) {
        printf("Failed to allocate memory for room description.\n");
        free(room);
        return NULL;
    }

    room->num_items = rand() % 3 + 1;
    room->items = malloc(sizeof(Item *) * room->num_items);
    if (!room->items) {
        printf("Failed to allocate memory for room items.\n");
        free(room->description);
        free(room);
        return NULL;
    }

    for (int i = 0; i < room->num_items; i++) {
        room->items[i] = create_item();
        if (!room->items[i]) {
            printf("Failed to create item.\n");
            // Free already allocated items
            for (int j = 0; j < i; j++) {
                free(room->items[j]);
            }
            free(room->items);
            free(room->description);
            free(room);
            return NULL;
        }
    }

    room->creature = create_creature();
    if (!room->creature) {
        printf("Failed to create creature.\n");
        // Free already allocated items and room
        for (int i = 0; i < room->num_items; i++) {
            free(room->items[i]);
        }
        free(room->items);
        free(room->description);
        free(room);
        return NULL;
    }

    room->up = NULL;
    room->down = NULL;
    room->left = NULL;
    room->right = NULL;

    return room;
}

void connect_rooms(Room *r1, Room *r2, Directions d){
    if(!r1 || !r2){
        printf("Invalid rooms to connect. \n");
        return;
    }   

    switch(d) {
        case UP:
            if (r1->up == NULL) {
                r1->up = r2;
                r2->down = r1;
            }
            break;
        case DOWN:
            if (r1->down == NULL) {
                r1->down = r2;
                r2->up = r1;
            }
            break;
        case RIGHT:
            if (r1->right == NULL) {
                r1->right = r2;
                r2->left = r1;
            }
            break;
        case LEFT:
            if (r1->left == NULL) {
                r1->left = r2;
                r2->right = r1;
            }
            break;
        default:
            printf("Invalid direction. \n");
            break;
    }
}

void free_room(Room *room) {
    if (room) {
        if (room->description) {
            free(room->description);  
        }

        if (room->items) {
            for (int i = 0; i < room->num_items; i++) {
                free(room->items[i]); 
            }
            free(room->items); 
        }

        
        free(room); 
    }
}

void describe_room(Room *room) {
    if (room && room->description) {  
        printf("%s\n", room->description); 
    } else {
        printf("No room to describe.\n");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Oyunla ilgili diğer başlık dosyalarınız

Room *create_final_room(Item **items) {
    // Oda bellek tahsisi
    Room *room = malloc(sizeof(Room));
    if (!room) {
        printf("Failed to allocate memory for room.\n");
        return NULL;
    }

    // Oda açıklamasını ayarlama
    room->description = strdup("In this place there is an evil you can not even imagine! This place smells like death and decay. You must be very careful!");
    if (!room->description) {
        printf("Failed to allocate memory for room description.\n");
        free(room);
        return NULL;
    }

    // Rastgele eşya sayısı belirleme (en az 1, en fazla 3)
    room->num_items = rand() % 3 + 1;
    room->items = malloc(sizeof(Item *) * room->num_items);
    if (!room->items) {
        printf("Failed to allocate memory for room items.\n");
        free(room->description);
        free(room);
        return NULL;
    }

    // Eşyaları yaratma
    for (int i = 0; i < room->num_items; i++) {
        room->items[i] = create_item();
        if (!room->items[i]) {
            printf("Failed to create item.\n");
            // Daha önce ayrılan eşyaları serbest bırakma
            for (int j = 0; j < i; j++) {
                free(room->items[j]);
            }
            free(room->items);
            free(room->description);
            free(room);
            return NULL;
        }
    }

    // BALROG yaratığını oluşturma
    Creature *BALROG = malloc(sizeof(Creature));
    if (!BALROG) {
        printf("Failed to allocate memory for BALROG.\n");
        // Bellek sızıntısını önlemek için serbest bırakma işlemleri
        for (int i = 0; i < room->num_items; i++) {
            free(room->items[i]);
        }
        free(room->items);
        free(room->description);
        free(room);
        return NULL;
    }

    BALROG->name = "BALROG";
    BALROG->health = 666;
    BALROG->strength = 666;

    room->creature = BALROG;

    return room;
}
