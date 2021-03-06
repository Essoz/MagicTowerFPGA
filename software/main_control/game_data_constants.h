
/* This file stores the bitmap constants of the floor */

#ifndef GAME_DATA_CONSTANTS_H
#define GAME_DATA_CONSTANTS_H
#include "alt_types.h"

#define PLAYER_STATUS_TYPE  10
#define TOT_FLOOR_NUMBER    4
#define FLOOR_SIZE          121

#define Status  0
#define Health  1
#define Attack  2
#define Defense 3
#define EXP     4
#define Yellow_Key      5
#define Blue_Key        6
#define Red_Key         7
#define Coin            8
#define Special_Items   9
/* Player_Status_Init
    Player Status Data for initialization
    The sequence is: {Status, Health, Attack, Defense, EXP, Yellow_Key, Blue_Key, Red_Key, Coin, Special_Items}
 */
const alt_u16 Player_Status_Init[PLAYER_STATUS_TYPE] = {
    0, 1000, 10, 10, 0, 5, 1, 1, 0, 0
};

#define ROAD            0
#define DIRT            1
#define BRICK           2
#define STAR            3
#define VOID            4
#define UPSTAIRS        5
#define DOWNSTAIRS      6
#define YELLOW_DOOR     7
#define BLUE_DOOR       8
#define RED_DOOR        9
#define YELLOW_KEY      10
#define BLUE_KEY        11
#define RED_KEY         12
#define RED_GEM         13
#define BLUE_GEM        14
#define GREEN_GEM       15
#define RED_POTION      16
#define BLUE_POTION     17
#define GREEN_POTION    18
#define GREEN_SLIME1    19
#define RED_SLIME1      20
#define BAT1            21
#define MAGICIAN1       22
#define SKELETON1       23
#define GUARD1          24
#define MAGICIAN_LIGHTNING1 25
#define BIG_SLIME1      26
#define SLIME_MAN1      27

