#pragma once
#include "../Manager/CMgrBase.h"

class CGameMgr :
    public CMgrBase
{
public:
    CGameMgr();
    virtual ~CGameMgr() { Release(); }

public:
    // CMgrBase을(를) 통해 상속됨
    void Initialize(HWND hWnd) override;
    void Update() override;
    void LateUpdate() override;
    void Render() override;
    void Release() override;
};

