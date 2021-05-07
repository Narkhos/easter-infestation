#include <stdbool.h>
#include <gb/gb.h>
#include "tools.h"
#include "text.h"
#include "menu.h"

UINT8 selected_menu_entry = 0;
UINT8 nb_menu_entry = 1;

void init_menu(UINT8 _nb_menu_entry) {
    nb_menu_entry = _nb_menu_entry;
    selected_menu_entry = 0;
}

INT8 draw_menu() {
	print_separator();
	
    for(int i = 0; i < nb_menu_entry; i++) {
        if (selected_menu_entry == i) {
            text_print_string_win(0, i + 2, "r");
        } else {
            text_print_string_win(0, i + 2, " ");
        }
    }

	if (keys > 0) {
		if (keys & J_UP) {
			selected_menu_entry = selected_menu_entry == 0 ? nb_menu_entry - 1 : selected_menu_entry - 1;
		}
		if (keys & J_DOWN) {
			selected_menu_entry = (selected_menu_entry + 1) % nb_menu_entry;
		}
		if (keys & J_A) {
            // return the selected menu entry as activated
			return selected_menu_entry;
		}
    }
	
    // no entry was activated
	return -1;
}