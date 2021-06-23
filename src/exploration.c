#include <stdbool.h>
#include <rand.h>
#include <gb/gb.h>
#include "text.h"
#include "tools.h"
#include "hero.h"
#include "exploration.h"

#include "gfx/dungeon_tileset.h"
#include "gfx/bg_tilemap.h"

#include "gfx/center_far_tilemap.h"
#include "gfx/center_near_tilemap.h"
#include "gfx/left_far_front_tilemap.h"
#include "gfx/left_far_side_tilemap.h"
#include "gfx/left_near_front_tilemap.h"
#include "gfx/left_near_side_tilemap.h"
#include "gfx/left_side_tilemap.h"
#include "gfx/right_far_front_tilemap.h"
#include "gfx/right_far_side_tilemap.h"
#include "gfx/right_near_front_tilemap.h"
#include "gfx/right_near_side_tilemap.h"
#include "gfx/right_side_tilemap.h"

#include "gfx/door_right_near_side_tilemap.h"
#include "gfx/door_right_far_side_tilemap.h"
#include "gfx/door_opened_right_side_tilemap.h"
#include "gfx/door_opened_near_tilemap.h"
#include "gfx/door_opened_left_side_tilemap.h"
#include "gfx/door_opened_far_tilemap.h"
#include "gfx/door_left_near_side_tilemap.h"
#include "gfx/door_left_far_side_tilemap.h"
#include "gfx/door_closed_right_side_tilemap.h"
#include "gfx/door_closed_near_tilemap.h"
#include "gfx/door_closed_left_side_tilemap.h"
#include "gfx/door_closed_far_tilemap.h"

