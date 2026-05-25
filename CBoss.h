#pragma once
#include "CObj.h"

class CBoss : public CObj
{
public:
    CBoss();
    virtual ~CBoss();

public:
    virtual void Initialize() override;
    virtual int  Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

private:
    void CheckPhase();
    void FirePhase1();
    void FirePhase2();
    void FirePhase3Spiral();

private:
    BOSS_PHASE m_ePhase;
    float      m_fSpiralAngle;
    float      m_fMoveDirX;
    DWORD      m_dwFireTick;
};