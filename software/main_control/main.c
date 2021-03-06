
#include <stdio.h>
#include <stdlib.h>

#include "system.h"
#include "game_data_constants.h"
#include "moster_data.h"
#include "vga/vga-helper.h"
#include "drawers/draw_aggregate.h"

#define YELLOW  0
#define BLUE    1
#define RED     2
#define HIDDEN  3

volatile unsigned int  * Player_controller_base  = (unsigned int *) 	PLAYER_CONTROLLER_BASE;
volatile alt_16        * Game_data_mem_base      = (alt_16 *)           MEM_FOR_GAME_DATA_BASE;
volatile unsigned char * Keycode_mem_base        = (unsigned char *)    0x15010;

// Some important global variables
// alt_16        *Game_data_mem_base;
// unsigned char *Keycode_mem_base;
unsigned int  cur_posX, cur_posY, cur_floor;
unsigned char usb_key;
unsigned int  encounter;

//int getch(void)
//{
//     struct termios tm, tm_old;
//     int fd = 0, ch;
//
//     if (tcgetattr(fd, &tm) < 0) {
//          return -1;
//     }
//
//     tm_old = tm;
//     cfmakeraw(&tm);
//     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
//          return -1;
//     }
//
//     ch = getchar();
//     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
//          return -1;
//     }
//
//     return ch;
//}

void UpdateMap() {
    for (int i = PLAYER_STATUS_TYPE; i < PLAYER_STATUS_TYPE + FLOOR_SIZE; i++) {
        Player_controller_base[i] = (int) Game_data_mem_base[i + cur_floor * FLOOR_SIZE];
    }
}

void Init_Game()
{
    // Game_data_mem_base   = malloc((PLAYER_STATUS_TYPE + TOT_FLOOR_NUMBER * FLOOR_SIZE) * sizeof(alt_16));
    // Keycode_mem_base     = malloc(sizeof(unsigned char));

    // Init Status
    for (int i = 0; i < PLAYER_STATUS_TYPE; i++) {
        Game_data_mem_base[i] = Player_Status_Init[i];
    }

    // Init Floor Config
    for (int i = 0; i < TOT_FLOOR_NUMBER; i++) {
        for (int j = 0; j < FLOOR_SIZE; j++) {
            Game_data_mem_base[PLAYER_STATUS_TYPE + i * FLOOR_SIZE + j] = Floor_Configuration_Init[i][j];
        }
    }

    cur_posX  = 5;
    cur_posY  = 10;
    cur_floor = 0;
    usb_key   = 0;
    encounter = 0;
}

int Normal_Walk()
{
    switch (usb_key) {
        case 0x1a:
            if (cur_posY > 0 && cur_posY <= 10) {
                return 1;
            } else {
                return 0;
            }
            break;
        case 0x16:
            if (cur_posY >= 0 && cur_posY < 10) {
                return 1;
            } else {
                return 0;
            }
            break;
        case 0x04:
            if (cur_posX > 0 && cur_posX <= 10) {
                return 1;
            } else {
                return 0;
            }
            break;
        case 0x07:
            if (cur_posX >= 0 && cur_posX < 10) {
                return 1;
            } else {
                return 0;
            }
            break;
        default:
            return 0;
            break;
    }
}

#define MOVE               0
#define BLOCK              1
#define PICK_RED_GEM       2
#define PICK_BLUE_GEM      3
#define PICK_YELLOW_KEY    4
#define PICK_BLUE_KEY      5
#define PICK_RED_KEY       6
#define PICK_RED_HEALTH    7
#define PICK_BLUE_HEALTH   8
#define PICK_EXP           9
#define MEET_YELLOW_DOOR   10
#define MEET_BLUE_DOOR     11
#define MEET_RED_DOOR      12
#define MEET_HIDDEN_PATH   13
#define MEET_COIN_STORE    14
#define MEET_EXP_STORE     15
#define GO_UPSTAIRS        16
#define GO_DOWNSTAIRS      17
#define BATTLE             18

