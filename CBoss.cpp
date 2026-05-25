#include "pch.h"
#include "CBoss.h"

CBoss::CBoss()
	: m_iHP(0), m_iMaxHP(3000)
	, m_ePhase(BP_ONE), m_bAlive(false)
	, m_fSpiralAngle(0.f), m_fRamDirX(1.f)
	, m_bRamming(false), m_fOrigX(0.f)
	, m_dwFireTick(0), m_dwRamTick(0)
	, m_iLaserX(0), m_bShowLaser(false), m_dwLaserTick(0)
{
	m_tInfo = { 0.f, 0.f, 120.f, 80.f };
}
CBoss::~CBoss() {}

void CBoss::Initialize(float fX, float fY)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_iMaxHP = 3000;
	m_iHP = m_iMaxHP;
	m_ePhase = BP_ONE;
	m_bAlive = true;
	m_fOrigX = fX;
	m_dwFireTick = GetTickCount();
}

void CBoss::TakeDamage(int iDmg)
{
	m_iHP -= iDmg;
	if (m_iHP <= 0) {
		m_iHP = 0;
		m_bAlive = false;
	}
	CheckPhase();
}

void CBoss::CheckPhase()
{
	float fRatio = (float)m_iHP / (float)m_iMaxHP;
	if (fRatio > 0.6f) m_ePhase = BP_ONE;
	else if (fRatio > 0.3f) m_ePhase = BP_TWO;
	else                    m_ePhase = BP_THREE;
}

void CBoss::Update(float fPlayerX, float fPlayerY)
{
	if (!m_bAlive) return;

	DWORD dwNow = GetTickCount();
	DWORD dwInterval = 1800;
	if (m_ePhase == BP_TWO)   dwInterval = 1400;
	if (m_ePhase == BP_THREE) dwInterval = 900;

	if (dwNow - m_dwFireTick > dwInterval) {
		m_dwFireTick = dwNow;
		switch (m_ePhase) {
		case BP_ONE:   FirePhase1();        break;
		case BP_TWO:   FirePhase2();        break;
		case BP_THREE: FirePhase3Spiral();  break;
		default: break;
		}
	}

	if (m_ePhase == BP_THREE) {
		if (!m_bShowLaser && dwNow - m_dwLaserTick > 2500) {
			m_bShowLaser = true;
			m_iLaserX = (int)m_tInfo.fX;
			m_dwLaserTick = dwNow;
		}
		if (m_bShowLaser && dwNow - m_dwLaserTick > 800) {
			m_bShowLaser = false;
			m_bRamming = true;
			m_dwRamTick = dwNow;
		}
	}

	if (m_bRamming) {
		UpdateRam(fPlayerX);
		if (dwNow - m_dwRamTick > 1200) {
			m_bRamming = false;
			m_dwLaserTick = dwNow;
		}
	}
	else if (m_ePhase != BP_THREE) {
		// Phase 1~2: 좌우 왕복
		m_tInfo.fX += m_fRamDirX * 1.5f;
		if (m_tInfo.fX > WINCX - m_tInfo.fCX * 0.5f ||
			m_tInfo.fX < m_tInfo.fCX * 0.5f)
			m_fRamDirX = -m_fRamDirX;
	}
}

void CBoss::UpdateRam(float fPlayerX)
{
	// 플레이어 X 방향으로 빠르게 돌진
	float fDX = fPlayerX - m_tInfo.fX;
	if (fDX > 0.f)       m_tInfo.fX += 6.f;
	else if (fDX < 0.f)  m_tInfo.fX -= 6.f;
}

void CBoss::FirePhase1()
{
	float aOffX[3] = { -30.f, 0.f, 30.f };
	for (int i = 0; i < 3; ++i) {
		BULLET b;
		b.fX = m_tInfo.fX + aOffX[i];
		b.fY = m_tInfo.fY + m_tInfo.fCY * 0.5f;
		b.fVX = 0.f;
		b.fVY = 4.5f;
		b.bAlive = true;
		b.bFromPlayer = false;
		m_vecNewBullets.push_back(b);
	}
}

