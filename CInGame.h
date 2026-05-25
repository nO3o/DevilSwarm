#pragma once
#include "CSceneBase.h"
class CPlayer;

class CInGame :
    public CSceneBase
{
public:
    CInGame() {}
    virtual ~CInGame() { Release(); }

public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void SpawnEnemy();
    void SpawnBoss();

public:
    enum HUD_INDEX {
        HUD_XP_BAR,
        HUD_LEVEL,
        HUD_WAVE,
        HUD_TIMER,
        HUD_BOTTOM_BG,
        HUD_HP_BAR,
        HUD_SHIELD_BAR,
        HUD_END
    };

    RECT m_rcUI[HUD_END];
    CPlayer* m_pPlayer;

private:
    DWORD m_dwSpawnTick;
    int m_iKillCount;
    int m_iMaxKillCount;
    bool m_bBossSpawned;
};

