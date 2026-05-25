#pragma once

class CBoss
{
public:
	CBoss();
	~CBoss();

public:
	void Initialize(float fX, float fY);
	void Update(float fPlayerX, float fPlayerY);
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	bool       IsAlive()    const { return m_bAlive; }
	int        GetHP()      const { return m_iHP; }
	int        GetMaxHP()   const { return m_iMaxHP; }
	BOSS_PHASE GetPhase()   const { return m_ePhase; }
	INFO       GetInfo()    const { return m_tInfo; }

	void TakeDamage(int iDmg);

	std::vector<BULLET>& GetNewBullets() { return m_vecNewBullets; }
	void            ClearNewBullets() { m_vecNewBullets.clear(); }

private:
	void CheckPhase();
	void FirePhase1();
	void FirePhase2();
	void FirePhase3Spiral();
	void UpdateRam(float fPlayerX);

private:
	INFO       m_tInfo;
	int        m_iHP;
	int        m_iMaxHP;
	BOSS_PHASE m_ePhase;
	bool       m_bAlive;

	float      m_fSpiralAngle;  // 나선 탄막 누적 각도
	float      m_fRamDirX;      // 돌진 방향
	bool       m_bRamming;      // 돌진 중 여부
	float      m_fOrigX;        // 돌진 전 원위치 X

	DWORD      m_dwFireTick;
	DWORD      m_dwRamTick;

	// 레이저 예고선 Y 목록 (Phase 3 렌더용)
	int        m_iLaserX;
	bool       m_bShowLaser;
	DWORD      m_dwLaserTick;

	std::vector<BULLET> m_vecNewBullets;
};
