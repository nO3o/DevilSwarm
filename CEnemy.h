#pragma once
#include "CObj.h"

class CEnemy : public CObj {
public:
    CEnemy();
    virtual ~CEnemy();

public:
    virtual void Initialize() override;
    void Initialize(ENEMY_TYPE eType);

    virtual int  Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

public:
    void SetEnemyType(ENEMY_TYPE eType);

private:
    void FireStraight(float fPlayerX, float fPlayerY);
    void FireSpread8();

private:
    ENEMY_TYPE m_eType;
    DWORD      m_dwFireTick;
    int        m_iSpreadIdx;
};