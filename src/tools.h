#ifndef _TOOLS_H
#define _TOOLS_H

extern const UINT16 powOfTen[5];

extern char *itoa(UINT16 n, char *s, UINT8 length);

#define ERROR_OUT_OF_BOUND 10000

#define WHITE  0
#define SILVER 1
#define GRAY   2
#define BLACK  3

#define PALETTE(c0, c1, c2, c3) c0 | c1 << 2 | c2 << 4 | c3 << 6

extern void print_separator();

extern void clear_win();

extern unsigned char win_tilemap[6*21];

// GAME STATES

#define SCREEN_SAME 0
#define SCREEN_EXPLORATION 1
#define SCREEN_INN 2
#define SCREEN_INN_EXIT 3
#define SCREEN_ALCHEMIST 4
#define SCREEN_ALCHEMIST_EXIT 5
#define SCREEN_BLACKSMITH 6
#define SCREEN_KNIGHT 7
#define SCREEN_BATTLE 8
#define SCREEN_BATTLE_MENU 9
#define SCREEN_BATTLE_NEAR_ATTACK 10
#define SCREEN_BATTLE_FAR_ATTACK 11
#define SCREEN_BATTLE_WIN 12
#define SCREEN_BATTLE_LOOSE 13
#define SCREEN_BOSS 14
#define SCREEN_TITLE 15
#define SCREEN_LEVEL_UP 16

extern UINT8 gameScreen;

extern unsigned int x; // scroll background x position
extern unsigned int y; // scroll background y position

// EGGS
#define EGG_FAR_LEFT_LSIDE 0
#define EGG_FAR_RIGHT_LSIDE 1
#define EGG_FAR_LEFT_MIDDLE 2
#define EGG_FAR_RIGHT_MIDDLE 3
#define EGG_FAR_LEFT_RSIDE 4
#define EGG_FAR_RIGHT_RSIDE 5
#define BROKEN_EGG_FAR_LEFT_LSIDE 6
#define BROKEN_EGG_FAR_RIGHT_LSIDE 7
#define BROKEN_EGG_FAR_LEFT_MIDDLE 8
#define BROKEN_EGG_FAR_RIGHT_MIDDLE 9
#define BROKEN_EGG_FAR_LEFT_RSIDE 10
#define BROKEN_EGG_FAR_RIGHT_RSIDE 11
#define EGG_NEAR_LEFT 12
#define EGG_NEAR_RIGHT 13
#define EGG_NEAR_LEFT_RSIDE 14
#define EGG_NEAR_RIGHT_LSIDE 15
#define BROKEN_EGG_NEAR_LEFT 16
#define BROKEN_EGG_NEAR_RIGHT 17
#define BROKEN_EGG_NEAR_LEFT_RSIDE 18
#define BROKEN_EGG_NEAR_RIGHT_LSIDE 19
#define BROKEN_EGG_LEFT 20
#define BROKEN_EGG_RIGHT 21

extern bool egg_visibility[22]; // visibility of each egg

extern const int egg_position[22][2];

extern void drawEggSide(UINT8 egg);
extern void drawEgg(UINT8 egg);
extern void drawAllVisibleEggs();
extern void initEggs();
extern void hideEggs();

extern void set_all_egg_visibility(bool visibility);

extern void hideBlobs();
extern void initBlobs();

extern void healing(bool withText);

extern void set_screen(UINT8 screen);

extern UINT8 prev_keys;
extern UINT8 keys;

extern const int Y_BUFFERS[2];
extern int y_buffer;
extern void swap_buffer();
extern void sound_OK();
extern void sound_KO();

extern void death_reset();

// ECONOMICS
#define INN_BASE_COST 155
#define UPGRADE_BASE_COST 205

#define POTION_BASE_COST 55

#define POTION_BASE_HEAL 15
#define TRADE_MULTIPLIER 5

extern bool alchimist_enabled;

// ENEMIES
#define ENEMY_STATE_IDLE 0
#define ENEMY_STATE_ATTACK 1
#define ENEMY_STATE_DEFEND 2

// ACTIONS
#define ACTION_MELEE 0
#define ACTION_LONG_RANGE 1
#define ACTION_BLOCK 2
#define ACTION_HEAL 3

extern bool game_victory;

extern void waiting(UINT8 frames);

extern UINT8 difficulty;
#endif