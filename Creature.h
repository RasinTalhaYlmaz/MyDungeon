#ifndef CREATURE_H
#define CREATURE_H

typedef struct Creature{
    char *name;
    int health;
    int strength;
}Creature;

Creature *create_creature();
#endif