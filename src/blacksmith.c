#include <stdbool.h>
#include <gb/gb.h>
#include "text.h"
#include "tools.h"
#include "menu.h"
#include "hero.h"
#include "blacksmith.h"

#include "gfx/blacksmith_tilemap.h"

// DRAW BLACKSMITH
void draw_blacksmith(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y, BLACKSMITH_TILEMAP_WIDTH, BLACKSMITH_TILEMAP_HEIGHT, BLACKSMITH_TILEMAP);
	printHeroStats(x, y);
}

UINT16 getUpgradeCost() {
	return UPGRADE_BASE_COST - hero.trade;
}

UINT8 state_blacksmith() {
	bool changed = false;

	UINT16 cost = getUpgradeCost();
	unsigned char str_cost[4];
	itoa(cost, str_cost, 3);

	text_print_string_win(0, 1, "UPGRADE?");
	
	text_print_string_win(1, 2, "SWORDm (");
	text_print_string_win(9, 2, str_cost);
	text_print_string_win(12, 2, "g)");

	text_print_string_win(1, 3, "SHIELDn (");
	text_print_string_win(10, 3, str_cost);
	text_print_string_win(13, 3, "g)");

	text_print_string_win(1, 4, "BOWo (");
	text_print_string_win(7, 4, str_cost);
	text_print_string_win(10, 4, "g)");

	text_print_string_win(1, 5, "EXIT");

	switch(draw_menu()) {
		case 0:
			if (hero.gold >= cost) {
				hero.gold -= cost;
				hero.sword++;
				sound_OK();
			} else {
				sound_KO();
			}
			changed = true;
			break;
		case 1:
			if (hero.gold >= cost) {
				hero.gold -= cost;
				hero.shield++;
				sound_OK();
			} else {
				sound_KO();
			}
			changed = true;
			break;
		case 2:
			if (hero.gold >= cost) {
				hero.gold -= cost;
				hero.bow++;
				sound_OK();
			} else {
				sound_KO();
			}
			changed = true;
			break;
		case 3:
			return SCREEN_EXPLORATION;
		case -1:
			changed = false;
	}

	if (changed) {
		draw_blacksmith(x, y + Y_BUFFERS[y_buffer]);
        swap_buffer();
	}
		
	return SCREEN_SAME;
	
}
