#ifndef _TEXT_H
#define _TEXT_H

#include <stdbool.h>

#define TEXT_FONT_OFFSET 0xB0
#define TEXT_ICON_OFFSET 0xE2

#define _TEXT_CHAR_A              TEXT_FONT_OFFSET
#define _TEXT_CHAR_0              TEXT_FONT_OFFSET + 26
#define _TEXT_CHAR_APOSTROPHE     TEXT_FONT_OFFSET + 26 + 10 + 0
#define _TEXT_CHAR_DASH           TEXT_FONT_OFFSET + 26 + 10 + 1
#define _TEXT_CHAR_DOT            TEXT_FONT_OFFSET + 26 + 10 + 2
#define _TEXT_CHAR_COMMA          TEXT_FONT_OFFSET + 26 + 10 + 3
#define _TEXT_CHAR_COLON          TEXT_FONT_OFFSET + 26 + 10 + 4
#define _TEXT_CHAR_EXCLAMATION    TEXT_FONT_OFFSET + 26 + 10 + 5
#define _TEXT_CHAR_INTERROGATION  TEXT_FONT_OFFSET + 26 + 10 + 6
#define _TEXT_CHAR_LPARENTHESES   TEXT_FONT_OFFSET + 26 + 10 + 7
#define _TEXT_CHAR_RPARENTHESES   TEXT_FONT_OFFSET + 26 + 10 + 8
#define _TEXT_CHAR_TOFU           TEXT_FONT_OFFSET + 26 + 10 + 9
#define _TEXT_CHAR_BORDER         TEXT_FONT_OFFSET + 26 + 10 + 10
#define _TEXT_CHAR_SPACE          TEXT_FONT_OFFSET + 26 + 10 + 11
#define _TEXT_CHAR_SLASH          TEXT_FONT_OFFSET + 26 + 10 + 12
#define _TEXT_CHAR_PLUS           TEXT_FONT_OFFSET + 26 + 10 + 13
/*#define _TEXT_CHAR_HEART          TEXT_FONT_OFFSET + 26 + 10 + 14
#define _TEXT_CHAR_BALLOON        TEXT_FONT_OFFSET + 26 + 10 + 15
#define _TEXT_CHAR_PUNCH          TEXT_FONT_OFFSET + 26 + 10 + 16
#define _TEXT_CHAR_LIGHT          TEXT_FONT_OFFSET + 26 + 10 + 17
#define _TEXT_CHAR_FLASK          TEXT_FONT_OFFSET + 26 + 10 + 18
#define _TEXT_CHAR_KEY            TEXT_FONT_OFFSET + 26 + 10 + 19
#define _TEXT_CHAR_GOLD           TEXT_FONT_OFFSET + 26 + 10 + 20
#define _TEXT_CHAR_LEVEL          TEXT_FONT_OFFSET + 26 + 10 + 21
#define _TEXT_CHAR_XP             TEXT_FONT_OFFSET + 26 + 10 + 22
#define _TEXT_CHAR_TORCH_HANDLE   TEXT_FONT_OFFSET + 26 + 10 + 23
#define _TEXT_CHAR_TORCH_TIP      TEXT_FONT_OFFSET + 26 + 10 + 24
#define _TEXT_CHAR_TORCH_FIRE     TEXT_FONT_OFFSET + 26 + 10 + 25
#define _TEXT_CHAR_SWORD          TEXT_FONT_OFFSET + 26 + 10 + 26
#define _TEXT_CHAR_SHIELD         TEXT_FONT_OFFSET + 26 + 10 + 27
#define _TEXT_CHAR_BOW            TEXT_FONT_OFFSET + 26 + 10 + 28
#define _TEXT_CHAR_BED            TEXT_FONT_OFFSET + 26 + 10 + 29*/

// a: HEART
// b: BALLOON
// c: PUNCH
// d: LIGHT
// e: KEY
// f: FLASK
// g: GOLD
// h: LEVEL
// i: XP
// j: TORCH HANDLE
// k: TORCH TIP
// l: TORCH FIRE
// m: SWORD
// n: SHIELD
// o: BOW
// p: BED
// q: DICE
// r: SELECTED LEFT
// s: SELECTED TOP
// t: MAP WALL
// u: MAP DOOR
// v: MAP EGG
// w: MAP FLOOR
// x:
// y:
// z: zz (sleeping)

void text_load_font();

void text_print_char(UINT8 x, UINT8 y, unsigned char chr, bool win);
void text_print_string(UINT8 x, UINT8 y, unsigned char *string, bool win);

void text_print_string_bkg(UINT8 x, UINT8 y, unsigned char *string);
void text_print_string_win(UINT8 x, UINT8 y, unsigned char *string);



#endif