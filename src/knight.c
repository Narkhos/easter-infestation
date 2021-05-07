#include <stdbool.h>
#include <gb/gb.h>
#include "text.h"
#include "tools.h"
#include "menu.h"
#include "hero.h"
#include "knight.h"

#include "gfx/knight_tilemap.h"

// DRAW KNIGHT
void draw_knight(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y, KNIGHT_TILEMAP_WIDTH, KNIGHT_TILEMAP_HEIGHT, KNIGHT_TILEMAP);
	printHeroStats(x, y);
}

UINT8 state_knight() {
	print_separator();
	text_print_string_win(0, 1, "BEWARE OF THE BEAST!");
	text_print_string_win(0, 2, "BLOW YOUR TORCH OUT");
	text_print_string_win(0, 3, "IN ITS NEST AND IT");
	text_print_string_win(0, 4, "WILL ATTACK YOU.");

	text_print_string_win(0, 5, "rEXIT");

	if (keys > 0) {

		if (keys & J_A) {
			sound_OK();
			return SCREEN_EXPLORATION;
		}
    }
		
	return SCREEN_SAME;
	
}
