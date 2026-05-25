#pragma once
#include "CObj.h"

class CBullet : public CObj
{
public:
    CBullet();
    virtual ~CBullet();

public:
    virtual void Initialize() override;
    virtual int  Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

public:
    void SetVelocity(float fVX, float fVY) { m_fVX = fVX; m_fVY = fVY; }
    void SetType(OBJID ID) { m_eType = ID; }

private:
    OBJID m_eType;
    float m_fVX;
    float m_fVY;
};