unsigned int level[25][25] = {
	{ 1, 1,66, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 8, 1, 0, 1, 1, 1, 0, 1, 8, 0, 8, 8,24, 1, 0, 1},
	{ 1, 0, 0, 3, 0, 1, 8, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{34, 0,24, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 3, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 0, 0, 0, 0, 8, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1,24, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 8, 1, 1, 8, 0, 1, 1, 0,24, 1, 0, 0, 0, 8, 0, 8, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 3, 1, 1, 1, 1},
	{ 1, 1, 8, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{ 1,24, 8, 1, 0, 0, 0, 0, 0, 1, 0, 8, 0, 1, 1, 8, 1, 1, 0, 1, 1, 0, 1, 1, 1},
	{ 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 8, 1},
	{ 1, 0, 0, 0, 0, 8, 1, 0, 1, 1, 0, 1, 8, 1, 1, 0, 1, 1, 1, 0, 1, 1, 8, 8, 1},
	{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 8, 1, 1, 0, 1, 0, 1, 0, 8, 1, 8,24, 1},
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 3, 8, 0, 0, 1, 1, 0, 1, 0, 0, 8, 0, 1, 3, 1, 1},
	{ 1,24, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 8, 1, 8, 8, 0, 0, 8, 1},
	{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1},
	{98, 8, 8, 8, 1, 8, 0, 0, 8, 1, 1,24, 1, 1, 1, 0, 1, 0, 8, 0, 8, 0, 8, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int level_width = 25;
int level_height = 25;

const int directions[4][2] = {
	{0, -1},
	{1, 0},
	{0, 1},
	{-1, 0}
};

const int right   [4] = {1, 2, 3, 0};
const int left    [4] = {3, 0, 1, 2};
const int forward [4] = {0, 1, 2, 3};
const int backward[4] = {2, 3, 0, 1};


void get_cell_position(int position[2], int direction, int distance, int* result) {
	result[0] =	position[0] + (directions[direction][0] * distance);
	result[1] = position[1] + (directions[direction][1] * distance);
}

unsigned int get_cell_content(int position[2]) {

	if (position[0] < 0 || position[0] >= level_height || position[1] < 0 || position[1] >= level_width) {
		return ERROR_OUT_OF_BOUND;
	} else {
		return level[position[1]][position[0]];
	}
}

void set_cell_content(int position[2], unsigned int value) {

	if (position[0] < 0 || position[0] >= level_height || position[1] < 0 || position[1] >= level_width) {
		return;
	} else {
		level[position[1]][position[0]] = value;
	}
}

// DRAW DUNGEON
void draw_dungeon(unsigned int x, unsigned int y) {
	// HIDE_SPRITES;
	// hideEggs();
	set_all_egg_visibility(false);

	int left_side[2];
	get_cell_position(hero.position, left[hero.direction], 1, left_side);
	
	int left_near[2];
	get_cell_position(left_side, forward[hero.direction], 1, left_near);
	
	int left_far[2];
	get_cell_position(left_near, forward[hero.direction], 1, left_far);
	
	int front_near[2];
	get_cell_position(hero.position, forward[hero.direction], 1, front_near);
	
	int front_far[2];
	get_cell_position(front_near, forward[hero.direction], 1, front_far);

	int right_side[2];
	get_cell_position(hero.position, right[hero.direction], 1, right_side);

	int right_near[2];
	get_cell_position(right_side, forward[hero.direction], 1, right_near);

	int right_far[2];
	get_cell_position(right_near, forward[hero.direction], 1, right_far);
	
	draw_background(x, y);

	unsigned int content;

	// FAR

	content = get_cell_content(left_far);
	
	if(content != ERROR_OUT_OF_BOUND) {
		if (!(get_cell_content(left_near) & 1)
			&& !(get_cell_content(front_near) & 1)) {
			if(content & 8) {
				// drawEgg(EGG_FAR_LEFT_LSIDE);
				if (!(get_cell_content(left_side) & 1)) {
					egg_visibility[EGG_FAR_LEFT_LSIDE] = true;
				}
				egg_visibility[EGG_FAR_RIGHT_LSIDE] = true;
			}
			if(content & 4) {
				// drawEgg(BROKEN_EGG_FAR_LEFT_LSIDE);
				if (!(get_cell_content(left_side) & 1)) {
					egg_visibility[BROKEN_EGG_FAR_LEFT_LSIDE] = true;
				}
				egg_visibility[BROKEN_EGG_FAR_RIGHT_LSIDE] = true;
			}
		}
		if(content & 1) {
			draw_left_far_side(x, y);
			draw_left_far_front(x, y);

			if(content & 2) {
				draw_door_left_far_side(x, y);
				draw_door_closed_left_far_front(x, y);
			}
		} else {
			if(content & 2) {
				draw_left_far_side(x, y);
				draw_left_far_front(x, y);
				draw_door_left_far_side(x, y);
				draw_door_opened_left_far_front(x, y);
			}
		}
	}
	
	content = get_cell_content(right_far);
	
	if(content != ERROR_OUT_OF_BOUND) {
		if (!(get_cell_content(right_near) & 1)
			&& !(get_cell_content(front_near) & 1)) {
			if(content & 8) {
				// drawEgg(EGG_FAR_LEFT_RSIDE);
				egg_visibility[EGG_FAR_LEFT_RSIDE] = true;
				if (!(get_cell_content(right_side) & 1)) {
					egg_visibility[EGG_FAR_RIGHT_RSIDE] = true;
				}
				
			}
			if(content & 4) {
				// drawEgg(BROKEN_EGG_FAR_LEFT_RSIDE);
				egg_visibility[BROKEN_EGG_FAR_LEFT_RSIDE] = true;
				if (!(get_cell_content(right_side) & 1)) {
					egg_visibility[BROKEN_EGG_FAR_RIGHT_RSIDE] = true;
				}
			}
		}

		if(content & 1) {
			draw_right_far_side(x, y);
			if(content & 2) {
				draw_door_right_far_side(x, y);
			}

			draw_right_far_front(x, y);
			if(content & 2) {
				draw_door_closed_right_far_front(x, y);
			}
		} else {
			if(content & 2) {
				draw_right_far_side(x, y);
				draw_door_right_far_side(x, y);
				draw_right_far_front(x, y);
				draw_door_opened_right_far_front(x, y);
			}
		}
	}
	
	content = get_cell_content(front_far);
	
	if(content != ERROR_OUT_OF_BOUND) {
		if (!(get_cell_content(front_near) & 1)) {
			if(content & 8) {
				// drawEgg(EGG_FAR_LEFT_MIDDLE);
				egg_visibility[EGG_FAR_LEFT_MIDDLE] = true;
				egg_visibility[EGG_FAR_RIGHT_MIDDLE] = true;
			}
			if(content & 4) {
				// drawEgg(BROKEN_EGG_FAR_LEFT_MIDDLE);
				egg_visibility[BROKEN_EGG_FAR_LEFT_MIDDLE] = true;
				egg_visibility[BROKEN_EGG_FAR_RIGHT_MIDDLE] = true;
			}
		}

		if(content & 1) {
			draw_center_far(x, y);
			
			if(content & 2) {
				draw_door_closed_center_far(x, y);
			}
		} else {
			if(content & 2) {
				draw_center_far(x, y);
				draw_door_opened_center_far(x, y);
			}
		}
	}

	// NEAR
	
	content = get_cell_content(left_near);
	if(content != ERROR_OUT_OF_BOUND) {
		if (!(get_cell_content(left_side) & 1)) {
			if(content & 8) {
				// drawEggSide(EGG_NEAR_RIGHT_LSIDE);
				egg_visibility[EGG_NEAR_RIGHT_LSIDE] = true;
			}
			if(content & 4) {
				// drawEggSide(BROKEN_EGG_NEAR_RIGHT_LSIDE);
				egg_visibility[BROKEN_EGG_NEAR_RIGHT_LSIDE] = true;
			}
		}

		if(content & 1) {
			draw_left_near_side(x, y);
			if(content & 2) {
				draw_door_left_near_side(x,y);
			}
			
			if(!(get_cell_content(left_side) & 1)) {
				draw_left_near_front(x, y);
			}
		} else {
			if(content & 2) {
				draw_left_near_side(x, y);
				draw_door_left_near_side(x, y);
				
				if(!(get_cell_content(left_side) & 1)) {
					draw_left_near_front(x, y);
				}
			}
		}
	}
	
	content = get_cell_content(right_near);
	if(content != ERROR_OUT_OF_BOUND) {
		if (!(get_cell_content(right_side) & 1)) {
			if(content & 8) {
				// drawEggSide(EGG_NEAR_LEFT_RSIDE);
				egg_visibility[EGG_NEAR_LEFT_RSIDE] = true;
			}
			if(content & 4) {
				// drawEggSide(BROKEN_EGG_NEAR_LEFT_RSIDE);
				egg_visibility[BROKEN_EGG_NEAR_LEFT_RSIDE] = true;
			}
		}

		if(content & 1) {
			draw_right_near_side(x, y);
			if(content & 2) {
				draw_door_right_near_side(x,y);
			}
			
			if(!(get_cell_content(right_side) & 1)) {
					draw_right_near_front(x, y);
			}
		} else {
			if(content & 2) {
				draw_right_near_side(x, y);
				draw_door_right_near_side(x, y);
				
				if(!(get_cell_content(right_side) & 1)) {
					draw_right_near_front(x, y);
				}
			}
		}
	}
	
	content = get_cell_content(front_near);
	if(content != ERROR_OUT_OF_BOUND) {
		if(content & 8) {
			// drawEgg(EGG_NEAR_LEFT);
			egg_visibility[EGG_NEAR_LEFT] = true;
			egg_visibility[EGG_NEAR_RIGHT] = true;
		}
		if(content & 4) {
			// drawEgg(BROKEN_EGG_NEAR_LEFT);
			egg_visibility[BROKEN_EGG_NEAR_LEFT] = true;
			egg_visibility[BROKEN_EGG_NEAR_RIGHT] = true;
		}

		if(content & 1) {
			draw_center_near(x, y);
			
			if(content & 2) {
				draw_door_closed_center_near(x, y);
			}
		} else {
			if(content & 2) {
				draw_center_near(x, y);
				draw_door_opened_center_near(x, y);
			}
		}
	}
	
	// SIDES
	
	content = get_cell_content(left_side);
	if(content != ERROR_OUT_OF_BOUND) {
		if(content & 1) {
			draw_left_side(x, y);
			if(content & 2) {
				draw_door_closed_left_side(x, y);
			}
		} else {
			
			if(content & 2) {
				draw_left_side(x, y);
				draw_door_opened_left_side(x, y);
			}
		}
	}
	
	content = get_cell_content(right_side);
	if(content != ERROR_OUT_OF_BOUND) {
		if(content & 1) {
			draw_right_side(x, y);
			if(content & 2) {
				draw_door_closed_right_side(x, y);
			}
		} else {
			
			if(content & 2) {
				draw_right_side(x, y);
				draw_door_opened_right_side(x, y);
			}
		}
	}
	
	content = get_cell_content(hero.position);
	if(content & 4) {
		// drawEgg(BROKEN_EGG_LEFT);
		egg_visibility[BROKEN_EGG_LEFT] = true;
		egg_visibility[BROKEN_EGG_RIGHT] = true;
	}
	
	printHeroStats(x, y);

	// SHOW_SPRITES;
}


bool player_move(int direction, UINT8* newState) {
	int dest_position[2];
	get_cell_position(hero.position, direction, 1, dest_position);
	
	int dest_content = get_cell_content(dest_position);
	
	if (dest_content == ERROR_OUT_OF_BOUND) {
		return false;
	} else {
		//clear_win();
		set_win_tiles(0, 2, 21, 5, win_tilemap);

		// Check for Inn to enter
		if(dest_content == MAP_INN) {
			*newState = SCREEN_INN;
			return false;
		}
		// Check for Blacksmith to enter
		if(dest_content == MAP_BLACKSMITH) {
			*newState = SCREEN_BLACKSMITH;
			return false;
		}
		// Check for Knight to enter
		if(dest_content == MAP_KNIGHT) {
			*newState = SCREEN_KNIGHT;
			return false;
		}
		// Check for Alchemist to enter
		if(dest_content == MAP_ALCHEMIST) {
			*newState = SCREEN_ALCHEMIST;
			return false;
		}

		// Check for an egg to open
		if(dest_content & 8) {
			dest_content -= 8;
			dest_content += 4;
			set_cell_content(dest_position, dest_content); //set to opened egg
			if (getAreaLevel() > 0) {
				*newState = SCREEN_BATTLE;
				return false;
			} else {
				return true;
			}
		}
		
		if(dest_content & 1) {
			// if it's a locked door, check if the player have a key and use it.
			if(!(dest_content & 2) || hero.keys == 0) {
				// Locked door and no key
				return false;
			} else {
				if(direction == hero.direction) {
					hero.keys--;
					set_cell_content(dest_position, 2); //set to opened door
					return true;
				} else { // Si on est en marche arrière, on ne peut pas utiliser la clé
					return false;
				}
			}
		}

		// Check for key to pickup
		if(dest_content & 16) {
			dest_content -= 16;
			set_cell_content(dest_position, dest_content);
			hero.keys ++;
			text_print_string_win(0, 2, "YOU FOUND A KEY");
		}

		// move player
		hero.position[0] = dest_position[0];
		hero.position[1] = dest_position[1];

		if(dest_content == 2) {
			// Si on est sur une case porte, on avance d'une case supplémentaire
			return player_move(direction, newState);
		} else {
			// Gestion des rencontres aléatoires
			if (getAreaLevel() > 0 && !hero.torch && ((rand() & 3) == 0)) {
				// *newState = SCREEN_BOSS;
				// return false;
				if ( getAreaLevel() >= 3) {
					if ((rand() & 3) == 0) {
						*newState = SCREEN_BOSS;
					} else {
						*newState = SCREEN_BATTLE;
					}
				} else {
					*newState = SCREEN_BATTLE;
				}
				return false;
			} else {
				return true;
			}
		}
	}
}


// DRAW BACKGROUND
void draw_background(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y, BG_TILEMAP_WIDTH, BG_TILEMAP_HEIGHT, BG_TILEMAP);
}

// DRAW WALLS

void draw_center_far(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 4, y + 4, CENTER_FAR_TILEMAP_WIDTH, CENTER_FAR_TILEMAP_HEIGHT, CENTER_FAR_TILEMAP);
}

void draw_left_far_front(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y + 4, LEFT_FAR_FRONT_TILEMAP_WIDTH, LEFT_FAR_FRONT_TILEMAP_HEIGHT, LEFT_FAR_FRONT_TILEMAP);
}

