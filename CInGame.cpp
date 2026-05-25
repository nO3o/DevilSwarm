#include "pch.h"
#include "CInGame.h"
#include "CGameMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"

void CInGame::Initialize()
{

    m_rcUI[HUD_XP_BAR] = { 0, 20, 800, 55 };
    m_rcUI[HUD_LEVEL] = { 10, 20, 100, 55 };

    m_rcUI[HUD_BOTTOM_BG] = { 0, 540, 800, 600 };
    m_rcUI[HUD_HP_BAR] = { 0, 540, 400, 600 };
    m_rcUI[HUD_SHIELD_BAR] = { 400, 540, 800, 600 };


    m_pPlayer = (static_cast<CPlayer*>(CObjMgr::GetInstance()->GetObj(OBJ_PLAYER).front()));
}

void CInGame::Update()
{
}

void CInGame::LateUpdate()
{
}

void CInGame::Render(HDC hDC)
{

    CObjMgr::GetInstance()->Render(hDC);

    SetBkMode(hDC, TRANSPARENT);


    if (m_pPlayer != nullptr)
    {
        WCHAR szXp[32];
        swprintf_s(szXp, L"경험치 %d / %d", m_pPlayer->GetEXP(), m_pPlayer->GetMaxEXP());
        DrawTextW(hDC, szXp, -1, &m_rcUI[HUD_XP_BAR], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    if (m_pPlayer != nullptr) {
        WCHAR szLevel[16];
        swprintf_s(szLevel, L"레벨 %d", m_pPlayer->GetLevel());
        DrawTextW(hDC, szLevel, -1, &m_rcUI[HUD_LEVEL], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    Rectangle(hDC, 0, 540, 800, 600);

    if (m_pPlayer != nullptr)
    {
        WCHAR szHp[32];
        swprintf_s(szHp, L"체력 %d / %d", m_pPlayer->GetHP(), m_pPlayer->GetMaxHP());
        DrawTextW(hDC, szHp, -1, &m_rcUI[HUD_HP_BAR], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    MoveToEx(hDC, 400, 540, NULL);
    LineTo(hDC, 400, 600);
    if (m_pPlayer != nullptr)
    {
        WCHAR szShield[32];
        swprintf_s(szShield, L"보호막 %d", m_pPlayer->GetShield());
        DrawTextW(hDC, szShield, -1, &m_rcUI[HUD_SHIELD_BAR], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

}

void CInGame::Release()
{
}
