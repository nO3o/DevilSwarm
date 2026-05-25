#pragma once
#include "CObj.h"

class CEnemy {
public:
	CEnemy();
	~CEnemy();

public:
	void Initialize(ENEMY_TYPE eType, float fX, float fY);
	void Update(float fPlayerX, float fPlayerY);
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	bool       IsAlive()    const { return m_bAlive; }
	bool       IsDeadFlag() const { return !m_bAlive; }
	ENEMY_TYPE GetType()    const { return m_eType; }
	int        GetHP()      const { return m_iHP; }
	int        GetMaxHP()   const { return m_iMaxHP; }
	INFO       GetInfo()    const { return m_tInfo; }

	void TakeDamage(int iDmg);

	// 발사 요청 -> CEnemyMgr 가 회수
	bool  HasPendingBullet() const { return m_bFireReq; }
	BULLET GetPendingBullet();

private:
	void FireStraight(float fPlayerX, float fPlayerY);
	void FireSpread8();

private:
	INFO       m_tInfo;
	ENEMY_TYPE m_eType;
	int        m_iHP;
	int        m_iMaxHP;
	float      m_fSpeed;
	float      m_fAngle;       // 지그재그 각도 (누적)
	bool       m_bAlive;

	DWORD      m_dwFireTick;   // 다음 발사 시각
	bool       m_bFireReq;     // 탄환 발사 요청 플래그
	BULLET     m_tPendingBlt;  // 요청 탄환 1발

	int        m_iSpreadIdx;   // 8방향 발사 인덱스 (ET_ELITE)
};