void draw_left_far_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 4, y + 4, LEFT_FAR_SIDE_TILEMAP_WIDTH, LEFT_FAR_SIDE_TILEMAP_HEIGHT, LEFT_FAR_SIDE_TILEMAP);
}

void draw_left_near_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 2, y + 2, LEFT_NEAR_SIDE_TILEMAP_WIDTH, LEFT_NEAR_SIDE_TILEMAP_HEIGHT, LEFT_NEAR_SIDE_TILEMAP);
}

void draw_left_near_front(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y + 2, LEFT_NEAR_FRONT_TILEMAP_WIDTH, LEFT_NEAR_FRONT_TILEMAP_HEIGHT, LEFT_NEAR_FRONT_TILEMAP);
}

void draw_left_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y, LEFT_SIDE_TILEMAP_WIDTH, LEFT_SIDE_TILEMAP_HEIGHT, LEFT_SIDE_TILEMAP);
}

void draw_right_far_front(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 8, y + 4, RIGHT_FAR_FRONT_TILEMAP_WIDTH, RIGHT_FAR_FRONT_TILEMAP_HEIGHT, RIGHT_FAR_FRONT_TILEMAP);
}

void draw_right_far_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 7, y + 4, RIGHT_FAR_SIDE_TILEMAP_WIDTH, RIGHT_FAR_SIDE_TILEMAP_HEIGHT, RIGHT_FAR_SIDE_TILEMAP);
}

