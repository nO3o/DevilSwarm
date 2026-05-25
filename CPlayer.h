#pragma once
#include "CObj.h"
class CPlayer :
    public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void Initialize() override;
    int  Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void KeyInput();

public:
    void RestoreHP() { m_iHP = m_iMaxHP; }
    void HealHP(int HP) { m_iHP += HP; }
    void IncreaseHP(int MaxHP) { m_iMaxHP = MaxHP; RestoreHP(); }

public:
    const int GetLevel() const { return m_iLevel; }
    const int GetEXP() const { return m_iEXP; }
    const int GetMaxEXP() const { return m_iMaxEXP; }
    const int GetShield() const { return m_iShild; }

public:
    template<typename T>
    CObj* CreateBullet();

private:
    int m_iLevel;
    int m_iEXP;
    int m_iMaxEXP;
    int m_iShild;
    float m_fAttackDelay;
    float m_fAttackTimer;
};