#include "pch.h"
#include "CTitle.h"
#include "CAFObj.h"
#include "CGameMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"

void CTitle::Initialize()
{
    CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAFObj<CPlayer>::Create());
}

void CTitle::Update()
{

	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		--m_iMenu;
		if (m_iMenu < 0)
			m_iMenu = TITLE_MENU::TM_END - 1;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		++m_iMenu;
		if (m_iMenu >= TITLE_MENU::TM_END)
			m_iMenu = 0;
	}
	else if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		if (m_iMenu == TITLE_MENU::TM_START)
			CGameMgr::GetInstance()->SetState(GS_INGAME);
		else
			PostQuitMessage(0);
	}
}

void CTitle::LateUpdate()
{
}

void CTitle::Render(HDC hDC) {

	SetBkMode(hDC, TRANSPARENT);
	DrawTextW(hDC, L"SKY WAR", -1, &m_rcLogo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    for (int i = 0; i < TM_END; ++i)
    {
        if (i == m_iMenu)
        {
            WCHAR szSelected[64];
            swprintf_s(szSelected, L"¢º %s", m_menuTexts[i]);
            DrawTextW(hDC, szSelected, -1, &m_menuRects[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
        else
        {
            DrawTextW(hDC, m_menuTexts[i], -1, &m_menuRects[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
}

void CTitle::Release()
{
}
