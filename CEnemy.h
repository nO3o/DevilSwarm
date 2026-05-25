#pragma once
#include "CObj.h"
class CEnemy :
    public CObj
{
public:
    CEnemy():m_eID(MOB_END) {}
    virtual ~CEnemy() {}

public:
    void Initialize() override;
    int  Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;
    
private:
    template<typename T>
    CObj* CreateMonster(MOB_ID ID);

private:
    MOB_ID m_eID;
};