void CBoss::FirePhase2()
{
	for (int i = 0; i < 8; ++i) {
		float fAng = (PI * 2.f / 8.f) * i;
		BULLET b;
		b.fX = m_tInfo.fX;
		b.fY = m_tInfo.fY;
		b.fVX = cosf(fAng) * 4.f;
		b.fVY = sinf(fAng) * 4.f;
		b.bAlive = true;
		b.bFromPlayer = false;
		m_vecNewBullets.push_back(b);
	}
}

void CBoss::FirePhase3Spiral()
{
	for (int i = 0; i < 3; ++i) {
		float fAng = m_fSpiralAngle + (PI * 2.f / 3.f) * i;
		BULLET b;
		b.fX = m_tInfo.fX;
		b.fY = m_tInfo.fY;
		b.fVX = cosf(fAng) * 5.f;
		b.fVY = sinf(fAng) * 5.f;
		b.bAlive = true;
		b.bFromPlayer = false;
		m_vecNewBullets.push_back(b);
	}
	m_fSpiralAngle += 0.35f; 
	if (m_fSpiralAngle > PI * 2.f)
		m_fSpiralAngle -= PI * 2.f;
}

void CBoss::LateUpdate() {}

void CBoss::Render(HDC hDC)
{
	if (!m_bAlive) return;

	int iL = (int)(m_tInfo.fX - m_tInfo.fCX * 0.5f);
	int iT = (int)(m_tInfo.fY - m_tInfo.fCY * 0.5f);
	int iR = (int)(m_tInfo.fX + m_tInfo.fCX * 0.5f);
	int iB = (int)(m_tInfo.fY + m_tInfo.fCY * 0.5f);


	SelectObject(hDC, GetStockObject(NULL_BRUSH));
	Rectangle(hDC, iL, iT, iR, iB);

	if (m_ePhase == BP_ONE) {
		Rectangle(hDC, iL - 20, iT + 10, iL, iT + 40);
		Rectangle(hDC, iR, iT + 10, iR + 20, iT + 40); 
	}


	int iBarL = iL;
	int iBarT = iT - 14;
	int iBarR = iR;
	int iBarB = iT - 4;
	SelectObject(hDC, GetStockObject(NULL_BRUSH));
	Rectangle(hDC, iBarL, iBarT, iBarR, iBarB);
	int iFilledR = iBarL + (int)((float)(iBarR - iBarL) * (float)m_iHP / (float)m_iMaxHP);
	SelectObject(hDC, GetStockObject(BLACK_BRUSH));
	Rectangle(hDC, iBarL, iBarT, iFilledR, iBarB);


	TCHAR szHP[32];
	wsprintf(szHP, TEXT("HP:%d"), m_iHP);
	TextOut(hDC, iL, iT - 28, szHP, lstrlen(szHP));


	TCHAR szPhase[16];
	wsprintf(szPhase, TEXT("PHASE %d"), (int)m_ePhase);
	TextOut(hDC, iL, iT - 42, szPhase, lstrlen(szPhase));


	if (m_ePhase == BP_THREE && m_bShowLaser) {
		HPEN hDashPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hDashPen);
		MoveToEx(hDC, m_iLaserX, iB, NULL);
		LineTo(hDC, m_iLaserX, WINCY);
		SelectObject(hDC, hOldPen);
		DeleteObject(hDashPen);

		TextOut(hDC, m_iLaserX - 20, iB + 4, TEXT("!LASER!"), lstrlen(TEXT("!LASER!")));
	}


	if (m_bRamming) {
		TextOut(hDC, iL, iB + 4, TEXT(">>RAM<<"), lstrlen(TEXT(">>RAM<<")));
	}
}

void CBoss::Release() {}