void draw_right_near_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 8, y + 2, RIGHT_NEAR_SIDE_TILEMAP_WIDTH, RIGHT_NEAR_SIDE_TILEMAP_HEIGHT, RIGHT_NEAR_SIDE_TILEMAP);
}

void draw_right_near_front(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 10, y + 2, RIGHT_NEAR_FRONT_TILEMAP_WIDTH, RIGHT_NEAR_FRONT_TILEMAP_HEIGHT, RIGHT_NEAR_FRONT_TILEMAP);
}

void draw_center_near(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 2, y + 2, CENTER_NEAR_TILEMAP_WIDTH, CENTER_NEAR_TILEMAP_HEIGHT, CENTER_NEAR_TILEMAP);
}

void draw_right_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 10, y, RIGHT_SIDE_TILEMAP_WIDTH, RIGHT_SIDE_TILEMAP_HEIGHT, RIGHT_SIDE_TILEMAP);
}

// DRAW DOORS

void draw_door_closed_center_near(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 4, y + 2, DOOR_CLOSED_NEAR_TILEMAP_WIDTH, DOOR_CLOSED_NEAR_TILEMAP_HEIGHT, DOOR_CLOSED_NEAR_TILEMAP);
}

void draw_door_opened_center_near(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 4, y + 2, DOOR_OPENED_NEAR_TILEMAP_WIDTH, DOOR_OPENED_NEAR_TILEMAP_HEIGHT, DOOR_OPENED_NEAR_TILEMAP);
}

