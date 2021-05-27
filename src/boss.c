#include <rand.h>
#include <gb/gb.h>
#include "text.h"
#include "tools.h"
#include "menu.h"
#include "hero.h"
#include "boss.h"

#include "gfx/boss_tileset.h"
#include "gfx/boss_idle_tilemap.h"
#include "gfx/boss_attack_tilemap.h"

Boss boss;

void initBoss(UINT16 level) {

	boss.LVL = level * 100;
	boss.HP_MAX = boss.LVL;
	boss.HP = boss.HP_MAX;
	boss.DEF = boss.LVL / 4;
	boss.ATT = boss.LVL / 4;

	boss.dead = false;

	boss.state = rand() & 3;
	
	if(boss.state == 3) {
		boss.state = ENEMY_STATE_IDLE;
	}
	
	return;
}

void drawBossState(unsigned int x, unsigned int y) {
		UINT8 _x = x + 6;
		UINT8 _y = y + 10;
		switch(boss.state) {
			case ENEMY_STATE_IDLE:
				text_print_string_bkg(_x, _y, "z");
				break;
			case ENEMY_STATE_ATTACK:
				text_print_string_bkg(_x, _y, "m");
				break;
			case ENEMY_STATE_DEFEND:
				text_print_string_bkg(_x, _y, "n");
				break;
			default:
				text_print_string_bkg(_x, _y, "*");
		}

		// status
		_x --;
		if (boss.HP > (boss.HP_MAX / 4) * 3) {
			text_print_string_bkg(_x, _y, "t");
		} else if (boss.HP > (boss.HP_MAX / 4) * 2) {
			text_print_string_bkg(_x, _y, "u");
		} else if (boss.HP > (boss.HP_MAX / 4)) {
			text_print_string_bkg(_x, _y, "v");
		} else {
			text_print_string_bkg(_x, _y, "w");
		}
}

// DRAW BOSS
void draw_boss(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y, BOSS_IDLE_TILEMAP_WIDTH, BOSS_IDLE_TILEMAP_HEIGHT, BOSS_IDLE_TILEMAP);
	printHeroStats(x, y);
	drawBossState(x, y);
}

// DRAW BOSS ATTACK
void draw_boss_attack(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y, BOSS_ATTACK_TILEMAP_WIDTH, BOSS_ATTACK_TILEMAP_HEIGHT, BOSS_ATTACK_TILEMAP);
	printHeroStats(x, y);
	drawBossState(x, y);
}


void bossAssault(UINT8 action_type) {
	
	if (boss.state == ENEMY_STATE_ATTACK) {
		UINT16 damages = boss.ATT;

		draw_boss_attack(x, y + Y_BUFFERS[y_buffer]);
		swap_buffer();

		// Wait for 10 frames
		waiting(10);

		if (action_type == ACTION_BLOCK) {
			damages -= hero.shield;
		}

		if (damages > 0) {
			hero.HP -= damages;
			if (hero.HP < 0) hero.HP = 0;
		}
	}
}

void hitBoss(UINT8 action_type) {
	UINT16 damages = hero.combat;
	if (boss.state == ENEMY_STATE_DEFEND) {
		damages -= boss.DEF;
	}

	switch(action_type) {
		case ACTION_MELEE:
			damages += hero.sword;
			break;
		case ACTION_LONG_RANGE:
			damages += hero.bow;
			break;
	}

	if (damages > 0) {
		boss.HP -= damages;
	}

	if (boss.HP <= 0) {
		boss.HP = 0;
		boss.dead = true;
	}
}

UINT8 bossAssaultResolution(UINT8 action_type) {

	switch(action_type) {
		case ACTION_MELEE:
			hitBoss(action_type);
			break;
		case ACTION_LONG_RANGE:
			hitBoss(action_type);
			break;
	}

	bossAssault(action_type);

	boss.state = rand() & 3;

	if(boss.state == 3) {
		boss.state = ENEMY_STATE_ATTACK; // More agressive
	}

	// Défaite
	if (hero.HP <= 0) {
		sound_KO();
		return SCREEN_BATTLE_LOOSE;
	}
	// Victoire
	if (boss.dead) {
		sound_OK();
		game_victory = true;
		return SCREEN_BATTLE_WIN;
	}

	return SCREEN_SAME;
	
}

UINT8 state_boss() {
	UINT8 newState = SCREEN_SAME;
	bool changed = false;

	text_print_string_win(0, 1, "CHOOSE YOUR MOVE");

	text_print_string_win(1, 2, "MELEE ATTACKm");
	text_print_string_win(1, 3, "LONG RANGE ATTACKo");
	text_print_string_win(1, 4, "BLOCKn");
	text_print_string_win(1, 5, "HEALf");

	switch(draw_menu()) {
		case 0:
			sound_OK();
			newState = bossAssaultResolution(ACTION_MELEE);
			changed = true;
			break;
		case 1:
			sound_OK();
			newState = bossAssaultResolution(ACTION_LONG_RANGE);
			changed = true;
			break;
		case 2:
			sound_OK();
			newState = bossAssaultResolution(ACTION_BLOCK);
			changed = true;
			break;
		case 3:
			healing(false);
			changed = true;
			break;
	}

	if (changed) {
		draw_boss(x, y + Y_BUFFERS[y_buffer]);

		if (newState == SCREEN_SAME) swap_buffer();
	}

	return newState;
}
