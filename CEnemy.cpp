#include "pch.h"
#include "CEnemy.h"

CEnemy::CEnemy()
	: m_eType(ET_STRAIGHT)
	, m_iHP(40), m_iMaxHP(40)
	, m_fSpeed(2.f), m_fAngle(0.f)
	, m_bAlive(true)
	, m_dwFireTick(0), m_bFireReq(false)
	, m_iSpreadIdx(0)
{
	m_tInfo = { 0.f, 0.f, 36.f, 36.f };
	m_tPendingBlt = { 0.f, 0.f, 0.f, 0.f, false, false };
}

CEnemy::~CEnemy() {}

void CEnemy::Initialize(ENEMY_TYPE eType, float fX, float fY)
{
	m_eType = eType;
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;

	switch (eType) {
	case ET_STRAIGHT: m_iMaxHP = 40;  m_fSpeed = 2.f;  break;
	case ET_ZIGZAG:   m_iMaxHP = 60;  m_fSpeed = 2.5f; break;
	case ET_DRONE:    m_iMaxHP = 30;  m_fSpeed = 3.5f; break;
	case ET_ELITE:    m_iMaxHP = 200; m_fSpeed = 1.5f; break;
	default: break;
	}
	m_iHP = m_iMaxHP;
}

void CEnemy::Update(float fPlayerX, float fPlayerY)
{
	if (!m_bAlive) return;

	switch (m_eType) {
	case ET_STRAIGHT:
		m_tInfo.fY += m_fSpeed;
		break;
	case ET_ZIGZAG:
		m_fAngle += 0.08f;
		m_tInfo.fY += m_fSpeed;
		m_tInfo.fX += sinf(m_fAngle) * 3.f;
		break;
	case ET_DRONE: {
		float fDX = fPlayerX - m_tInfo.fX;
		float fDY = fPlayerY - m_tInfo.fY;
		float fDist = sqrtf(fDX * fDX + fDY * fDY);
		if (fDist > 1.f) {
			m_tInfo.fX += (fDX / fDist) * m_fSpeed;
			m_tInfo.fY += (fDY / fDist) * m_fSpeed;
		}
		break;
	}
	case ET_ELITE:
		m_tInfo.fY += m_fSpeed;
		break;
	default: break;
	}

	if (m_tInfo.fY > WINCY + 60.f ||
		m_tInfo.fX < -60.f || m_tInfo.fX > WINCX + 60.f)
		m_bAlive = false;

	m_bFireReq = false;
	DWORD dwNow = GetTickCount();
	if (dwNow - m_dwFireTick > 2000) {
		m_dwFireTick = dwNow;
		switch (m_eType) {
		case ET_STRAIGHT:
		case ET_ZIGZAG:
			FireStraight(fPlayerX, fPlayerY);
			break;
		case ET_ELITE:
			FireSpread8();
			break;
		default: break;
		}
	}
}

void CEnemy::FireStraight(float fPlayerX, float fPlayerY)
{
	float fDX = fPlayerX - m_tInfo.fX;
	float fDY = fPlayerY - m_tInfo.fY;
	float fDst = sqrtf(fDX * fDX + fDY * fDY);
	if (fDst < 1.f) return;

	float fSpd = 4.f;
	m_tPendingBlt.fX = m_tInfo.fX;
	m_tPendingBlt.fY = m_tInfo.fY;
	m_tPendingBlt.fVX = (fDX / fDst) * fSpd;
	m_tPendingBlt.fVY = (fDY / fDst) * fSpd;
	m_tPendingBlt.bAlive = true;
	m_tPendingBlt.bFromPlayer = false;
	m_bFireReq = true;
}

void CEnemy::FireSpread8()
{
	float fAng = (PI * 2.f / 8.f) * m_iSpreadIdx;
	m_iSpreadIdx = (m_iSpreadIdx + 1) % 8;

	m_tPendingBlt.fX = m_tInfo.fX;
	m_tPendingBlt.fY = m_tInfo.fY;
	m_tPendingBlt.fVX = cosf(fAng) * 3.5f;
	m_tPendingBlt.fVY = sinf(fAng) * 3.5f;
	m_tPendingBlt.bAlive = true;
	m_tPendingBlt.bFromPlayer = false;
	m_bFireReq = true;
}

BULLET CEnemy::GetPendingBullet()
{
	m_bFireReq = false;
	return m_tPendingBlt;
}

void CEnemy::TakeDamage(int iDmg)
{
	m_iHP -= iDmg;
	if (m_iHP <= 0) {
		m_iHP = 0;
		m_bAlive = false;
	}
}

void CEnemy::LateUpdate() {}

void CEnemy::Render(HDC hDC)
{
	if (!m_bAlive) return;

	int iL = (int)(m_tInfo.fX - m_tInfo.fCX * 0.5f);
	int iT = (int)(m_tInfo.fY - m_tInfo.fCY * 0.5f);
	int iR = (int)(m_tInfo.fX + m_tInfo.fCX * 0.5f);
	int iB = (int)(m_tInfo.fY + m_tInfo.fCY * 0.5f);

	SelectObject(hDC, GetStockObject(NULL_BRUSH));
	Ellipse(hDC, iL, iT, iR, iB);

	int iBarL = iL;
	int iBarT = iT - 10;
	int iBarR = iR;
	int iBarB = iT - 3;
	SelectObject(hDC, GetStockObject(NULL_BRUSH));
	Rectangle(hDC, iBarL, iBarT, iBarR, iBarB);

	int iFilledR = iBarL + (int)((float)(iBarR - iBarL) * (float)m_iHP / (float)m_iMaxHP);
	SelectObject(hDC, GetStockObject(BLACK_BRUSH));
	Rectangle(hDC, iBarL, iBarT, iFilledR, iBarB);

	const TCHAR* pLabel = TEXT("N");
	switch (m_eType) {
	case ET_STRAIGHT: pLabel = TEXT("S"); break;
	case ET_ZIGZAG:   pLabel = TEXT("Z"); break;
	case ET_DRONE:    pLabel = TEXT("D"); break;
	case ET_ELITE:    pLabel = TEXT("E"); break;
	default: break;
	}
	TextOut(hDC, (int)m_tInfo.fX - 4, (int)m_tInfo.fY - 6, pLabel, lstrlen(pLabel));
}

void CEnemy::Release() {}