// Floor Configuration for initialization
const alt_u16 Floor_Configuration_Init[TOT_FLOOR_NUMBER][FLOOR_SIZE] = {
    {
        STAR, VOID, VOID, STAR, ROAD, UPSTAIRS, STAR, BRICK, VOID, STAR, VOID,
        STAR, VOID, RED_POTION, GREEN_SLIME1, ROAD, STAR, BRICK, GUARD1, BRICK, VOID, VOID,
        VOID, VOID, DIRT, BRICK, ROAD, ROAD, STAR, ROAD, ROAD, DIRT, STAR,
        STAR, VOID, STAR, VOID, ROAD, ROAD, ROAD, ROAD, STAR, ROAD, STAR,
        BRICK, VOID, BRICK, STAR, VOID, ROAD, DIRT, STAR, STAR, VOID, VOID,
        STAR, VOID, STAR, DIRT, VOID, ROAD, ROAD, VOID, VOID, VOID, BRICK,
        VOID, VOID, ROAD, DIRT, STAR, ROAD, VOID, VOID, BRICK, VOID, STAR,
        VOID, BRICK, VOID, ROAD, DIRT, ROAD, STAR, VOID, VOID, VOID, VOID,
        VOID, VOID, STAR, ROAD, ROAD, ROAD, VOID, VOID, VOID, VOID, VOID,
        VOID, VOID, VOID, STAR, VOID, ROAD, VOID, VOID, VOID, VOID, VOID,
        STAR, VOID, BRICK, VOID, STAR, ROAD, STAR, VOID, VOID, VOID, VOID
    },
    {
        YELLOW_KEY, BLUE_GEM, ROAD, RED_SLIME1, BRICK, DOWNSTAIRS, BRICK, BRICK, VOID, VOID, DIRT,
        BLUE_POTION, ROAD, BRICK, BAT1, BRICK, ROAD, BRICK, BRICK, BRICK, VOID, VOID,
        YELLOW_KEY, ROAD, BRICK, RED_SLIME1, BRICK, ROAD, DIRT, ROAD, GREEN_SLIME1, BLUE_GEM, STAR,
        RED_GEM, GREEN_SLIME1, BRICK, DIRT, BRICK, ROAD, ROAD, ROAD, RED_SLIME1, GREEN_SLIME1, RED_GEM,
        BRICK, BLUE_KEY, BRICK, ROAD, BRICK, ROAD, ROAD, BRICK, STAR, VOID, STAR,
        BRICK, BRICK, BRICK, ROAD, ROAD, ROAD, ROAD, VOID, VOID, VOID, BRICK,
        BRICK, BRICK, BRICK, BRICK, BRICK, BLUE_DOOR, VOID, VOID, BRICK, BLUE_POTION, YELLOW_KEY, 
        BRICK, ROAD, ROAD, ROAD, BRICK, DIRT, STAR, VOID, ROAD, ROAD, BRICK,
        BRICK, ROAD, BRICK, ROAD, BRICK, ROAD, RED_SLIME1, MAGICIAN_LIGHTNING1, SLIME_MAN1, ROAD, RED_GEM,
        BRICK, BAT1, BRICK, ROAD, BRICK, ROAD, VOID, VOID, STAR, RED_KEY, VOID,
        BRICK, UPSTAIRS, BRICK, ROAD, ROAD, ROAD, STAR, VOID, VOID, VOID, STAR
    },
    {
        UPSTAIRS, BAT1, BLUE_DOOR, MAGICIAN1, BRICK, BLUE_POTION, BLUE_GEM, BLUE_POTION, BLUE_GEM, BLUE_GEM, DIRT,
        BLUE_GEM, RED_GEM, BRICK, ROAD, BRICK, RED_SLIME1, BAT1, RED_SLIME1, ROAD, ROAD, ROAD,
        BRICK, BRICK, BRICK, ROAD, BRICK, ROAD, DIRT, ROAD, ROAD, ROAD, RED_KEY,
        ROAD, ROAD, ROAD, DIRT, BRICK, ROAD, ROAD, SKELETON1, GUARD1, SKELETON1, RED_POTION,
        ROAD, RED_POTION, BRICK, ROAD, BRICK, BRICK, BRICK, BRICK, YELLOW_DOOR, BRICK, BRICK, 
        GREEN_SLIME1, BRICK, BRICK, ROAD, ROAD, ROAD, ROAD, ROAD, ROAD, ROAD, BRICK,
        RED_SLIME1, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, ROAD, YELLOW_KEY,
        GREEN_SLIME1, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, ROAD, BLUE_KEY, 
        ROAD, BRICK, BRICK, BRICK, BRICK, BRICK, RED_DOOR, BRICK, BRICK, DIRT, YELLOW_KEY,
        ROAD, ROAD, ROAD, BRICK, BRICK, MAGICIAN1, ROAD, SKELETON1, BRICK, ROAD, ROAD,
        BRICK, DOWNSTAIRS, ROAD, BAT1, ROAD, ROAD, ROAD, ROAD, BAT1, ROAD, ROAD,
    },
    {
        DOWNSTAIRS, ROAD, ROAD, STAR, ROAD, ROAD, ROAD, STAR, RED_GEM, BLUE_POTION, RED_GEM,
        ROAD, DIRT, RED_SLIME1, BRICK, ROAD, BRICK, BLUE_GEM, BRICK, ROAD, BRICK, ROAD,
        ROAD, BRICK, BLUE_GEM, BRICK, GREEN_SLIME1, STAR, ROAD, BRICK, MAGICIAN_LIGHTNING1, BRICK, ROAD,
        GREEN_SLIME1, BRICK, BRICK, BRICK, RED_SLIME1, BRICK, ROAD, BRICK, BIG_SLIME1, BRICK, GUARD1,
        BAT1, BRICK, RED_KEY, BRICK, GREEN_SLIME1, BRICK, ROAD, STAR, SKELETON1, STAR, ROAD,
        ROAD, BRICK, BLUE_DOOR, BRICK, ROAD, BRICK, RED_POTION, BRICK, ROAD, BRICK, ROAD,
        ROAD, ROAD, RED_SLIME1, ROAD, ROAD, STAR, ROAD, ROAD, ROAD, STAR, GREEN_POTION,
        BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, DIRT,
        ROAD, BAT1, RED_SLIME1, DIRT, RED_POTION, RED_POTION, ROAD, RED_SLIME1, ROAD, RED_GEM, ROAD,
        ROAD, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, 
        ROAD, ROAD, RED_SLIME1, GREEN_SLIME1, BAT1, ROAD, GREEN_SLIME1, BAT1, DIRT, YELLOW_KEY, UPSTAIRS, 
    }
};

#endif // !GAME_DATA_CONSTANTS_H
