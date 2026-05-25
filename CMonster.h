#pragma once
#include "CObj.h"
class CMonster :
    public CObj
{
public:
    CMonster() {}
    virtual ~CMonster() { Release(); }

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;
};