void draw_door_closed_center_far(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 5, y + 4, DOOR_CLOSED_FAR_TILEMAP_WIDTH, DOOR_CLOSED_FAR_TILEMAP_HEIGHT, DOOR_CLOSED_FAR_TILEMAP);
}

void draw_door_opened_center_far(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 5, y + 4, DOOR_OPENED_FAR_TILEMAP_WIDTH, DOOR_OPENED_FAR_TILEMAP_HEIGHT, DOOR_OPENED_FAR_TILEMAP);
}

void draw_door_closed_right_far_front(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 9, y + 4, DOOR_CLOSED_FAR_TILEMAP_WIDTH, DOOR_CLOSED_FAR_TILEMAP_HEIGHT, DOOR_CLOSED_FAR_TILEMAP);
}

void draw_door_opened_right_far_front(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 9, y + 4, DOOR_OPENED_FAR_TILEMAP_WIDTH, DOOR_OPENED_FAR_TILEMAP_HEIGHT, DOOR_OPENED_FAR_TILEMAP);
}

void draw_door_closed_left_far_front(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 1, y + 4, DOOR_CLOSED_FAR_TILEMAP_WIDTH, DOOR_CLOSED_FAR_TILEMAP_HEIGHT, DOOR_CLOSED_FAR_TILEMAP);
}

