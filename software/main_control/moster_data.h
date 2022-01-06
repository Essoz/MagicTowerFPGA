
/* This file stores the moster attributes */

#ifndef MOSTER_DATA_H
#define MOSTER_DATA_H
#include "alt_types.h"

typedef struct Moster_Attributes
{
    int Monster_Health;
    int Monster_Attack;
    int Monster_Defense;
    int Monster_Energy_Bar;
    int Monster_Attack_Per_Round;
    int EXP_Gained;
    int Coin_Gained;
    int Special;
} Moster_Attributes;

// Each Moster Type
const Moster_Attributes Green_Slime           = {35, 19, 2, 25, 1, 1, 0, 0};
const Moster_Attributes Red_Slime             = {45, 23, 3, 25, 1, 1, 1, 0};
const Moster_Attributes Bat                   = {35, 30, 3, 27, 1, 1, 2, 0};
const Moster_Attributes Magician              = {50, 18, 4, 35, 1, 1, 3, 1};
const Moster_Attributes Skeleton              = {70, 80, 0, 40, 1, 1, 5, 0};
const Moster_Attributes Guard                 = {20, 50, 36, 33, 1, 1, 4, 0};
const Moster_Attributes Magician_Lightning    = {160, 30, 37, 60, 1, 2, 10, 1};
const Moster_Attributes Slime_Man             = {176, 98, 66, 31, 1, 2, 12, 3};

// The overall Moster List in Tower
const Moster_Attributes* Moster_List[8] = {
		&Green_Slime, &Red_Slime, &Bat, &Magician, &Skeleton, &Guard,
		&Magician_Lightning, &Slime_Man
};

#endif // !MOSTER_DATA_H
