#include <stdbool.h>
//#include <stdio.h>
#include <gb/gb.h>
// #include <string.h>
#include "gfx/sprites.h"
#include "music/hUGEDriver.h"

//#include <time.h>
//#include <rand.h>
#include "tools.h"
#include "exploration.h"
#include "blacksmith.h"
#include "knight.h"
#include "battle.h"
#include "boss.h"
#include "inn.h"
#include "hero.h"
#include "title.h"

#include "gfx/dungeon_tileset.h"
#include "text.h"

extern const hUGESong_t song;

void main(void) {
	
	// Music init
    BGP_REG  = 0b11100100;
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

	__critical {
        hUGE_init(&song);
        add_VBL(hUGE_dosound);
    }

	// Charge les tuiles des sprites dans la mémoire vidéo
    set_sprite_data(0,SPRITES_TILE_COUNT, SPRITES);
	
	SPRITES_8x16;
	
	initEggs();
	initBlobs();

    SHOW_BKG;
	SHOW_WIN;
	SHOW_SPRITES;

	set_interrupts(VBL_IFLAG);
	
	text_load_font();
	
	for (int i = 0 ; i < 6*21 ; i++) {
        win_tilemap[i] = 0xDF;
    }
	
	clear_win();
	
	move_win(7, 12*8);

	set_screen(SCREEN_TITLE);
	state_title();

	UINT8 newState = SCREEN_SAME;

	while(1) {
		wait_vbl_done();
		
		keys = joypad();

		if (keys == prev_keys) {
            continue;
        }

		switch(gameScreen) {
			case SCREEN_EXPLORATION:
				newState = state_exploration();
				break;
			case SCREEN_INN:
				newState = state_inn();
				break;
			case SCREEN_INN_EXIT:
				newState = state_inn_exit();
				break;
			case SCREEN_BLACKSMITH:
				newState = state_blacksmith();
				break;
			case SCREEN_KNIGHT:
				newState = state_knight();
				break;
			case SCREEN_BATTLE:
				newState = state_battle();
				break;
			case SCREEN_BATTLE_WIN:
				newState = state_battle_win();
				break;
			case SCREEN_BATTLE_LOOSE:
				newState = state_battle_loose();
				break;
			case SCREEN_LEVEL_UP:
				newState = state_level_up();
				break;
			case SCREEN_BOSS:
				newState = state_boss();
				break;
			case SCREEN_TITLE:
				newState = state_title();
				break;
		}
		
		// On ne change pas de state, on se contente de swap le buffer
		if (newState == 0) {
			// swap_buffer();
		} else { // On a un changement de state, on déclenche le set_screen
			set_screen(newState);
			newState = 0;
		}
		
		prev_keys = keys;
	}
}