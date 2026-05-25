#include "pch.h"
#include "CReward.h"

CReward::CReward()
	: m_eType(RT_GOLD), m_iValue(0)
	, m_bAlive(false), m_dwExpire(0), m_fBob(0.f)
{
	m_tInfo = { 0.f, 0.f, 20.f, 20.f };
}
CReward::~CReward() {}

void CReward::Initialize(REWARD_TYPE eType, float fX, float fY, int iValue)
{
	m_eType = eType;
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_iValue = iValue;
	m_bAlive = true;
	m_dwExpire = GetTickCount();
	m_fBob = 0.f;
}

void CReward::Update()
{
	if (!m_bAlive) return;

	if (GetTickCount() - m_dwExpire > 30000)
		m_bAlive = false;

	m_fBob += 0.08f;
	if (m_fBob > PI * 2.f) m_fBob -= PI * 2.f;
}
void CReward::LateUpdate() {}

void CReward::Render(HDC hDC)
{
	if (!m_bAlive) return;

	float fRenderY = m_tInfo.fY + sinf(m_fBob) * 4.f;  

	int iL = (int)(m_tInfo.fX - m_tInfo.fCX * 0.5f);
	int iT = (int)(fRenderY - m_tInfo.fCY * 0.5f);
	int iR = (int)(m_tInfo.fX + m_tInfo.fCX * 0.5f);
	int iB = (int)(fRenderY + m_tInfo.fCY * 0.5f);

	SelectObject(hDC, GetStockObject(NULL_BRUSH));
	Rectangle(hDC, iL, iT, iR, iB);

	const TCHAR* pLabel = TEXT("G");
	switch (m_eType) {
	case RT_GOLD:      pLabel = TEXT("G");  break;
	case RT_ITEM_NORM: pLabel = TEXT("I");  break;
	case RT_ITEM_RARE: pLabel = TEXT("R!"); break;
	default: break;
	}
	TextOut(hDC, iL + 4, iT + 3, pLabel, lstrlen(pLabel));

	if (m_eType == RT_GOLD) {
		TCHAR szVal[16];
		wsprintf(szVal, TEXT("+%d"), m_iValue);
		TextOut(hDC, iL, iB + 2, szVal, lstrlen(szVal));
	}
}

void CReward::Release() {}
