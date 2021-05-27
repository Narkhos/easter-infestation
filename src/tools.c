#include <stdbool.h>
#include <gb/gb.h>
#include "text.h"
#include "menu.h"
#include "tools.h"
#include "hero.h"
#include "exploration.h"
#include "title.h"
#include "inn.h"
#include "blacksmith.h"
#include "knight.h"
#include "battle.h"
#include "boss.h"

#include "gfx/dungeon_tileset.h"
#include "gfx/inn_tileset.h"
#include "gfx/blacksmith_tileset.h"
#include "gfx/knight_tileset.h"
#include "gfx/battlefield_tileset.h"
#include "gfx/boss_tileset.h"

bool game_victory = false;

const UINT16 powOfTen[5] = {1, 10, 100, 1000, 10000};

unsigned char win_tilemap[6*21];

char *itoa(UINT16 n, char *s, UINT8 length)
{
	UINT16 ret;
	
	for(UINT8 i = 0; i < length; i++) {
		unsigned int j = length - i -1;
		ret = n/powOfTen[j];
		s[i] = (BYTE)ret + '0';
		n = n - ret * powOfTen[j];
	}
	
	s[length] = '\0';
	
	return s;
}

void print_separator() {
	text_print_string_win(0, 0, "____________________");
}

void clear_win() {
	set_win_tiles(0, 1, 21, 5, win_tilemap);
	print_separator();
}

UINT8 gameScreen = SCREEN_EXPLORATION;

unsigned int x = 0; // scroll background x position
unsigned int y = 0; // scroll background y position


// EGGS

const int egg_position[22][2] = {
	{48 - 32, 64}, 	// EGG_FAR_LEFT_LSIDE
	{56 - 32, 64}, 	// EGG_FAR_RIGHT_LSIDE
	{48, 64},		// EGG_FAR_LEFT_MIDDLE
	{56, 64},		// EGG_FAR_RIGHT_MIDDLE
	{48 + 32, 64},	// EGG_FAR_LEFT_RSIDE
	{56 + 32, 64},	// EGG_FAR_RIGHT_RSIDE
	{48 - 32, 64},	// BROKEN_EGG_FAR_LEFT_LSIDE
	{56 - 32, 64},	// BROKEN_EGG_FAR_RIGHT_LSIDE
	{48, 64},		// BROKEN_EGG_FAR_LEFT_MIDDLE
	{56, 64},		// BROKEN_EGG_FAR_RIGHT_MIDDLE
	{48 + 32, 64},	// BROKEN_EGG_FAR_LEFT_RSIDE
	{56 + 32, 64},	// BROKEN_EGG_FAR_RIGHT_RSIDE
	{48, 80},		// EGG_NEAR_LEFT
	{56, 80},		// EGG_NEAR_RIGHT
	
	{96, 80},		// EGG_NEAR_LEFT_RSIDE
	{8, 80},		// EGG_NEAR_RIGHT_LSIDE
	
	{48, 80},		// BROKEN_EGG_NEAR_LEFT
	{56, 80},		// BROKEN_EGG_NEAR_RIGHT
	
	{96, 80},		// BROKEN_EGG_NEAR_LEFT_RSIDE
	{8, 80},		// BROKEN_EGG_NEAR_RIGHT_LSIDE

	{48, 96},		// BROKEN_EGG_LEFT
	{56, 96}		// BROKEN_EGG_RIGHT
};

bool egg_visibility[22];

void drawEggSide(UINT8 egg) {
	move_sprite(egg, egg_position[egg][0] + x, egg_position[egg][1] + y);
}

void drawEgg(UINT8 egg) {
	drawEggSide(egg);
	drawEggSide(egg + 1);
}

void drawAllVisibleEggs() {
	hideEggs();

	for (UINT8 i = 0; i < 22; i ++) {
		if (egg_visibility[i]) {
			drawEggSide(i);
		}
	}
}

