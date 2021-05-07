#ifndef _EXPLORATION_H
#define _EXPLORATION_H

// MAP CODES
#define MAP_FLOOR 		 		 0 // 0b00000000
#define MAP_WALL 		 		 1 // 0b00000001	
#define MAP_DOOR_OPENED  		 2 // 0b00000010
#define MAP_DOOR_CLOSED  		 3 // 0b00000011
#define MAP_EGG_OPENED   		 4 // 0b00000100
#define MAP_EGG_CLOSED   		 8 // 0b00001000
#define MAP_KEY		    		16 // 0b00010000
#define MAP_EGG_CLOSED_WITH_KEY 24 // MAP_EGG_CLOSED | MAP_KEY
#define MAP_EGG_OPENED_WITH_KEY 20 // MAP_EGG_OPENED | MAP_KEY
#define MAP_INN					34 // 0b00100010
#define MAP_BLACKSMITH			66 // 0b01000010		
#define MAP_KNIGHT  			98 // 0b01100010		

extern unsigned int level[25][25];

extern int level_width;
extern int level_height;

extern const int directions[4][2];

extern const int right   [4];
extern const int left    [4];
extern const int forward [4];
extern const int backward[4];


extern void get_cell_position(int position[2], int direction, int distance, int* result);

extern unsigned int get_cell_content(int position[2]);

extern void set_cell_content(int position[2], unsigned int value);

extern void draw_dungeon(unsigned int x, unsigned int y);

extern bool player_move(int direction, UINT8* newState);


// DRAW BACKGROUND
extern void draw_background(unsigned int x, unsigned int y);

// DRAW WALLS

extern void draw_center_far(unsigned int x, unsigned int y);
extern void draw_left_far_front(unsigned int x, unsigned int y);
extern void draw_left_far_side(unsigned int x, unsigned int y);
extern void draw_left_near_side(unsigned int x, unsigned int y);
extern void draw_left_near_front(unsigned int x, unsigned int y);
extern void draw_left_side(unsigned int x, unsigned int y);
extern void draw_right_far_front(unsigned int x, unsigned int y);
extern void draw_right_far_side(unsigned int x, unsigned int y);
extern void draw_right_near_side(unsigned int x, unsigned int y);
extern void draw_right_near_front(unsigned int x, unsigned int y);
extern void draw_center_near(unsigned int x, unsigned int y);
extern void draw_right_side(unsigned int x, unsigned int y);

// DRAW DOORS

extern void draw_door_closed_center_near(unsigned int x, unsigned int y);
extern void draw_door_opened_center_near(unsigned int x, unsigned int y);
extern void draw_door_closed_center_far(unsigned int x, unsigned int y);
extern void draw_door_opened_center_far(unsigned int x, unsigned int y);
extern void draw_door_closed_right_far_front(unsigned int x, unsigned int y);
extern void draw_door_opened_right_far_front(unsigned int x, unsigned int y);
extern void draw_door_closed_left_far_front(unsigned int x, unsigned int y);
extern void draw_door_opened_left_far_front(unsigned int x, unsigned int y);
extern void draw_door_closed_right_side(unsigned int x, unsigned int y);
extern void draw_door_opened_right_side(unsigned int x, unsigned int y);
extern void draw_door_closed_left_side(unsigned int x, unsigned int y);
extern void draw_door_opened_left_side(unsigned int x, unsigned int y);
extern void draw_door_right_near_side(unsigned int x, unsigned int y);
extern void draw_door_left_near_side(unsigned int x, unsigned int y);
extern void draw_door_right_far_side(unsigned int x, unsigned int y);
extern void draw_door_left_far_side(unsigned int x, unsigned int y);

UINT8 state_exploration();

#endif