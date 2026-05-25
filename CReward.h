#pragma once
#include "CObj.h"

class CReward : public CObj {
public:
    CReward();
    virtual ~CReward();

public:
    virtual void Initialize() override;
    virtual int  Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

public:
    void SetRewardInfo(REWARD_TYPE eType, float fVal);
    REWARD_TYPE GetRewardType() const { return m_eType; }
    float GetSoulValue() const { return m_fValue; }

private:
    REWARD_TYPE m_eType;
    DWORD       m_dwExpireTick;
    float       m_fValue;
    float       m_fDirX;
    float       m_fDirY;
    int         m_iBounceCount;
};