void initEggs() {
	
	set_sprite_tile(EGG_FAR_LEFT_LSIDE, 0);
	set_sprite_tile(EGG_FAR_RIGHT_LSIDE, 2);
	set_sprite_tile(EGG_FAR_LEFT_MIDDLE, 0);
	set_sprite_tile(EGG_FAR_RIGHT_MIDDLE, 2);
	set_sprite_tile(EGG_FAR_LEFT_RSIDE, 0);
	set_sprite_tile(EGG_FAR_RIGHT_RSIDE, 2);

	set_sprite_tile(BROKEN_EGG_FAR_LEFT_LSIDE, 4);
	set_sprite_tile(BROKEN_EGG_FAR_RIGHT_LSIDE, 6);
	set_sprite_tile(BROKEN_EGG_FAR_LEFT_MIDDLE, 4);
	set_sprite_tile(BROKEN_EGG_FAR_RIGHT_MIDDLE, 6);
	set_sprite_tile(BROKEN_EGG_FAR_LEFT_RSIDE, 4);
	set_sprite_tile(BROKEN_EGG_FAR_RIGHT_RSIDE, 6);

	set_sprite_tile(EGG_NEAR_LEFT, 8);
	set_sprite_tile(EGG_NEAR_RIGHT, 10);
	
	set_sprite_tile(EGG_NEAR_LEFT_RSIDE, 8);
	set_sprite_tile(EGG_NEAR_RIGHT_LSIDE, 10);

	set_sprite_tile(BROKEN_EGG_NEAR_LEFT, 12);
	set_sprite_tile(BROKEN_EGG_NEAR_RIGHT, 14);
	
	set_sprite_tile(BROKEN_EGG_NEAR_LEFT_RSIDE, 12);
	set_sprite_tile(BROKEN_EGG_NEAR_RIGHT_LSIDE, 14);

	set_sprite_tile(BROKEN_EGG_LEFT, 16);
	set_sprite_tile(BROKEN_EGG_RIGHT, 18);
}

void hideEggs() {
	move_sprite(EGG_FAR_LEFT_LSIDE, 0, 0);
	move_sprite(EGG_FAR_RIGHT_LSIDE, 0, 0);
	move_sprite(EGG_FAR_LEFT_MIDDLE, 0, 0);
	move_sprite(EGG_FAR_RIGHT_MIDDLE, 0, 0);
	move_sprite(EGG_FAR_LEFT_RSIDE, 0, 0);
	move_sprite(EGG_FAR_RIGHT_RSIDE, 0, 0);
	move_sprite(BROKEN_EGG_FAR_LEFT_LSIDE, 0, 0);
	move_sprite(BROKEN_EGG_FAR_RIGHT_LSIDE, 0, 0);
	move_sprite(BROKEN_EGG_FAR_LEFT_MIDDLE, 0, 0);
	move_sprite(BROKEN_EGG_FAR_RIGHT_MIDDLE, 0, 0);
	move_sprite(BROKEN_EGG_FAR_LEFT_RSIDE, 0, 0);
	move_sprite(BROKEN_EGG_FAR_RIGHT_RSIDE, 0, 0);
	move_sprite(EGG_NEAR_LEFT, 0, 0);
	move_sprite(EGG_NEAR_RIGHT, 0, 0);
	move_sprite(EGG_NEAR_LEFT_RSIDE, 0, 0);
	move_sprite(EGG_NEAR_RIGHT_LSIDE, 0, 0);
	move_sprite(BROKEN_EGG_NEAR_LEFT, 0, 0);
	move_sprite(BROKEN_EGG_NEAR_RIGHT, 0, 0);
	move_sprite(BROKEN_EGG_NEAR_LEFT_RSIDE, 0, 0);
	move_sprite(BROKEN_EGG_NEAR_RIGHT_LSIDE, 0, 0);
	move_sprite(BROKEN_EGG_LEFT, 0, 0);
	move_sprite(BROKEN_EGG_RIGHT, 0, 0);
}

void set_all_egg_visibility(bool visibility) {
	for (UINT8 i = 0; i < 22; i ++) {
		egg_visibility[i] = visibility;
	}
}

