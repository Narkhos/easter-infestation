#include <rand.h>
#include <gb/gb.h>
#include "text.h"
#include "tools.h"
#include "menu.h"
#include "hero.h"
#include "battle.h"

#include "gfx/battlefield_tilemap.h"

// BLOBS

const UINT8 blob_state_position[6][2] = {
	{3, 5},
	{6, 5},
	{9, 5},
	{1, 10},
	{6, 10},
	{11, 10},
};

const int blob_position[12][2] = {
	{48 - 24, 64}, 	// BLOB_FAR_LEFT_LSIDE
	{56 - 24, 64}, 	// BLOB_FAR_RIGHT_LSIDE
	{48, 64},		// BLOB_FAR_LEFT_MIDDLE
	{56, 64},		// BLOB_FAR_RIGHT_MIDDLE
	{48 + 24, 64},	// BLOB_FAR_LEFT_RSIDE
	{56 + 24, 64},	// BLOB_FAR_RIGHT_RSIDE

	{9, 80},		// BLOB_NEAR_LEFT_LSIDE
	{17, 80},		// BLOB_NEAR_RIGHT_LSIDE
	{48, 80},		// BLOB_NEAR_LEFT_MIDDLE
	{56, 80},		// BLOB_NEAR_RIGHT_MIDDLE
	{87, 80},		// BLOB_NEAR_LEFT_RSIDE
	{95, 80},		// BLOB_NEAR_RIGHT_RSIDE
};

Battlefield battlefield;

UINT8 countBlobs() {
	UINT8 count = 0;
	for(int i = 0; i < 6; i++) {
		if (!battlefield.blob[i].dead) count ++;
	}

	return count;
}

void initBlob(UINT8 index, UINT8 level) {

	battlefield.blob[index].LVL = level;
	battlefield.blob[index].HP_MAX = battlefield.blob[index].LVL / 2 + 5;
	battlefield.blob[index].HP = battlefield.blob[index].HP_MAX;
	battlefield.blob[index].DEF = battlefield.blob[index].LVL / 4 + 1;
	battlefield.blob[index].ATT = battlefield.blob[index].LVL / 4 + 2;

	battlefield.blob[index].index = index;
	battlefield.blob[index].dead = index == 4 ? false : rand() & 1;

	battlefield.blob[index].state = rand() & 3;
	
	if(battlefield.blob[index].state == 3) {
		battlefield.blob[index].state = ENEMY_STATE_IDLE;
	}
	
	return;
}

void initBattlefield(UINT8 level) {
	battlefield.LVL = level;

	for(int i = 0; i<6; i++) {
		initBlob(i, level);
	}
}

void updateBattlefield() {
	for(int i = 0; i<6; i++) {
		battlefield.blob[i].state = rand() & 3;

		if(battlefield.blob[i].state == 3) {
			battlefield.blob[i].state = ENEMY_STATE_IDLE;
		}
	}
}

void drawBlobSide(UINT8 blob) {
	move_sprite(blob, blob_position[blob - 22][0] + x, blob_position[blob - 22][1] + y);
}

void drawBlobSprite(UINT8 blob) {
	drawBlobSide(blob);
	drawBlobSide(blob + 1);
}

void hideBlobSide(UINT8 blob) {
	move_sprite(blob, 0, 0);
}

void hideBlobSprite(UINT8 blob) {
	hideBlobSide(blob);
	hideBlobSide(blob + 1);
}

