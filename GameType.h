#pragma once

typedef struct tagInfo {
	float fX, fY;
	float fCX, fCY;
}INFO;

typedef struct tagBullet {
	float fX, fY;
	float fVX, fVY;
	bool  bAlive;
	bool  bFromPlayer; 
} BULLET;

enum GAME_STATE {
    GS_TITLE,
    GS_LOBBY,
    GS_STAGE_SELECT,
    GS_SQUAD,
    GS_INGAME,
    GS_LEVELUP_CARD,
    GS_PAUSED,
    GS_CLEAR,
    GS_GAMEOVER,
    GS_END
};

enum OBJID {
	OBJ_PLAYER,
	OBJ_PLAYER_BULLET,
	OBJ_ENEMY,
	OBJ_ENEMY_BULLET,
	OBJ_BOSS,
	OBJ_REWARD,
	OBJ_END
};

enum ENEMY_TYPE {
	ET_STRAIGHT,
	ET_ZIGZAG,
	ET_DRONE,
	ET_ELITE
};

enum REWARD_TYPE {
	RT_SOUL,
	RT_SOUL02,
	RT_SOUL03,
	RT_END
};

enum BOSS_PHASE {
	BP_ONE,
	BP_TWO,
	BP_THREE
};

enum HUD_UI_INDEX {
	HUD_XP_BAR,
	HUD_LEVEL,
	HUD_BOTTOM_BG,
	HUD_HP_BAR,
	HUD_SHIELD_BAR,
	HUD_END
};