void hideBlobs() {
	move_sprite(BLOB_FAR_LEFT_LSIDE, 0, 0);
	move_sprite(BLOB_FAR_RIGHT_LSIDE, 0, 0);
	move_sprite(BLOB_FAR_LEFT_MIDDLE, 0, 0);
	move_sprite(BLOB_FAR_RIGHT_MIDDLE, 0, 0);
	move_sprite(BLOB_FAR_LEFT_RSIDE, 0, 0);
	move_sprite(BLOB_FAR_RIGHT_RSIDE, 0, 0);

	move_sprite(BLOB_NEAR_LEFT_LSIDE, 0, 0);
	move_sprite(BLOB_NEAR_RIGHT_LSIDE, 0, 0);
	move_sprite(BLOB_NEAR_LEFT_MIDDLE, 0, 0);
	move_sprite(BLOB_NEAR_RIGHT_MIDDLE, 0, 0);
	move_sprite(BLOB_NEAR_LEFT_RSIDE, 0, 0);
	move_sprite(BLOB_NEAR_RIGHT_RSIDE, 0, 0);
}

void initBlobs() {
	
	set_sprite_tile(BLOB_FAR_LEFT_LSIDE, 0x18);
	set_sprite_tile(BLOB_FAR_RIGHT_LSIDE, 0x1A);
	set_sprite_tile(BLOB_FAR_LEFT_MIDDLE, 0x18);
	set_sprite_tile(BLOB_FAR_RIGHT_MIDDLE, 0x1A);
	set_sprite_tile(BLOB_FAR_LEFT_RSIDE, 0x18);
	set_sprite_tile(BLOB_FAR_RIGHT_RSIDE, 0x1A);

	set_sprite_tile(BLOB_NEAR_LEFT_LSIDE, 0x14);
	set_sprite_tile(BLOB_NEAR_RIGHT_LSIDE, 0x16);
	set_sprite_tile(BLOB_NEAR_LEFT_MIDDLE, 0x14);
	set_sprite_tile(BLOB_NEAR_RIGHT_MIDDLE, 0x16);
	set_sprite_tile(BLOB_NEAR_LEFT_RSIDE, 0x14);
	set_sprite_tile(BLOB_NEAR_RIGHT_RSIDE, 0x16);
}

void healing(bool withText) {
	UINT16 maxHP = getHeroMaxHP();

	if (hero.herbs == 0) {
		if (withText) {
			text_print_string_win(0, 3, "POTION(f) REQUIRED");
		}
		sound_KO();
		
		return;
	}

	if (hero.HP >= maxHP) {
		if (withText) {
			text_print_string_win(0, 3, "YOU FEEL GOOD");
		}
		sound_KO();

		return;
	}

	if (hero.herbs > 0 && hero.HP < maxHP) {
		hero.herbs --;
		hero.HP += maxHP / 2 + hero.survival;
		if (hero.HP > maxHP) hero.HP = maxHP;
		if (withText) {
			text_print_string_win(0, 3, "YOU FEEL BETTER");
		}

		sound_OK();
	}

	return;
}