void drawBlobState(UINT8 index, unsigned int x, unsigned int y) {
		UINT8 _x = x + blob_state_position[index][0];
		UINT8 _y = y + blob_state_position[index][1];
		switch(battlefield.blob[index].state) {
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
		if (battlefield.blob[index].HP > (battlefield.blob[index].HP_MAX / 4) * 3) {
			text_print_string_bkg(_x, _y, "t");
		} else if (battlefield.blob[index].HP > (battlefield.blob[index].HP_MAX / 4) * 2) {
			text_print_string_bkg(_x, _y, "u");
		} else if (battlefield.blob[index].HP > (battlefield.blob[index].HP_MAX / 4)) {
			text_print_string_bkg(_x, _y, "v");
		} else {
			text_print_string_bkg(_x, _y, "w");
		}
}


void initBlobsPalette() {
	UINT8 blobSprite;
	for (UINT8 i = 0; i < 6; i++) {
		blobSprite = blobIndexToSprite(i);
		set_sprite_prop(blobSprite, get_sprite_prop(blobSprite) & ~S_PALETTE);
		set_sprite_prop(blobSprite + 1, get_sprite_prop(blobSprite + 1) & ~S_PALETTE);
	}
}

UINT8 blobIndexToSprite(UINT8 index) {
	return BLOB_FAR_LEFT_LSIDE + index * 2;
}

void drawBlob(UINT8 index, unsigned int x, unsigned int y) {

	if (!battlefield.blob[index].dead) {
		drawBlobSprite(blobIndexToSprite(index));

		drawBlobState(index, x, y);
	} else {
		hideBlobSprite(blobIndexToSprite(index));
	}
}

void drawBattlefield(unsigned int x, unsigned int y) {
	for(int i = 0; i<6; i++) {
		drawBlob(i, x, y);
	}
}

// DRAW BATTLEFIELD
void draw_battlefield(unsigned int x, unsigned int y, bool draw_enemies) {
	set_bkg_tiles(x, y, BATTLEFIELD_TILEMAP_WIDTH, BATTLEFIELD_TILEMAP_HEIGHT, BATTLEFIELD_TILEMAP);
	printHeroStats(x, y);
	if (draw_enemies) drawBattlefield(x, y);
}

UINT16 battle_gold_loot = 0;
bool battle_herb_loot = 0;

UINT8 state_level_up() {

	text_print_string_win(0, 1, "LEVEL UP!");

	text_print_string_win(1, 2, "COMBAT: c+1");
	text_print_string_win(1, 3, "SURVIVAL: d+1");
	text_print_string_win(1, 4, "TRADE: b+1");

	INT8 choice = draw_menu();
	if (choice != -1) {
		increaseLevel(choice);
		sound_OK();
		return SCREEN_EXPLORATION;
	}

	draw_battlefield(x, y + Y_BUFFERS[y_buffer], false);
		
	return SCREEN_SAME;
}

UINT8 state_battle_loose() {
	print_separator();
	text_print_string_win(0, 1, "YOU DIED");

	text_print_string_win(0, 5, "rOK");

	if (keys > 0) {
		if (keys & J_A) {
			sound_OK();
			death_reset();
			return SCREEN_EXPLORATION;
		}
    }

	draw_battlefield(x, y + Y_BUFFERS[y_buffer], false);
	
	return SCREEN_SAME;
}

UINT8 state_battle_win() {
	print_separator();

	if (game_victory) {
		text_print_string_win(0, 1, "CONGRATULATIONS!");
		text_print_string_win(0, 2, "YOU BRING PEACE BACK");
		text_print_string_win(0, 3, "TO THE KINGDOM!");
		text_print_string_win(0, 5, "THE END");
	} else {
		char xp[4];
		itoa(BATTLE_XP, xp, 3);
		text_print_string_win(0, 1, "VICTORY!");

		text_print_string_win(0, 2, "i: +");
		text_print_string_win(4, 2, xp);

		if (battle_gold_loot > 0) {
			char gold[4];
			itoa(battle_gold_loot, gold, 3);

			text_print_string_win(0, 3, "g: +");
			text_print_string_win(4, 3, gold);
		}

		if (battle_herb_loot) {
			text_print_string_win(0, 4, "f: +1");
		}

		text_print_string_win(0, 5, "rOK");
	}

	if (keys > 0) {
		if (keys & J_A) {
			
			if (!game_victory) {
				sound_OK();
				UINT16 levelUp = increaseXP(BATTLE_XP);
				if (levelUp) {
					return SCREEN_LEVEL_UP;
				} else {
					return SCREEN_EXPLORATION;
				}
			}
		}
    }

	draw_battlefield(x, y + Y_BUFFERS[y_buffer], false);
		
	return SCREEN_SAME;
}

void blobsAssault(UINT8 action_type) {
	
	for(int i = 0; i < 6; i++) {
		if (!battlefield.blob[i].dead) {
			if (battlefield.blob[i].state == ENEMY_STATE_ATTACK) {
				UINT8 blobSprite = blobIndexToSprite(i);
				scroll_sprite(blobSprite, 0, 2);
				scroll_sprite(blobSprite + 1, 0, 2);
				UINT16 damages = battlefield.blob[i].ATT;
				if (action_type == ACTION_BLOCK) {
					damages -= hero.shield;
				}

				if (damages > 0) {
					hero.HP -= damages;
					if (hero.HP < 0) hero.HP = 0;
				}
			}
		}
	}
}

void hitBlob(UINT8 index, UINT8 action_type) {
	UINT16 damages = hero.combat;
	if (battlefield.blob[index].state == ENEMY_STATE_DEFEND) {
		damages -= battlefield.blob[index].DEF;
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
		battlefield.blob[index].HP -= damages;
		UINT8 blobSprite = blobIndexToSprite(index);
		set_sprite_prop(blobSprite, get_sprite_prop(blobSprite) | S_PALETTE);
		set_sprite_prop(blobSprite + 1, get_sprite_prop(blobSprite + 1) | S_PALETTE);
	}

	if (battlefield.blob[index].HP <= 0) {
		battlefield.blob[index].HP = 0;
		battlefield.blob[index].dead = true;
	}
}

UINT8 assaultResolution(UINT8 action_type, UINT8 direction) {
	switch(action_type) {
		case ACTION_MELEE:
			hitBlob(direction + 3, action_type);
			break;
		case ACTION_LONG_RANGE:
			hitBlob(direction, action_type);
			break;
	}

	blobsAssault(action_type);

	updateBattlefield();
	// Défaite
	if (hero.HP <= 0) {
		sound_KO();
		return SCREEN_BATTLE_LOOSE;
	}
	// Victoire
	if (countBlobs() == 0) {
		// Une chance sur 4 de looter un soin
		if (hero.herbs < 99 && (rand() & 3) <= 1) {
			battle_herb_loot = true;
			hero.herbs ++;
		} else {
			battle_herb_loot = false;
		}
		battle_gold_loot = rand() & 127;
		hero.gold += battle_gold_loot;
		sound_OK();
		return SCREEN_BATTLE_WIN;
	}

	return SCREEN_SAME;
}

UINT8 state_battle() {
	UINT8 newState = SCREEN_SAME;
	bool changed = false;

	initBlobsPalette();

	text_print_string_win(0, 1, "CHOOSE YOUR MOVE");

	text_print_string_win(1, 2, "MELEE ATTACKm");
	text_print_string_win(1, 3, "LONG RANGE ATTACKo");
	text_print_string_win(1, 4, "BLOCKn");
	text_print_string_win(1, 5, "HEALf");

	switch(draw_menu()) {
		case 0:
			sound_OK();
			newState = SCREEN_BATTLE_NEAR_ATTACK;
			changed = true;
			break;
		case 1:
			sound_OK();
			newState = SCREEN_BATTLE_FAR_ATTACK;
			changed = true;
			break;
		case 2:
			sound_OK();
			newState = assaultResolution(ACTION_BLOCK, 0);
			changed = true;
			break;
		case 3:
			healing(false);
			changed = true;
			break;
	}

	if (changed) {
		draw_battlefield(x, y + Y_BUFFERS[y_buffer], true);
		if (newState == SCREEN_SAME) swap_buffer();
	}
		
	return newState;
}

UINT8 state_battle_near_attack() {
	UINT8 newState = SCREEN_SAME;
	bool changed = false;

	initBlobsPalette();

	text_print_string_win(0, 1, "MELEE ATTACK");

	text_print_string_win(1, 2, "LEFTm");
	text_print_string_win(1, 3, "FRONTm");
	text_print_string_win(1, 4, "RIGHTm");
	text_print_string_win(1, 5, "BACK");

	switch(draw_menu()) {
		case 0:
			sound_OK();
			newState = assaultResolution(ACTION_MELEE, 0);
			changed = true;
			break;
		case 1:
			sound_OK();
			newState = assaultResolution(ACTION_MELEE, 1);
			changed = true;
			break;
		case 2:
			sound_OK();
			newState = assaultResolution(ACTION_MELEE, 2);
			changed = true;
			break;
		case 3:
			sound_OK();
			newState = SCREEN_BATTLE_MENU;
			changed = true;
			break;
	}

	if (changed) {
		draw_battlefield(x, y + Y_BUFFERS[y_buffer], true);
		if (newState == SCREEN_SAME) swap_buffer();
	}
		
	return newState;
}

UINT8 state_battle_far_attack() {
	UINT8 newState = SCREEN_SAME;
	bool changed = false;

	initBlobsPalette();

	text_print_string_win(0, 1, "LONG RANGE ATTACK");

	text_print_string_win(1, 2, "LEFTo");
	text_print_string_win(1, 3, "FRONTo");
	text_print_string_win(1, 4, "RIGHTo");
	text_print_string_win(1, 5, "BACK");

	switch(draw_menu()) {
		case 0:
			sound_OK();
			newState = assaultResolution(ACTION_LONG_RANGE, 0);
			changed = true;
			break;
		case 1:
			sound_OK();
			newState = assaultResolution(ACTION_LONG_RANGE, 1);
			changed = true;
			break;
		case 2:
			sound_OK();
			newState = assaultResolution(ACTION_LONG_RANGE, 2);
			changed = true;
			break;
		case 3:
			newState = SCREEN_BATTLE_MENU;
			changed = true;
			break;
	}

	if (changed) {
		draw_battlefield(x, y + Y_BUFFERS[y_buffer], true);
		if (newState == SCREEN_SAME) swap_buffer();
	}
		
	return newState;
}
