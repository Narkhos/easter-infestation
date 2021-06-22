#include <stdbool.h>
#include <gb/gb.h>
#include "tools.h"
#include "exploration.h"
#include "text.h"
#include "hero.h"

int starting_position[2] = {1, 2};
int starting_direction = 0; // nord : 0, est : 1, sud : 2, ouest : 3

Hero hero;

UINT8 getHeroLevel() {
	return hero.combat + hero.survival + hero.trade;
}

UINT16 getHeroMaxHP() {
	return getHeroLevel() * 10;
}


void increaseLevel(UINT8 stat) {
	hero.XP -= XP_MAX;

	switch(stat) {
		case STAT_COMBAT:
			hero.combat ++;
			break;
		case STAT_SURVIVAL:
			hero.survival ++;
			break;
		case STAT_TRADE:
			hero.trade ++;
			break;
		
	}
}

bool increaseXP(UINT16 gain) {
	hero.XP += gain;
	if (hero.XP > XP_MAX) {
		return true; // level UP
	}
	return false; // No level UP
}

void initHero(UINT8 job) {
	hero.torch = true;
	hero.job = job;
	hero.keys = 0;
	hero.potions = 0;
	hero.gold = 50;
	hero.XP = 0;

	hero.sword = 1;
	hero.bow = 1;
	hero.shield = 1;

	hero.position[0] = starting_position[0];
	hero.position[1] = starting_position[1];
	hero.direction = starting_direction;
	
	switch(job) {
		case GLADIATOR:
			hero.combat = 3;
			hero.survival = 1;
			hero.trade = 0;
		break;
		case SCOUT:
			hero.combat = 1;
			hero.survival = 2;
			hero.trade = 1;
			hero.potions = 2;
		break;
		case PRINCE:
			hero.combat = 1;
			hero.survival = 1;
			hero.trade = 2;
			hero.gold = 150;
		break;
	}
	
	hero.HP = getHeroMaxHP();
}

void light(bool on) {
	if (on) {
		BGP_REG = PALETTE(WHITE, SILVER, GRAY, BLACK);
	} else {
		BGP_REG = PALETTE(SILVER, GRAY, BLACK, BLACK);
	}
}

void toggleTorch() {
	hero.torch = !hero.torch;
	light(hero.torch);
	if (hero.torch || !alchimist_enabled) {
		level[Y_ALCHEMIST][X_ALCHEMIST] = MAP_WALL;
	} else {
		level[Y_ALCHEMIST][X_ALCHEMIST] = MAP_ALCHEMIST;
	}
}


void printHeroStats(unsigned int x, unsigned int y) {
	unsigned char str[6];

	text_print_string_bkg(x + 12, y + 0, "a");
	text_print_string_bkg(x + 13, y + 0, itoa(hero.HP, str, 3));
	text_print_string_bkg(x + 16, y + 0, "/");
	text_print_string_bkg(x + 17, y + 0, itoa(getHeroMaxHP(), str, 3));
	
	text_print_string_bkg(x + 12, y + 1, "________");
	
	// Level
	text_print_string_bkg(x + 12, y + 2, "h");
	text_print_string_bkg(x + 13, y + 2, itoa(getHeroLevel(), str, 2));
	
	// XP
	text_print_string_bkg(x + 15, y + 2, " i");
	text_print_string_bkg(x + 17, y + 2, itoa(hero.XP, str, 3));

	text_print_string_bkg(x + 12, y + 3, "________");

	// Combat
	text_print_string_bkg(x + 12, y + 4, "c");
	text_print_string_bkg(x + 13, y + 4, itoa(hero.combat, str, 2));
	
	// Survie
	text_print_string_bkg(x + 12, y + 5, "d");
	text_print_string_bkg(x + 13, y + 5, itoa(hero.survival, str, 2));
	
	// Charisme
	text_print_string_bkg(x + 12, y + 6, "b");
	text_print_string_bkg(x + 13, y + 6, itoa(hero.trade, str, 2));
	
	// Sword
	text_print_string_bkg(x + 15, y + 4, "  m");
	text_print_string_bkg(x + 18, y + 4, itoa(hero.sword, str, 2));
	
	// Bow
	text_print_string_bkg(x + 15, y + 5, "  n");
	text_print_string_bkg(x + 18, y + 5, itoa(hero.shield, str, 2));
	
	// Shield
	text_print_string_bkg(x + 15, y + 6, "  o");
	text_print_string_bkg(x + 18, y + 6, itoa(hero.bow, str, 2));
	
	text_print_string_bkg(x + 12, y + 7, "________");

	// Keys
	text_print_string_bkg(x + 12, y + 8, "e");
	text_print_string_bkg(x + 13, y + 8, itoa(hero.keys, str, 1));
	
	// potions
	text_print_string_bkg(x + 14, y + 8, " f");
	text_print_string_bkg(x + 16, y + 8, itoa(hero.potions, str, 2));
	
	// Gold coins
	text_print_string_bkg(x + 12, y + 9, "g");
	text_print_string_bkg(x + 13, y + 9, itoa(hero.gold, str, 4));

	// Torch
	if (hero.torch) {
		text_print_string_bkg(x + 18, y + 8, "l ");
	} else {
		text_print_string_bkg(x + 18, y + 8, "k ");
	}
	text_print_string_bkg(x + 17, y + 9, " j ");
	

	text_print_string_bkg(x + 12, y + 10, "________");

	UINT8 areaLevel = getAreaLevel();
	
	switch(gameScreen) {
		case SCREEN_EXPLORATION:
			if (areaLevel == 0) {
				text_print_string_bkg(x + 12, y + 11, "  TOWN  ");
			} else if(areaLevel >=3) {
				text_print_string_bkg(x + 12, y + 11, "NEST h");
				text_print_string_bkg(x + 18, y + 11, itoa(areaLevel, str, 2));
			} else {
				text_print_string_bkg(x + 12, y + 11, "AREA h");
				text_print_string_bkg(x + 18, y + 11, itoa(areaLevel, str, 2));
			}
			
			break;
		case SCREEN_INN:
			text_print_string_bkg(x + 12, y + 11, " INN    ");
			break;
		case SCREEN_INN_EXIT:
			text_print_string_bkg(x + 12, y + 11, " INN    ");
			break;
		case SCREEN_BLACKSMITH:
			text_print_string_bkg(x + 12, y + 11, " SMITH  ");
			break;
		case SCREEN_TITLE:
			text_print_string_bkg(x + 12, y + 11, " TITLE  ");
			break;
	}
}

UINT8 getAreaLevel() {
	return (hero.position[0] + hero.position[1]) / 10;
}