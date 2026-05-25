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
    bool IncreaseEXP(float EXP);

public:
    const int GetShield() const { return m_iShild; }
    const int   GetLevel() const { return m_iLevel; }
    const float GetEXPPer() const { return m_fEXP/m_fMaxEXP*100.f; }

public:
    template<typename T>
    CObj* CreateBullet();

private:
    int m_iLevel;
    int m_iShild;
    float m_fEXP;
    float m_fMaxEXP;
    float m_fAttackDelay;
    float m_fAttackTimer;
};