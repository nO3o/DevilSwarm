#include "pch.h"
#include "CWin.h"
#include "CGameMgr.h"

void CWin::Initialize() {}

void CWin::Update()
{
    if (GetAsyncKeyState(VK_RETURN)) {
        CGameMgr::GetInstance()->SetState(GS_TITLE);
    }
}

void CWin::LateUpdate() {}

void CWin::Render(HDC hDC)
{
    RECT rcWin = { (LONG)(WINCX * 0.5f - 200), (LONG)(WINCY * 0.5f - 100), (LONG)(WINCX * 0.5f + 200), (LONG)(WINCY * 0.5f + 100) };
    Rectangle(hDC, rcWin.left, rcWin.top, rcWin.right, rcWin.bottom);

    SetBkMode(hDC, TRANSPARENT);
    TCHAR szWinText[] = TEXT("승리!! 게임 클리어!!");
    TextOut(hDC, (int)(WINCX * 0.5f - 85), (int)(WINCY * 0.5f - 20), szWinText, lstrlen(szWinText));

    TCHAR szSubText[] = TEXT("엔터 키 입력 시 타이틀 화면으로 돌아갑니다.");
    TextOut(hDC, (int)(WINCX * 0.5f - 70), (int)(WINCY * 0.5f + 10), szSubText, lstrlen(szSubText));
    SetBkMode(hDC, OPAQUE);
}

void CWin::Release() {}
