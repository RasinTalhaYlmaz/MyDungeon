#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Player.h"
#include "Item.h"

char *attackItemNames[4] = {"Sword", "Spear", "Shuriken", "Axe"};
char *defenseItemNames[4] = {"Shield", "Potion", "Vest", "Helmet"};
char *specialItemNames[4] = {"Pan", "Claws", "Mithril", "StuddedShield"};


Item *create_item() {
    Item *item = malloc(sizeof(Item));
    if (!item) {
        printf("Failed to allocate memory for item.\n");
        return NULL;
    }

    int type = rand() % 2 + 1; // 1: Attack, 2: Defense

    switch (type) {
        case 1: // Attack Item
            item->a.damage = rand() % 30 + 21;
            item->name = strdup(attackItemNames[rand() % 4]);
            if (!item->name) {
                printf("Failed to allocate memory for item name.\n");
                free(item);
                return NULL;
            }
            item->isAttack = true;
            item->isDefense = false;
            break;

        case 2: // Defense Item
            item->d.shield = rand() % 30 + 21;
            item->name = strdup(defenseItemNames[rand() % 4]);
            if (!item->name) {
                printf("Failed to allocate memory for item name.\n");
                free(item);
                return NULL;
            }
            item->isAttack = false;
            item->isDefense = true;
            break;
    }
    return item;
}

SpecialItem *create_special_item(Player *player) {
    SpecialItem *item = malloc(sizeof(SpecialItem));
    if (!item || !player) {
        printf("Failed to allocate memory for special item or player.\n");
        return NULL;
    }

    item->name = strdup(specialItemNames[rand() % 4]);
    if (!item->name) {
        printf("Failed to allocate memory for special item name.\n");
        free(item);
        return NULL;
    }

    item->isSpecial = true;
    item->damage = 0; 

    if (strcmp(item->name, "Pan") == 0) {
        item->damage = player->strength * 3;
    } else if (strcmp(item->name, "Adamantium Claws") == 0) {
        item->damage = 25;
        player->health += player->strength + item->damage;
    } else if (strcmp(item->name, "Mithril") == 0) {
        item->shield = player->health * 2;
    } else if (strcmp(item->name, "Studded Shield") == 0) {
        item->shield = 50;
        item->damage = 10;
    }

    return item;
}

void describe_item(Item *item) {
    if (!item) {
        printf("No item to describe.\n");
        return;
    }

    printf("ITEM DETAILS --->");
    if (item->isAttack) {
        printf("Name: %s, Type: Attack, Damage: %d\n", item->name, item->a.damage);
    } else if (item->isDefense) {
        printf("Name: %s, Type: Defense, Shield: %d\n", item->name, item->d.shield);
    }
}

void describe_special_item(SpecialItem *item) {
    if (!item) {
        printf("No special item to describe.\n");
        return;
    }

    printf("SPECIAL ITEM DETAILS\n");
    printf("Name: %s, ", item->name);

    if (strcmp(item->name, "Pan") == 0) {
        printf("Effect: This magical pan triples your strength!\n");
    } else if (strcmp(item->name, "Adamantium Claws") == 0) {
        printf("Effect: These claws heal you for as much damage as you deal!\n");
    } else if (strcmp(item->name, "Mithril") == 0) {
        printf("Effect: This mithril doubles your health!\n");
    } else if (strcmp(item->name, "Studded Shield") == 0) {
        printf("Effect: This shield increases both damage and protection!\n");
    }
}
