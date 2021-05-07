#include <gb/gb.h>
#include "./font/font.tileset.h"
#include "./text.h"

void text_load_font() {
    set_bkg_data(TEXT_FONT_OFFSET, FONT_TILESET_TILE_COUNT, FONT_TILESET);
}

// Write the given char at the (x, y) position on the background or window layer
void text_print_char(UINT8 x, UINT8 y, unsigned char chr, bool win) {
    UINT16 tile = _TEXT_CHAR_TOFU;

    if (chr >= 'a' && chr <= 'z') {
        tile = TEXT_ICON_OFFSET + chr - 'a';
    } else
	if (chr >= 'A' && chr <= 'Z') {
        tile = _TEXT_CHAR_A + chr - 'A';
    } else if (chr >= '0' && chr <= '9') {
        tile = _TEXT_CHAR_0 + chr - '0';
    } else {
        switch (chr) {
            case '\'':
                tile = _TEXT_CHAR_APOSTROPHE;
                break;
            case '-':
                tile = _TEXT_CHAR_DASH;
                break;
            case '.':
                tile = _TEXT_CHAR_DOT;
                break;
            case ',':
                tile = _TEXT_CHAR_COMMA;
                break;
            case ':':
                tile = _TEXT_CHAR_COLON;
                break;
            case '!':
                tile = _TEXT_CHAR_EXCLAMATION;
                break;
            case '?':
                tile = _TEXT_CHAR_INTERROGATION;
                break;
            case '(':
                tile = _TEXT_CHAR_LPARENTHESES;
                break;
            case ')':
                tile = _TEXT_CHAR_RPARENTHESES;
                break;
            case ' ':
                tile = _TEXT_CHAR_SPACE;
                break;
			case '_':
                tile = _TEXT_CHAR_BORDER;
                break;
			case '/':
                tile = _TEXT_CHAR_SLASH;
                break;
			case '+':
                tile = _TEXT_CHAR_PLUS;
                break;			
        }
    }

    win
		? set_win_tiles(x, y, 1, 1, &tile)
		: set_bkg_tiles(x, y, 1, 1, &tile);
}

// Write the given string at the (x, y) position on the window layer
// Line feed (\n) allowed
void text_print_string(UINT8 x, UINT8 y, unsigned char *string, bool win) {
    UINT8 offset_x = 0;
    UINT8 offset_y = 0;

    while (string[0]) {
        if (string[0] == '\n') {
            offset_x = 0;
            offset_y += 1;
        } else {
            text_print_char(x + offset_x, y + offset_y, (unsigned char) string[0], win);
            offset_x += 1;
        }

        string += 1;  // Increment pointer address, /!\ THIS IS DANGEROUS!
    }
}

void text_print_string_win(UINT8 x, UINT8 y, unsigned char *string) {
	text_print_string(x, y,string, true);
}

void text_print_string_bkg(UINT8 x, UINT8 y, unsigned char *string) {
	text_print_string(x, y,string, false);
}