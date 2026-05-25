#pragma once
#include "CObj.h"
#include "CAFObj.h"
#include "CBullet.h"

class CPlayer : public CObj
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
    const int   GetShield() const { return m_iShild; }
    const int   GetLevel()  const { return m_iLevel; }
    const float GetEXPPer() const { return (m_fEXP / m_fMaxEXP) * 100.f; }

    int GetWave() const { return m_iWave; }
    void SetWave(int iWave) { m_iWave = iWave; }

    int GetKillCount() const { return m_iKillCount; }
    void AddKillCount() { ++m_iKillCount; }
    void ResetKillCount() { m_iKillCount = 0; }

public:
    template<typename T>
    CObj* CreateBullet()
    {
        CObj* pObj = CAFObj<T>::Create();
        if (pObj)
        {
            pObj->Initialize();
            pObj->SetPos(m_tInfo.fX, m_tInfo.fY - 20.f);

            CBullet* pBullet = static_cast<CBullet*>(pObj);
            pBullet->SetVelocity(0.f, -3.5f);
        }
        return pObj;
    }

private:
    int   m_iLevel;
    int   m_iShild;
    int   m_iWave;
    int   m_iKillCount;
    float m_fEXP;
    float m_fMaxEXP;
    float m_fAttackDelay;
    float m_fAttackTimer;
};