int Judge_the_block()
{
    alt_16 block_type;
    int encounter_signal;

    switch (usb_key) {
        case 0x1a:
            block_type = Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + (cur_posY - 1) * 11 + cur_posX];
            break;
        case 0x16:
            block_type = Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + (cur_posY + 1) * 11 + cur_posX];
            break;
        case 0x04:
            block_type = Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + cur_posY * 11 + cur_posX - 1];
            break;
        case 0x07:
            block_type = Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + cur_posY * 11 + cur_posX + 1];
            break;
        default:
            return 0;
            break;
    }

    switch (block_type) {
		case ROAD:
			encounter_signal = MOVE;
            break;
        case DIRT:
			encounter_signal = MOVE;
            break;
		case BRICK:
			encounter_signal = BLOCK;
            break;
		case STAR:
			encounter_signal = BLOCK;
            break;
		case VOID:
			encounter_signal = BLOCK;
            break;
        case UPSTAIRS:
            encounter_signal = GO_UPSTAIRS;
            break;
        case DOWNSTAIRS:
            encounter_signal = GO_DOWNSTAIRS;
            break;
		case YELLOW_DOOR:
			encounter_signal = MEET_YELLOW_DOOR;
            break;
		case BLUE_DOOR:
			encounter_signal = MEET_BLUE_DOOR;
            break;
		case RED_DOOR:
			encounter_signal = MEET_RED_DOOR;
            break;
		case YELLOW_KEY:
			encounter_signal = PICK_YELLOW_KEY;
            break;
		case BLUE_KEY:
			encounter_signal = PICK_BLUE_KEY;
            break;
		case RED_KEY:
			encounter_signal = PICK_RED_KEY;
            break;
		case RED_GEM:
			encounter_signal = PICK_RED_GEM;
            break;
		case BLUE_GEM:
			encounter_signal = PICK_BLUE_GEM;
            break;
		case RED_POTION:
			encounter_signal = PICK_RED_HEALTH;
            break;
		case BLUE_POTION:
			encounter_signal = PICK_BLUE_HEALTH;
            break;
        case GREEN_POTION:
			encounter_signal = PICK_EXP;
			break;
		default:
			encounter_signal = BATTLE;		// We set default to battle because the moster types are too many
            break;
    }

    return encounter_signal;
}

void Move()
{
    switch (usb_key) {
        case 0x1a:
            if (cur_posY > 0 && cur_posY <= 10) {
                cur_posY--;
            }
            break;
        case 0x16:
            if (cur_posY >= 0 && cur_posY < 10) {
                cur_posY++;
            }
            break;
        case 0x04:
            if (cur_posX > 0 && cur_posX <= 10) {
                cur_posX--;
            }
            break;
        case 0x07:
            if (cur_posX >= 0 && cur_posX < 10) {
                cur_posX++;
            }
            break;
        default: break;
    }
}

int Increase_Attribute(int Type, alt_16 value)
{
    if (Game_data_mem_base[Type] + value >= 0)
    {
        Game_data_mem_base[Type] += value;
        return 1;
    }
    else { return 0;}
}

void Change_Status(alt_16 value)
{
    Game_data_mem_base[3] = value;
}

void Pick_Items()
{
    switch (usb_key) {
        case 0x1a:
            Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + (cur_posY - 1) * 11 + cur_posX] = (alt_16) ROAD;
            break;
        case 0x16:
            Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + (cur_posY + 1) * 11 + cur_posX] = (alt_16) ROAD;
            break;
        case 0x04:
            Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + cur_posY * 11 + cur_posX - 1]   = (alt_16) ROAD;
            break;
        case 0x07:
            Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + cur_posY * 11 + cur_posX + 1]   = (alt_16) ROAD;
            break;
        default: break;
    }
}

void Meet_Door(int Type)
{
    switch (Type)
    {
        case YELLOW:
            if (0 == Increase_Attribute(Yellow_Key, -1)) { return;}
            break;
        case BLUE:
            if (0 == Increase_Attribute(Blue_Key, -1)) { return;}
            break;
        case RED:
            if (0 == Increase_Attribute(Red_Key, -1)) { return;}
            break;
        case HIDDEN:
            break;
        default: break;
    }
    // If there are keys left:
    Pick_Items();
}

