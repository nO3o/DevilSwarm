#include "pch.h"
#include "CReward.h"

CReward::CReward()
    : m_eType(RT_SOUL), m_fValue(0.f), m_dwExpireTick(0)
    , m_fDirX(0.f), m_fDirY(0.f)
{
    m_tInfo = { 0.f, 0.f, 24.f, 24.f };
}

CReward::~CReward() {}

void CReward::Initialize()
{
    m_bDead = false;
    m_dwExpireTick = GetTickCount();
    m_fSpeed = 1.5f;

    float fAngle = (float)(rand() % 360) * 3.141592f / 180.f;
    m_fDirX = cosf(fAngle);
    m_fDirY = sinf(fAngle);
}

void CReward::SetRewardInfo(REWARD_TYPE eType, float fVal)
{
    m_eType = eType;

    switch (eType) {
    case RT_SOUL:   m_fValue = fVal;        break;
    case RT_SOUL02: m_fValue = fVal * 1.5f; break;
    case RT_SOUL03: m_fValue = fVal * 3.f;  break;
    default:        m_fValue = fVal;        break;
    }
}

int CReward::Update()
{
    if (m_bDead) return 1;

    if (GetTickCount() - m_dwExpireTick > 15000)
        return 1;

    m_tInfo.fX += m_fDirX * m_fSpeed;
    m_tInfo.fY += m_fDirY * m_fSpeed;

    float fRadiusX = m_tInfo.fCX * 0.5f;
    float fRadiusY = m_tInfo.fCY * 0.5f;

    if (m_tInfo.fX - fRadiusX < 0.f) {
        m_tInfo.fX = fRadiusX;
        m_fDirX = -m_fDirX;
    }
    else if (m_tInfo.fX + fRadiusX > WINCX) {
        m_tInfo.fX = WINCX - fRadiusX;
        m_fDirX = -m_fDirX;
    }

    if (m_tInfo.fY - fRadiusY < 0.f) {
        m_tInfo.fY = fRadiusY;
        m_fDirY = -m_fDirY;
    }
    else if (m_tInfo.fY + fRadiusY > WINCY) {
        m_tInfo.fY = WINCY - fRadiusY;
        m_fDirY = -m_fDirY;
    }

    return 0;
}

void CReward::LateUpdate()
{
    UpdateRect();
}

void CReward::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    const TCHAR* pLabel = TEXT("S");
    switch (m_eType) {
    case RT_SOUL:   pLabel = TEXT("S"); break;
    case RT_SOUL02: pLabel = TEXT("N"); break;
    case RT_SOUL03: pLabel = TEXT("B"); break;
    }
    TextOut(hDC, m_tRect.left + 5, m_tRect.top + 3, pLabel, lstrlen(pLabel));

    TCHAR szVal[32];
    swprintf_s(szVal, L"+%.0f EXP", m_fValue);
    TextOut(hDC, m_tRect.left - 15, m_tRect.bottom + 2, szVal, lstrlen(szVal));
}

void CReward::Release() {}