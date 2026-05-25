#pragma once
#include "CSceneBase.h"
class CWin :
    public CSceneBase
{
public:
    CWin() {}
    virtual ~CWin() {  Release();}

public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;
};