void Meet_Coin_Store()
{

}

void Meet_EXP_Store()
{

}

void Go_Upstairs()
{
    Move();
    if ((cur_floor + 1) < TOT_FLOOR_NUMBER) {
        cur_floor ++;
    }
    draw_all_text(cur_floor);
}

void Go_DownStairs()
{
    Move();
    if (cur_floor > 0) {
        cur_floor --;
    }
    draw_all_text(cur_floor);
}

/*  Return 1 if the knight defeats the moster, 0 if the knight fails  */
int Do_Battle(int moster_type)
{
    Moster_Attributes* target_moster;

    // Choose the monster_type
    switch (moster_type)
    {
        case GREEN_SLIME1:
            target_moster = Moster_List[0];
            break;
        case RED_SLIME1:
            target_moster = Moster_List[1];
            break;
        case BAT1:
            target_moster = Moster_List[2];
            break;
        case MAGICIAN1:
            target_moster = Moster_List[3];
            break;
        case SKELETON1:
            target_moster = Moster_List[4];
            break;
        case GUARD1:
            target_moster = Moster_List[5];
            break;
        case MAGICIAN_LIGHTNING1:
            target_moster = Moster_List[6];
            break;
        case SLIME_MAN1:
            target_moster = Moster_List[7];
            break;
        default:
            break;
    }

    int monster_health = target_moster->Monster_Health;
    int monster_energy_bar = target_moster->Monster_Energy_Bar;

    // Calculate the health change of the player
    int player_health  = (int) Game_data_mem_base[Health];
    int player_attack  = (int) Game_data_mem_base[Attack];
    int player_defense = (int) Game_data_mem_base[Defense];
    // int player_status  = (int) Game_data_mem_base[Status];

#define damage(x, y) ( (x > y) ? (x - y) : 0 )

    while (1)
    {
        // Player attack first normally
        monster_health -= damage(player_attack, target_moster->Monster_Defense);
        if (monster_health > 0)
        {
            if (target_moster->Special == 1) {
                player_health -= target_moster->Monster_Attack;
            } else {
                player_health -= damage(target_moster->Monster_Attack, player_defense);
            }
        }
        else
        {
            Game_data_mem_base[Health] = player_health;
            Increase_Attribute(Coin, target_moster->Coin_Gained);
            Increase_Attribute(EXP, target_moster->EXP_Gained);
            Pick_Items();
            return 1;
        }
        
        if (player_health <= 0)
        {
            Game_data_mem_base[Health] = 0;
            return 0;
        }
    }

#undef damage
}

void Battle()
{
    int moster_type;

    switch (usb_key) {
        case 0x1a:
            moster_type = (int) Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + (cur_posY - 1) * 11 + cur_posX];
            break;
        case 0x16:
            moster_type = (int) Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + (cur_posY + 1) * 11 + cur_posX];
            break;
        case 0x04:
            moster_type = (int) Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + cur_posY * 11 + cur_posX - 1];
            break;
        case 0x07:
            moster_type = (int) Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + cur_posY * 11 + cur_posX + 1];
            break;
        default: break;
    }

    Do_Battle(moster_type);
}

void Print_All()
{
    // Clear the screen
    printf("\033[2J");
    // Print the current floor config
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (i == cur_posY && j == cur_posX) {
                printf("P,  ");
                continue;
            }
            printf("%d,  ", Game_data_mem_base[PLAYER_STATUS_TYPE + cur_floor * FLOOR_SIZE + i * 11 + j]);
        }
        printf("\n");
    }
    // Print the player status
    printf("Floor: %d\n", cur_floor);
    printf("X: %d\n", cur_posX);
    printf("Y: %d\n", cur_posY);
    printf("Status: %d\n", Game_data_mem_base[Status]);
    printf("Health: %d\n", Game_data_mem_base[Health]);
    printf("Attack: %d\n", Game_data_mem_base[Attack]);
    printf("Defense: %d\n", Game_data_mem_base[Defense]);
    printf("EXP: %d\n", Game_data_mem_base[EXP]);
    printf("Yellow_Key: %d\n", Game_data_mem_base[Yellow_Key]);
    printf("Blue_Key: %d\n", Game_data_mem_base[Blue_Key]);
    printf("Red_Key: %d\n", Game_data_mem_base[Red_Key]);
    printf("Coin: %d\n", Game_data_mem_base[Coin]);
}



