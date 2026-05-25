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
    OBJ_BULLET, 
    OBJ_MONSTER, 
    OBJ_SHIELD, 
    OBJ_SOUL,
    OBJ_ITEM, 
    OBJ_UI, 
    OBJ_END 
};

enum ENEMY_TYPE {
	ET_STRAIGHT,
	ET_ZIGZAG, 
	ET_DRONE,  
	ET_ELITE,     
	ET_END
};

enum REWARD_TYPE {
	RT_GOLD, 
	RT_ITEM_NORM,  
	RT_ITEM_RARE, 
	RT_END
};

enum BOSS_PHASE {
	BP_ONE = 1,   
	BP_TWO = 2, 
	BP_THREE = 3  
};

