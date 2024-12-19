#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Creature.h"

char *creatureNames[4] = {"Orc", "Goblin", "Spider", "Troll"};

Creature *create_creature(){
    Creature *creature = malloc(sizeof(Creature));
    if(!creature){
        printf("Failed to allocate memory for creature. \n");
        return NULL;
    }

    creature->name = strdup(creatureNames[rand() % 4]);

    if (strcmp(creature->name, "Troll") == 0) {
        creature->health = rand() % 100 + 150; 
        creature->strength = rand() % 50 + 21;
    }
    else {
        creature->health = rand() % 50 + 50;
        creature->strength = rand() % 20 +30;
    }

    return creature;
}