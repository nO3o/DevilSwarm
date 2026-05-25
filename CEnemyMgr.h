#pragma once
#include "Singleton.h"
#include "CEnemy.h"
#include "CBoss.h"
#include "CReward.h"

class CEnemyMgr {
	DECLARE_SINGLETON(CEnemyMgr)

private:
	CEnemyMgr();
	~CEnemyMgr();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
public:
	void SetPlayerInfo(INFO* pInfo) { m_pPlayer = pInfo; }

	int  GetKillCount() const { return m_iKillCount; }
	int  GetGold()      const { return m_iGold; }
	bool IsBossAlive()  const { return m_pBoss && m_pBoss->IsAlive(); }
	int  GetWave()      const { return m_iWave; }

	void NotifyPlayerBullet(const BULLET& tBlt);

private:
	void SpawnEnemy();
	void SpawnBoss();
	void SpawnReward(float fX, float fY, int iHpMax, bool bBoss);

	void UpdateBullets();
	void CheckBulletHitPlayer(); 

	void RemoveDeadEnemies();
	void RemoveDeadRewards();

	bool IsCircleOverlap(float fAX, float fAY, float fAR,
		float fBX, float fBY, float fBR);

private:
	std::list<CEnemy*>    m_EnemyList;
	std::list<BULLET>     m_BulletList;
	CBoss* m_pBoss;
	std::vector<CReward*> m_vecReward;

	INFO*   m_pPlayer;

	int    m_iWave;         // 현재 웨이브 번호
	int    m_iKillCount;    // 격추 수
	int    m_iGold;         // 누적 골드
	DWORD  m_dwSpawnTick;   // 마지막 스폰 시각
	DWORD  m_dwWaveTick;    // 웨이브 시작 시각
	bool   m_bBossSpawned;  // 보스 스폰 완료 여부

	// 플레이어 피격 알림용
	bool   m_bPlayerHit;
	TCHAR  m_szHitMsg[32];
	DWORD  m_dwHitMsgTick;
};

