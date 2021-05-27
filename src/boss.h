#ifndef _BOSS_H
#define _BOSS_H

typedef struct
{
	UINT16 LVL;

	UINT16 HP_MAX;
	INT16 HP;
	UINT8 DEF;
	UINT8 ATT;
	bool dead;
	UINT16 state;
} Boss;

extern Boss boss;

extern void initBoss(UINT16 level);

extern void drawBossState(unsigned int x, unsigned int y);

// DRAW BOSS
extern void draw_boss(unsigned int x, unsigned int y);
extern void draw_boss_attack(unsigned int x, unsigned int y);


extern void bossAssault(UINT8 action_type);
extern void hitBoss(UINT8 action_type);
extern UINT8 bossAssaultResolution(UINT8 action_type);
extern UINT8 state_boss();

#endif