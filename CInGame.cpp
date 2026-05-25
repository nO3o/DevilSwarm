#include "pch.h"
#include "CInGame.h"
#include "CGameMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CBoss.h"
#include "CEnemy.h"

void CInGame::Initialize()
{
	m_dwSpawnTick = GetTickCount();
	m_iKillCount = 0;
	m_bBossSpawned = false;

	m_rcUI[HUD_XP_BAR] = { 0, 20, 800, 55 };
	m_rcUI[HUD_LEVEL] = { 10, 20, 100, 55 };

	m_rcUI[HUD_BOTTOM_BG] = { 0, 540, 800, 600 };
	m_rcUI[HUD_HP_BAR] = { 0, 540, 400, 600 };
	m_rcUI[HUD_SHIELD_BAR] = { 400, 540, 800, 600 };

	m_pPlayer = static_cast<CPlayer*>(CObjMgr::GetInstance()->GetPlayer());

	CObjMgr::GetInstance()->Initialize();
}

void CInGame::Update()
{
	
	DWORD dwNow = GetTickCount();

	if (dwNow - m_dwSpawnTick > 1500)
	{
		SpawnEnemy();
		m_dwSpawnTick = dwNow;
	}

	if (m_iKillCount >= 15 && !m_bBossSpawned)
	{
		SpawnBoss();
	}

	CObjMgr::GetInstance()->Update();

	if (m_bBossSpawned && (CObjMgr::GetInstance()->GetObjList(OBJ_BOSS).empty() || CObjMgr::GetInstance()->GetObjList(OBJ_BOSS).front()->GetDead()))
	{
		CGameMgr::GetInstance()->SetState(GS_CLEAR);
	}
}

void CInGame::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CInGame::Render(HDC hDC)
{
	SetBkMode(hDC, TRANSPARENT);

	CObjMgr::GetInstance()->Render(hDC);

	if (m_pPlayer != nullptr)
	{
		WCHAR szXp[32];
		swprintf_s(szXp, L"경험치 %.2f%%", m_pPlayer->GetEXPPer());
		DrawTextW(hDC, szXp, -1, &m_rcUI[HUD_XP_BAR], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	if (m_pPlayer != nullptr)
	{
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
	CObjMgr::GetInstance()->Release();
}

void CInGame::SpawnEnemy()
{
	CEnemy* pEnemy = new CEnemy;
	pEnemy->Initialize(ET_STRAIGHT);
	pEnemy->SetPos((float)(50 + rand() % 700), -50.f);

	CObjMgr::GetInstance()->AddObject(OBJ_ENEMY, pEnemy);
}

void CInGame::SpawnBoss()
{
	CBoss* pBoss = new CBoss;
	pBoss->Initialize();
	pBoss->SetPos(400.f, 100.f);

	CObjMgr::GetInstance()->AddObject(OBJ_BOSS, pBoss);

	m_bBossSpawned = true;
}