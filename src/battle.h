#ifndef _BATTLE_H
#define _BATTLE_H

// BLOBS
#define BLOB_FAR_LEFT_LSIDE 22
#define BLOB_FAR_RIGHT_LSIDE 23
#define BLOB_FAR_LEFT_MIDDLE 24
#define BLOB_FAR_RIGHT_MIDDLE 25
#define BLOB_FAR_LEFT_RSIDE 26
#define BLOB_FAR_RIGHT_RSIDE 27

#define BLOB_NEAR_LEFT_LSIDE 28
#define BLOB_NEAR_RIGHT_LSIDE 29
#define BLOB_NEAR_LEFT_MIDDLE 30
#define BLOB_NEAR_RIGHT_MIDDLE 31
#define BLOB_NEAR_LEFT_RSIDE 32
#define BLOB_NEAR_RIGHT_RSIDE 33

typedef struct
{
	UINT8 LVL;

	UINT16 HP_MAX;
	INT16 HP;
	UINT8 DEF;
	UINT8 ATT;
	bool dead;
	UINT8 index;
	UINT16 state;
} Blob;

typedef struct
{
	UINT8 LVL;
	Blob blob[6]; // { far_left, far, far_right, near_left, near, near_right }
} Battlefield;

extern const UINT8 blob_state_position[6][2];
extern const int blob_position[12][2];
extern Battlefield battlefield;

extern UINT8 countBlobs();
extern void initBlob(UINT8 index, UINT8 level);
extern void initBattlefield(UINT8 level);
extern void updateBattlefield();
extern void drawBlobSide(UINT8 blob);
extern void drawBlobSprite(UINT8 blob);
extern void hideBlobSide(UINT8 blob);
extern void hideBlobSprite(UINT8 blob);
extern void drawBlobState(UINT8 index, unsigned int x, unsigned int y);
extern void drawBlob(UINT8 index, unsigned int x, unsigned int y);
extern void drawBattlefield(unsigned int x, unsigned int y);

// DRAW BATTLEFIELD
extern void draw_battlefield(unsigned int x, unsigned int y, bool draw_enemies);

extern UINT16 battle_gold_loot;
extern bool battle_herb_loot;

extern UINT8 state_level_up();
extern UINT8 state_battle_loose();
extern UINT8 state_battle_win();

extern void blobsAssault(UINT8 action_type);
extern void hitBlob(UINT8 index, UINT8 action_type);
extern UINT8 assaultResolution(UINT8 action_type, UINT8 direction);
extern UINT8 state_battle();
extern UINT8 state_battle_near_attack();
extern UINT8 state_battle_far_attack();

extern UINT8 blobIndexToSprite(UINT8 index);

extern void initBlobsPalette();
#endif