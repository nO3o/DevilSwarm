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
    void RestoreHP() { m_fHP = m_fMaxHP; }
    void HealHP(float HP) { m_fHP += HP; }
    void IncreaseHP(float MaxHP) { m_fMaxHP = MaxHP; RestoreHP(); }

private:
    float m_fMaxHP;
    float m_fShild;
    float m_fRageCurrent;
    float m_fRageMax;
    float m_fRageRate;
};