// Execution of the Game
int main()
{
    
    Init_Game();
    for (int i = 0; i < PLAYER_STATUS_TYPE + TOT_FLOOR_NUMBER * FLOOR_SIZE; i++) {
        Player_controller_base[i] = (int) Game_data_mem_base[i];
    }
    draw_cover();
    printf("Welcome to the Magic Tower!\n");
    printf("Press Enter to move on...\n");
    while (usb_key != 0x28) {
    	usb_key = Keycode_mem_base[0];
    }
    fb_test();
    draw_all_text(cur_floor);
    // Main Loop
    while(1) {
        
//        Print_All();

        // Transmit all data to the register file
        for (int i = 0; i < PLAYER_STATUS_TYPE + TOT_FLOOR_NUMBER * FLOOR_SIZE; i++) {
            Player_controller_base[i] = (int) Game_data_mem_base[i];
        }

        // for (int i = PLAYER_STATUS_TYPE; i < PLAYER_STATUS_TYPE + FLOOR_SIZE; i++) {
        //     Player_controller_base[i] = (int) Game_data_mem_base[i + cur_floor * FLOOR_SIZE];
        // }
        UpdateMap();
        Player_controller_base[PLAYER_STATUS_TYPE + FLOOR_SIZE]      = cur_posX;
        Player_controller_base[PLAYER_STATUS_TYPE + FLOOR_SIZE + 1]  = cur_posY;

        // Receive the usb_key
        usb_key = 0x00;
        while ( usb_key != 0x1a && usb_key != 0x04 && usb_key != 0x16 && usb_key != 0x07 ) {
            usb_key = Keycode_mem_base[0];
            if (usb_key == 0x14) {
                return 0;
            }
            while(usb_key == Keycode_mem_base[0]);
        }

        if (0 == Normal_Walk()) {
            continue;
        }

        encounter = 0;     // Clear the encounter
        encounter = Judge_the_block();

        switch (encounter) {
            case MOVE:
                Move();
                break;
            case BLOCK:
                break;
            case PICK_RED_GEM:
                Pick_Items();
                Increase_Attribute(Attack, 2);
                break;
            case PICK_BLUE_GEM:
                Pick_Items();
                Increase_Attribute(Defense, 2);
                break;
            case PICK_YELLOW_KEY:
                Pick_Items();
                Increase_Attribute(Yellow_Key, 1);
                break;
            case PICK_BLUE_KEY:
                Pick_Items();
                Increase_Attribute(Blue_Key, 1);
                break;
            case PICK_RED_KEY:
                Pick_Items();
                Increase_Attribute(Red_Key, 1);
                break;
            case PICK_RED_HEALTH:
                Pick_Items();
                Increase_Attribute(Health, 100);
                break;
            case PICK_BLUE_HEALTH:
                Pick_Items();
                Increase_Attribute(Health, 200);
                break;
            case PICK_EXP:
                Pick_Items();
                Increase_Attribute(EXP, 5);
                break;
            case MEET_YELLOW_DOOR:
                Meet_Door(YELLOW);
                break;
            case MEET_BLUE_DOOR:
                Meet_Door(BLUE);
                break;
            case MEET_RED_DOOR:
                Meet_Door(RED);
                break;
            case MEET_HIDDEN_PATH:
                Meet_Door(HIDDEN);
                break;
            case MEET_COIN_STORE:
                Meet_Coin_Store();
                break;
            case MEET_EXP_STORE:
                Meet_EXP_Store();
                break;
            case GO_UPSTAIRS:
                Go_Upstairs();
                break;
            case GO_DOWNSTAIRS:
                Go_DownStairs();
                break;
            case BATTLE:
                Battle();
                break;
            default: break;
        }

        // The player dies
        if (Game_data_mem_base[Health] <= 0) {
            printf("YOU DIE, GAME OVER\n");
            draw_gameover_slow();
            break;
        }
    }

    return 0;
}
