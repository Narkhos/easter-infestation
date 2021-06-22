#include <stdbool.h>
#include <gb/gb.h>
#include "text.h"
#include "menu.h"
#include "tools.h"
#include "hero.h"
#include "exploration.h"
#include "alchemist.h"

#include "gfx/alchemist_tilemap.h"

// DRAW ALCHEMIST
void draw_alchemist(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y, ALCHEMIST_TILEMAP_WIDTH, ALCHEMIST_TILEMAP_HEIGHT, ALCHEMIST_TILEMAP);
	printHeroStats(x, y);
}

UINT16 getPotionCost() {
	INT16 potionCost = POTION_BASE_COST - (hero.trade * TRADE_MULTIPLIER_POTION);

	if (potionCost > 0 ) return potionCost;

	return 0;
}

UINT8 state_alchemist_exit() {
	print_separator();
	text_print_string_win(0, 1, "COME BACK SOON");

	text_print_string_win(0, 3, "rEXIT");

	if (keys > 0) {

		if (keys & J_A) {
			sound_OK();
			return SCREEN_EXPLORATION;
		}
    }
		
	return SCREEN_SAME;
}

UINT8 state_alchemist() {
	bool changed = false;

	print_separator();
	text_print_string_win(0, 1, "BUY SOME POTION?");

	UINT16 cost = getPotionCost();
	unsigned char str_cost[4];
	itoa(cost, str_cost, 3);

	text_print_string_win(1, 2, "1 POTION (");
	text_print_string_win(11, 2, str_cost);
	text_print_string_win(14, 2, "g)");

	itoa(cost * 2, str_cost, 3);
	text_print_string_win(1, 3, "2 POTIONS(");
	text_print_string_win(11, 3, str_cost);
	text_print_string_win(14, 3, "g)");

	itoa(cost * 3, str_cost, 3);
	text_print_string_win(1, 4, "3 POTIONS(");
	text_print_string_win(11, 4, str_cost);
	text_print_string_win(14, 4, "g)");

	text_print_string_win(1, 5, "NO THANKS");

	switch(draw_menu()) {
		case 0:
			if (hero.gold >= cost) {
				hero.gold -= cost;
				hero.potions += 1;
				sound_OK();
				alchimist_enabled = false;
				level[Y_ALCHEMIST][X_ALCHEMIST] = MAP_WALL;
				return SCREEN_ALCHEMIST_EXIT;
			} else {
				sound_KO();
			}
			break;
		case 1:
			if (hero.gold >= cost * 2) {
				hero.gold -= cost * 2;
				hero.potions += 2;
				sound_OK();
				alchimist_enabled = false;
				level[Y_ALCHEMIST][X_ALCHEMIST] = MAP_WALL;
				return SCREEN_ALCHEMIST_EXIT;
			} else {
				sound_KO();
			}
			break;
		case 2:
			if (hero.gold >= cost * 3) {
				hero.gold -= cost * 3;
				hero.potions += 3;
				sound_OK();
				alchimist_enabled = false;
				level[Y_ALCHEMIST][X_ALCHEMIST] = MAP_WALL;
				return SCREEN_ALCHEMIST_EXIT;
			} else {
				sound_KO();
			}
			break;
		case 3:
			alchimist_enabled = false;
			level[Y_ALCHEMIST][X_ALCHEMIST] = MAP_WALL;
			return SCREEN_EXPLORATION;
			break;
		case -1:
			changed = false;
			break;

	}

	if (changed) {
		draw_alchemist(x, y + Y_BUFFERS[y_buffer]);
        swap_buffer();
	}
		
	return SCREEN_SAME;
}
