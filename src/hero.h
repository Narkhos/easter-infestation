#ifndef _HERO_H
#define _HERO_H

#include <stdbool.h>

#define GLADIATOR  0
#define SCOUT 1
#define PRINCE   2

#define STAT_COMBAT  0
#define STAT_SURVIVAL 1
#define STAT_TRADE   2

#define BATTLE_XP 100

#define XP_MAX 500

typedef struct
{
	UINT8 combat;
	UINT8 survival;
	UINT8 trade;
	UINT8 job;
	INT16 HP;
	UINT8 keys;
	UINT8 potions;
	UINT16 gold;
	UINT16 XP;
	
	// Equipement level
	UINT8 sword;
	UINT8 bow;
	UINT8 shield;

	// Torch
	bool torch;

	int position[2];
	int direction;
	UINT16 moves;
	
} Hero;

extern int starting_position[2];
extern int starting_direction; // north : 0, east : 1, south : 2, west : 3

extern Hero hero;

extern UINT8 getHeroLevel();

extern UINT16 getHeroMaxHP();


extern void increaseLevel(UINT8 stat);

extern bool increaseXP(UINT16 gain);

extern void initHero(UINT8 job);

extern void light(bool on);

extern void toggleTorch();

extern void printHeroStats(unsigned int x, unsigned int y);

extern UINT8 getAreaLevel();

#endif