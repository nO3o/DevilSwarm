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

	CObjMgr::GetInstance()->Initialize();
	m_pPlayer = static_cast<CPlayer*>(CObjMgr::GetInstance()->GetPlayer());


	if (m_pPlayer)
	{
		m_pPlayer->SetWave(1);
		m_pPlayer->ResetKillCount();
	}
	m_iKillCount = 0;
	m_iMaxKillCount = 15;
}

void CInGame::Update()
{
	if (m_pPlayer->GetDead()) {
		CGameMgr::GetInstance()->SetState(GS_GAMEOVER);
		m_pPlayer->RestoreHP();
	}

	DWORD dwNow = GetTickCount();

	if (dwNow - m_dwSpawnTick > 1500)
	{
		SpawnEnemy();
		m_dwSpawnTick = dwNow;
	}

	if (m_pPlayer != nullptr)
	{
		m_iKillCount = m_pPlayer->GetKillCount();
		int iCurrentWave = m_pPlayer->GetWave();

		if (m_iKillCount >= m_iMaxKillCount && !m_bBossSpawned)
		{
			if (iCurrentWave < 3)
			{
				iCurrentWave += 1;
				m_pPlayer->SetWave(iCurrentWave); 
				m_pPlayer->ResetKillCount(); 
				m_iKillCount = 0;    

			
				m_iMaxKillCount = 15 * iCurrentWave;

			}
			else if (iCurrentWave == 3)
				SpawnBoss();
		}
	}


	CObjMgr::GetInstance()->Update();

	if (m_bBossSpawned) 
	{
		const auto& BossList = CObjMgr::GetInstance()->GetObjList(OBJ_BOSS);

		if (CObjMgr::GetInstance()->GetObjList(OBJ_BOSS).empty() || CObjMgr::GetInstance()->GetObjList(OBJ_BOSS).front()->GetDead())
		{
			CGameMgr::GetInstance()->SetState(GS_CLEAR);
		}
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
		WCHAR szWave[32];
		swprintf_s(szWave, L"WAVE : %d", m_pPlayer->GetWave());
		RECT rcWave = { 250, 65, 400, 100 };
		DrawTextW(hDC, szWave, -1, &rcWave, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

		WCHAR szKill[32];
		swprintf_s(szKill, L"KILL : %d / %d", m_iKillCount, m_iMaxKillCount);
		RECT rcKill = { 450, 65, 650, 100 };
		DrawTextW(hDC, szKill, -1, &rcKill, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}

	if (m_pPlayer != nullptr)
	{
		WCHAR szXp[32];
		swprintf_s(szXp, L"경험치 %.2f%%", m_pPlayer->GetEXPPer());
		DrawTextW(hDC, szXp, -1, &m_rcUI[HUD_XP_BAR], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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

		MoveToEx(hDC, 400, 540, NULL);
		LineTo(hDC, 400, 600);
	
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