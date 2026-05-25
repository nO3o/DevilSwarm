#pragma once

typedef struct tagInfo {
	float fX, fY;
	float fCX, fCY;
}INFO;

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

enum MOB_ID {
    MONSTER_A,
    MONSTER_B,
    MONSTER_SHILD,
    MONSTER_BOOM,
    MONSTER_ELITE,
    BOOS_BUTCHER,
    BOOS_DIABLO,
    MOB_END
};