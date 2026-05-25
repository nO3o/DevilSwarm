#include "pch.h"
#include "CTitle.h"
#include "CGameMgr.h"

void CTitle::Initialize()
{
}

void CTitle::Update()
{

	if (GetAsyncKeyState(VK_UP)) {
        --m_iMenu;
        if (m_iMenu < 0)
            m_iMenu = TM_END - 1;
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
        ++m_iMenu;
        if (m_iMenu >= TM_END) m_iMenu = 0;

	}
	else if (GetAsyncKeyState(VK_RETURN)) {
		if (m_iMenu == TM_START)
			CGameMgr::GetInstance()->SetState(GS_LOBBY);
		else
			PostQuitMessage(0);
	}
}

void CTitle::LateUpdate()
{
}

void CTitle::Render(HDC hDC) {

	SetBkMode(hDC, TRANSPARENT);
	DrawTextW(hDC, L"SKY WAR", -1, &rcLogo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    for (int i = 0; i < TM_END; ++i)
    {
        if (i == m_iMenu)
        {
            WCHAR szSelected[64];
            swprintf_s(szSelected, L"▶ %s", menuTexts[i]);
            DrawTextW(hDC, szSelected, -1, &menuRects[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
        else
        {
            // 선택되지 않은 메뉴: 기본 색상 및 화살표 없음
            DrawTextW(hDC, menuTexts[i], -1, &menuRects[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}

void CTitle::Release()
{
}
