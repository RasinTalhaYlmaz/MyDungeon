#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

typedef struct AttackItem{
    int damage;
}AttackItem;

typedef struct DefenseItem{
    int shield;
}DefenseItem;

typedef struct SpecialItem{
    char *name;
    int damage;
    int shield;
    bool isSpecial;
}SpecialItem;

typedef struct Item{
    char *name;
    AttackItem a;
    DefenseItem d;
    SpecialItem s;
    bool isAttack;
    bool isDefense; 
}Item;

Item *create_item();
SpecialItem *create_special_item();
void describe_item(Item *item);
void describe_special_item(SpecialItem *item);

#endif