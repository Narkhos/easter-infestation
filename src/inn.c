#include <stdbool.h>
#include <gb/gb.h>
#include "text.h"
#include "menu.h"
#include "tools.h"
#include "hero.h"
#include "inn.h"

#include "gfx/inn_tilemap.h"

// DRAW INN
void draw_inn(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y, INN_TILEMAP_WIDTH, INN_TILEMAP_HEIGHT, INN_TILEMAP);
	printHeroStats(x, y);
}

UINT16 getInnCost() {
	return INN_BASE_COST - hero.trade;
}

UINT8 state_inn_exit() {
	print_separator();
	text_print_string_win(0, 1, "HAVE A NICE DAY!");

	text_print_string_win(0, 3, "rEXIT");

	if (keys > 0) {

		if (keys & J_A) {
			sound_OK();
			return SCREEN_EXPLORATION;
		}
    }
		
	return SCREEN_SAME;
}

UINT8 state_inn() {
	bool changed = false;

	print_separator();
	text_print_string_win(0, 1, "REST FOR THE NIGHT?");

	UINT16 cost = getInnCost();
	unsigned char str_cost[4];
	itoa(cost, str_cost, 3);

	text_print_string_win(1, 2, "YES (");
	text_print_string_win(6, 2, str_cost);
	text_print_string_win(9, 2, "g)");

	text_print_string_win(1, 3, "NO");

	switch(draw_menu()) {
		case 0:
			if (hero.gold >= cost) {
				hero.gold -= cost;
				hero.HP = getHeroMaxHP();
				sound_OK();
				return SCREEN_INN_EXIT;
			} else {
				sound_KO();
			}
			break;
		case 1:
			return SCREEN_EXPLORATION;
			break;
		case -1:
			changed = false;
			break;

	}

	if (changed) {
		draw_inn(x, y + Y_BUFFERS[y_buffer]);
        swap_buffer();
	}
		
	return SCREEN_SAME;
}
