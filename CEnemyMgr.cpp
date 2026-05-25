#include "pch.h"
#include "CEnemyMgr.h"

IMPLEMENT_SINGLETON(CEnemyMgr)

CEnemyMgr::CEnemyMgr()
	: m_pBoss(nullptr)
	, m_iWave(1), m_iKillCount(0), m_iGold(0)
	, m_dwSpawnTick(0), m_dwWaveTick(0)
	, m_bBossSpawned(false)
	, m_bPlayerHit(false), m_dwHitMsgTick(0)
{
	m_szHitMsg[0] = TEXT('\0');
}
CEnemyMgr::~CEnemyMgr() {}

void CEnemyMgr::Initialize()
{
	m_dwSpawnTick = GetTickCount();
	m_dwWaveTick = GetTickCount();
}

void CEnemyMgr::Update()
{
	DWORD dwNow = GetTickCount();

	if (dwNow - m_dwSpawnTick > 1500 && !m_bBossSpawned) {
		m_dwSpawnTick = dwNow;
		SpawnEnemy();
	}

	if (m_iKillCount >= 15 && !m_bBossSpawned) {
		SpawnBoss();
		m_bBossSpawned = true;
	}

	for (auto& pEnemy : m_EnemyList) {
		if (!pEnemy->IsAlive()) continue;
		pEnemy->Update(m_pPlayer->fX, m_pPlayer->fY);

		if (pEnemy->HasPendingBullet())
			m_BulletList.push_back(pEnemy->GetPendingBullet());
	}

	if (m_pBoss && m_pBoss->IsAlive()) {
		m_pBoss->Update(m_pPlayer->fX, m_pPlayer->fY);

		for (auto& b : m_pBoss->GetNewBullets())
			m_BulletList.push_back(b);
		m_pBoss->ClearNewBullets();
	}

	UpdateBullets();
	CheckBulletHitPlayer();

	for (auto& pReward : m_vecReward) {
		if (pReward->IsAlive())
			pReward->Update();
	}

	RemoveDeadEnemies();
	RemoveDeadRewards();
}

void CEnemyMgr::SpawnEnemy()
{
	int iRand = rand() % 4;
	if (iRand == 2 && m_iWave < 2) iRand = 0;

	ENEMY_TYPE eType = (ENEMY_TYPE)iRand;

	float fSpawnX = (float)(50 + rand() % (WINCX - 100));

	CEnemy* pEnemy = new CEnemy;
	pEnemy->Initialize(eType, fSpawnX, -30.f);
	m_EnemyList.push_back(pEnemy);
}

void CEnemyMgr::SpawnBoss()
{
	m_pBoss = new CBoss;
	m_pBoss->Initialize((float)WINCX * 0.5f, 100.f);
	m_iWave = 3;
}

void CEnemyMgr::SpawnReward(float fX, float fY, int iHpMax, bool bBoss)
{
	CReward* pGold = new CReward;
	int iGoldVal = bBoss ? 300 + rand() % 200 : 20 + rand() % 40;
	pGold->Initialize(RT_GOLD, fX, fY, iGoldVal);
	m_vecReward.push_back(pGold);
	m_iGold += iGoldVal;

	int iItemChance = bBoss ? 0 : (rand() % 10);
	if (iItemChance < 3 || bBoss) {
		CReward* pItem = new CReward;
		REWARD_TYPE eItemType = bBoss ?
			(rand() % 3 == 0 ? RT_ITEM_RARE : RT_ITEM_NORM) :
			RT_ITEM_NORM;
		pItem->Initialize(eItemType, fX + 24.f, fY, 1);
		m_vecReward.push_back(pItem);
	}
}

void CEnemyMgr::UpdateBullets()
{
	for (auto& b : m_BulletList) {
		if (!b.bAlive) continue;
		b.fX += b.fVX;
		b.fY += b.fVY;

		if (b.fX < -20.f || b.fX > WINCX + 20.f ||
			b.fY < -20.f || b.fY > WINCY + 20.f)
			b.bAlive = false;
	}
}

