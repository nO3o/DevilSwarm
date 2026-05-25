#pragma once
#include "CSceneBase.h"
class CLose :
    public CSceneBase
{
public:
    CLose() {}
    virtual ~CLose() {}
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;
};

