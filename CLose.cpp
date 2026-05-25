#include "pch.h"
#include "CLose.h"
#include "CGameMgr.h"

void CLose::Initialize()
{
}

void CLose::Update()
{
}

void CLose::LateUpdate()
{
}

void CLose::Render(HDC hDC)
{
    RECT rcWin = { (LONG)(WINCX * 0.5f - 200), (LONG)(WINCY * 0.5f - 100), (LONG)(WINCX * 0.5f + 200), (LONG)(WINCY * 0.5f + 100) };
    Rectangle(hDC, rcWin.left, rcWin.top, rcWin.right, rcWin.bottom);

    SetBkMode(hDC, TRANSPARENT);

    RECT rcTitle = rcWin;
    rcTitle.bottom -= 40; 
    DrawText(hDC, TEXT("패배!!"), -1, &rcTitle, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    RECT rcSub = rcWin;
    rcSub.top += 40;
    DrawText(hDC, TEXT("엔터 키 입력 시 타이틀 화면으로 돌아갑니다."), -1, &rcSub, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SetBkMode(hDC, OPAQUE);

    if (GetAsyncKeyState(VK_RETURN) & 0x0001)
        CGameMgr::GetInstance()->SetState(GS_TITLE);
}

void CLose::Release()
{
}