void CEnemyMgr::CheckBulletHitPlayer()
{
	float fPR = m_pPlayer->fCX * 0.4f;
	for (auto& b : m_BulletList) {
		if (!b.bAlive || b.bFromPlayer) continue;
		if (IsCircleOverlap(b.fX, b.fY, 5.f,
			m_pPlayer->fX, m_pPlayer->fY, fPR)) {
			b.bAlive = false;
			m_bPlayerHit = true;
			m_dwHitMsgTick = GetTickCount();
			wsprintf(m_szHitMsg, TEXT("HIT!"));
		}
	}
}

void CEnemyMgr::NotifyPlayerBullet(const BULLET& tBlt)
{

	for (auto& pEnemy : m_EnemyList) {
		if (!pEnemy->IsAlive()) continue;
		INFO ti = pEnemy->GetInfo();
		if (IsCircleOverlap(tBlt.fX, tBlt.fY, 5.f,
			ti.fX, ti.fY, ti.fCX * 0.5f)) {
			pEnemy->TakeDamage(20);
			if (!pEnemy->IsAlive()) {
				++m_iKillCount;
				SpawnReward(ti.fX, ti.fY, pEnemy->GetMaxHP(), false);
			}
			return;
		}
	}

	if (m_pBoss && m_pBoss->IsAlive()) {
		INFO bi = m_pBoss->GetInfo();
		if (IsCircleOverlap(tBlt.fX, tBlt.fY, 5.f,
			bi.fX, bi.fY, bi.fCX * 0.5f)) {
			m_pBoss->TakeDamage(20);
			if (!m_pBoss->IsAlive()) {
				SpawnReward(bi.fX, bi.fY, m_pBoss->GetMaxHP(), true);
			}
		}
	}
}

bool CEnemyMgr::IsCircleOverlap(
	float fAX, float fAY, float fAR,
	float fBX, float fBY, float fBR)
{
	float fDX = fBX - fAX;
	float fDY = fBY - fAY;
	float fDist = sqrtf(fDX * fDX + fDY * fDY);
	return fDist < (fAR + fBR);
}

void CEnemyMgr::RemoveDeadEnemies()
{
	m_EnemyList.remove_if([](CEnemy* p) {
		if (!p->IsAlive()) {
			p->Release();
			delete p;
			return true;
		}
		return false;
		});

	m_BulletList.remove_if([](const BULLET& b) {
		return !b.bAlive;
		});
}

void CEnemyMgr::RemoveDeadRewards()
{
	for (int i = (int)m_vecReward.size() - 1; i >= 0; --i) {
		if (!m_vecReward[i]->IsAlive()) {
			m_vecReward[i]->Release();
			Safe_Delete(m_vecReward[i]);
			m_vecReward.erase(m_vecReward.begin() + i);
		}
	}
}

void CEnemyMgr::LateUpdate() {}

void CEnemyMgr::Render(HDC hDC)
{

	for (auto& pEnemy : m_EnemyList)
		pEnemy->Render(hDC);

	for (auto& b : m_BulletList)
	{
		if (!b.bAlive) continue;
		int iX = (int)b.fX, iY = (int)b.fY;
		Ellipse(hDC, iX - 4, iY - 4, iX + 4, iY + 4);
	}

	if (m_pBoss && m_pBoss->IsAlive())
		m_pBoss->Render(hDC);

	for (auto& pReward : m_vecReward)
		pReward->Render(hDC);

	TCHAR szInfo[64];
	wsprintf(szInfo, TEXT("WAVE:%d KILL:%d GOLD:%d"), m_iWave, m_iKillCount, m_iGold);
	TextOut(hDC, 10, 10, szInfo, lstrlen(szInfo));

	if (m_bPlayerHit)
	{
		TextOut(hDC, (int)m_pPlayer->fX - 16, (int)m_pPlayer->fY - 30, m_szHitMsg, lstrlen(m_szHitMsg));
		if (GetTickCount() - m_dwHitMsgTick > 600)
			m_bPlayerHit = false;
	}
}

void CEnemyMgr::Release()
{
	for (auto& pEnemy : m_EnemyList) {
		pEnemy->Release();
		delete pEnemy;
	}
	m_EnemyList.clear();
	m_BulletList.clear();

	Safe_Delete(m_pBoss);

	for (auto& pReward : m_vecReward) {
		pReward->Release();
		delete pReward;
	}
	m_vecReward.clear();
}