void set_screen(UINT8 screen) {
	HIDE_BKG;
	gameScreen = screen;
	clear_win();

	if (gameScreen != SCREEN_EXPLORATION) hideEggs();
	if (gameScreen != SCREEN_BATTLE
		&& gameScreen != SCREEN_BATTLE_NEAR_ATTACK
		&& gameScreen != SCREEN_BATTLE_FAR_ATTACK
		&& gameScreen != SCREEN_BATTLE_MENU) {
		
		hideBlobs();
	}

	light(true);

	switch(gameScreen) {
		case SCREEN_EXPLORATION:
			SWITCH_ROM_MBC1(2);
			set_bkg_data(0, DUNGEON_TILESET_TILE_COUNT, DUNGEON_TILESET);
			draw_dungeon(x, y + Y_BUFFERS[y_buffer]);
			light(hero.torch);
			break;
		case SCREEN_INN:
			SWITCH_ROM_MBC1(1);
    		set_bkg_data(0, INN_TILESET_TILE_COUNT, INN_TILESET);
			draw_inn(x, y + Y_BUFFERS[y_buffer]);
			init_menu(2);
			break;
		case SCREEN_INN_EXIT:
			SWITCH_ROM_MBC1(1);
    		set_bkg_data(0, INN_TILESET_TILE_COUNT, INN_TILESET);
			draw_inn(x, y + Y_BUFFERS[y_buffer]);
			init_menu(1);
			break;
		case SCREEN_BLACKSMITH:
			SWITCH_ROM_MBC1(1);
    		set_bkg_data(0, BLACKSMITH_TILESET_TILE_COUNT, BLACKSMITH_TILESET);
			draw_blacksmith(x, y + Y_BUFFERS[y_buffer]);
			init_menu(4);
			break;
		case SCREEN_KNIGHT:
			SWITCH_ROM_MBC1(1);
    		set_bkg_data(0, KNIGHT_TILESET_TILE_COUNT, KNIGHT_TILESET);
			draw_knight(x, y + Y_BUFFERS[y_buffer]);
			break;
		case SCREEN_BATTLE:
			SWITCH_ROM_MBC1(3);
			initBattlefield(getAreaLevel());
    		set_bkg_data(0, BATTLEFIELD_TILESET_TILE_COUNT, BATTLEFIELD_TILESET);
			draw_battlefield(x, y + Y_BUFFERS[y_buffer], true);
			init_menu(4);
			break;
		case SCREEN_BATTLE_MENU:
			init_menu(4);
			break;
		case SCREEN_BATTLE_NEAR_ATTACK:
		case SCREEN_BATTLE_FAR_ATTACK:
			init_menu(4);
			break;
		case SCREEN_BATTLE_WIN:
		case SCREEN_BATTLE_LOOSE:
			SWITCH_ROM_MBC1(3);
    		set_bkg_data(0, BATTLEFIELD_TILESET_TILE_COUNT, BATTLEFIELD_TILESET);
			draw_battlefield(x, y + Y_BUFFERS[y_buffer], false);
			break;
		case SCREEN_LEVEL_UP:
			SWITCH_ROM_MBC1(3);
    		set_bkg_data(0, BATTLEFIELD_TILESET_TILE_COUNT, BATTLEFIELD_TILESET);
			draw_battlefield(x, y + Y_BUFFERS[y_buffer], false);
			init_menu(3);
			break;
		case SCREEN_BOSS:
			SWITCH_ROM_MBC1(3);
			initBoss(getAreaLevel());
    		set_bkg_data(0, BOSS_TILESET_TILE_COUNT, BOSS_TILESET);
			draw_boss(x, y + Y_BUFFERS[y_buffer]);
			init_menu(4);
			break;
		case SCREEN_TITLE:
			SWITCH_ROM_MBC1(1);
			draw_title(x, y + Y_BUFFERS[y_buffer]);
			init_menu(3);
			break;
	}

	swap_buffer();

	SHOW_BKG;
}

UINT8 prev_keys = 0;
UINT8 keys = 0;

const int Y_BUFFERS[2] = {0, 12};
int y_buffer = 1;

void swap_buffer() {
	move_bkg(0, Y_BUFFERS[y_buffer]*8);
	y_buffer = (y_buffer + 1) % 2;
	if( gameScreen == SCREEN_EXPLORATION) {
		drawAllVisibleEggs();
	}
}

void sound_OK() {
	NR10_REG = 0b01110011;
	NR11_REG = 0b10000000;
	NR12_REG = 0b11110000;
	NR13_REG = 0b00001010;
	NR14_REG = 0b11000110;
}

void sound_KO() {
	NR10_REG = 0b01001000;
	NR11_REG = 0b01000000;
	NR12_REG = 0b11111010;
	NR13_REG = 0b00000000;
	NR14_REG = 0b11000100;
}

void death_reset() {
	hero.position[0] = starting_position[0];
	hero.position[1] = starting_position[1];
	hero.direction = starting_direction;
	hero.HP = getHeroMaxHP() / 2;

	// Fermeture des oeufs
	for(int x = 0; x < level_width; x++) {
		for(int y = 0; y < level_height; y++) {
			if(level[y][x] & MAP_EGG_OPENED) {
				level[y][x] -= MAP_EGG_OPENED;
				level[y][x] += MAP_EGG_CLOSED;
			}
		}
	}
}

void waiting(UINT8 frames) {
	for(UINT8 i = frames; i != 0; --i) {
		wait_vbl_done();
	}
}