void draw_door_opened_left_far_front(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 1, y + 4, DOOR_OPENED_FAR_TILEMAP_WIDTH, DOOR_OPENED_FAR_TILEMAP_HEIGHT, DOOR_OPENED_FAR_TILEMAP);
}

void draw_door_closed_right_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 11, y + 2, DOOR_CLOSED_RIGHT_SIDE_TILEMAP_WIDTH, DOOR_CLOSED_RIGHT_SIDE_TILEMAP_HEIGHT, DOOR_CLOSED_RIGHT_SIDE_TILEMAP);
}

void draw_door_opened_right_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 11, y + 2, DOOR_OPENED_RIGHT_SIDE_TILEMAP_WIDTH, DOOR_OPENED_RIGHT_SIDE_TILEMAP_HEIGHT, DOOR_OPENED_RIGHT_SIDE_TILEMAP);
}

void draw_door_closed_left_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y + 2, DOOR_CLOSED_LEFT_SIDE_TILEMAP_WIDTH, DOOR_CLOSED_LEFT_SIDE_TILEMAP_HEIGHT, DOOR_CLOSED_LEFT_SIDE_TILEMAP);
}

void draw_door_opened_left_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x, y + 2, DOOR_OPENED_LEFT_SIDE_TILEMAP_WIDTH, DOOR_OPENED_LEFT_SIDE_TILEMAP_HEIGHT, DOOR_OPENED_LEFT_SIDE_TILEMAP);
}

void draw_door_right_near_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 8, y + 4, DOOR_RIGHT_NEAR_SIDE_TILEMAP_WIDTH, DOOR_RIGHT_NEAR_SIDE_TILEMAP_HEIGHT, DOOR_RIGHT_NEAR_SIDE_TILEMAP);
}

void draw_door_left_near_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 3, y + 4, DOOR_LEFT_NEAR_SIDE_TILEMAP_WIDTH, DOOR_LEFT_NEAR_SIDE_TILEMAP_HEIGHT, DOOR_LEFT_NEAR_SIDE_TILEMAP);
}

void draw_door_right_far_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 7, y + 4, DOOR_RIGHT_FAR_SIDE_TILEMAP_WIDTH, DOOR_RIGHT_FAR_SIDE_TILEMAP_HEIGHT, DOOR_RIGHT_FAR_SIDE_TILEMAP);
}

void draw_door_left_far_side(unsigned int x, unsigned int y) {
	set_bkg_tiles(x + 4, y + 4, DOOR_LEFT_FAR_SIDE_TILEMAP_WIDTH, DOOR_LEFT_FAR_SIDE_TILEMAP_HEIGHT, DOOR_LEFT_FAR_SIDE_TILEMAP);
}

UINT8 state_exploration() {
	bool changed = false;
	UINT8 newState = SCREEN_SAME;

	switch(hero.direction) {
		case 0:
			text_print_string_win(7, 1, "NORTH");
			break;
		case 1:
			text_print_string_win(7, 1, "EAST ");
			break;
		case 2:
			text_print_string_win(7, 1, "SOUTH");
			break;
		case 3:
			text_print_string_win(7, 1, "WEST ");
			break;
	}
	
	if (keys > 0) {
		if (keys & J_UP) {
			changed = player_move(forward[hero.direction], &newState);
			if (newState != SCREEN_SAME) {
				return newState;
			}
		}
		if (keys & J_DOWN) {
			changed = player_move(backward[hero.direction], &newState);
			if (newState != SCREEN_SAME) {
				return newState;
			}
		}
		if (keys & J_RIGHT) {
			hero.direction = (hero.direction + 1) % 4;
			changed = true;
		}
		if (keys & J_LEFT) {
			hero.direction = hero.direction > 0 ? hero.direction - 1 : 3;
			changed = true;
		}
		if (keys & J_B) {
			toggleTorch();
			changed = true;
		}

		if (keys & J_START) {
			healing(true);
			changed = true;
		}
	}
		
	if (changed) {
		draw_dungeon(x, y + Y_BUFFERS[y_buffer]);
		printHeroStats(x, y + Y_BUFFERS[y_buffer]);
		swap_buffer();
	}
	
	return SCREEN_SAME;	
}