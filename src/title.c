#include <gb/gb.h>
#include <stdbool.h>
#include "text.h"
#include "menu.h"
#include "title.h"
#include "tools.h"
#include "hero.h"

#include "music/hUGEDriver.h"

// DRAW TITLE
void draw_title(unsigned int x, unsigned int y) {
	text_print_string_bkg(x + 1, y + 2, "EASTER INFESTATION");
	text_print_string_bkg(x + 3, y + 8, "BY XAVIER DIREZ");
	text_print_string_bkg(x + 8, y + 10, "2021");

	move_sprite(EGG_NEAR_LEFT, 80, 48);
	move_sprite(EGG_NEAR_RIGHT, 88, 48);
}

UINT8 state_title() {
	INT8 selected = -1;

	text_print_string_win(0, 1, "CHOOSE YOUR CLASS");

	text_print_string_win(1, 2, "WARRIOR c03 d01 b00");
	text_print_string_win(1, 3, "SCOUT   c01 d02 b01");
	text_print_string_win(1, 4, "LORD    c01 d01 b02");

	selected = draw_menu();

	if (selected >= 0) {
		// Disable title music
		hUGE_mute_channel(HT_CH1, true);
		hUGE_mute_channel(HT_CH2, true);
		hUGE_mute_channel(HT_CH3, true);
		hUGE_mute_channel(HT_CH4, true);

		initHero(selected); // 0: GLADIATOR; 1: SCOUT; 2: PRINCE
		sound_OK();
		return SCREEN_EXPLORATION;
	}
		
	return SCREEN_SAME;
}