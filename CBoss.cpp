#include "pch.h"
#include "CBoss.h"
#include "CBullet.h"
#include "CObjMgr.h"

CBoss::CBoss()
    : m_ePhase(BP_ONE), m_fSpiralAngle(0.f), m_fMoveDirX(1.f)
    , m_dwFireTick(0)
{
    m_tInfo = { 0.f, 0.f, 120.f, 80.f };
}

CBoss::~CBoss() { Release(); }

void CBoss::Initialize()
{
    m_iMaxHP = 3000;
    m_iHP = m_iMaxHP;
    m_ePhase = BP_ONE;
    m_bDead = false;
    m_dwFireTick = GetTickCount();
}

void CBoss::CheckPhase()
{
    float fRatio = (float)m_iHP / (float)m_iMaxHP;
    if (fRatio > 0.6f)       m_ePhase = BP_ONE;
    else if (fRatio > 0.3f)  m_ePhase = BP_TWO;
    else                     m_ePhase = BP_THREE;
}

int CBoss::Update()
{
    if (m_bDead) return 1;
    CheckPhase();

    DWORD dwNow = GetTickCount();
    DWORD dwInterval = 2000;
    if (m_ePhase == BP_TWO)   dwInterval = 1500;
    if (m_ePhase == BP_THREE) dwInterval = 950;

    if (dwNow - m_dwFireTick > dwInterval) {
        m_dwFireTick = dwNow;
        switch (m_ePhase) {
        case BP_ONE:   FirePhase1();        break;
        case BP_TWO:   FirePhase2();        break;
        case BP_THREE: FirePhase3Spiral();  break;
        }
    }

    m_tInfo.fX += m_fMoveDirX * 1.0f;
    if (m_tInfo.fX > WINCX - m_tInfo.fCX * 0.5f || m_tInfo.fX < m_tInfo.fCX * 0.5f)
        m_fMoveDirX = -m_fMoveDirX;

    return 0;
}

void CBoss::FirePhase1()
{
    float aOffX[3] = { -30.f, 0.f, 30.f };
    for (int i = 0; i < 3; ++i) {
        CBullet* pB = new CBullet;
        pB->Initialize();
        pB->SetPos(m_tInfo.fX + aOffX[i], m_tInfo.fY + m_tInfo.fCY * 0.5f);
        pB->SetVelocity(0.f, 2.2f);
        CObjMgr::GetInstance()->AddObject(OBJ_ENEMY_BULLET, pB);
    }
}

void CBoss::FirePhase2()
{
    for (int i = 0; i < 8; ++i) {
        float fAng = (3.141592f * 2.f / 8.f) * i;
        CBullet* pB = new CBullet;
        pB->Initialize();
        pB->SetPos(m_tInfo.fX, m_tInfo.fY);
        pB->SetVelocity(cosf(fAng) * 2.0f, sinf(fAng) * 2.0f);
        CObjMgr::GetInstance()->AddObject(OBJ_ENEMY_BULLET, pB);
    }
}

void CBoss::FirePhase3Spiral()
{
    for (int i = 0; i < 3; ++i) {
        float fAng = m_fSpiralAngle + (3.141592f * 2.f / 3.f) * i;
        CBullet* pB = new CBullet;
        pB->Initialize();
        pB->SetPos(m_tInfo.fX, m_tInfo.fY);
        pB->SetVelocity(cosf(fAng) * 2.5f, sinf(fAng) * 2.5f);
        CObjMgr::GetInstance()->AddObject(OBJ_ENEMY_BULLET, pB);
    }
    m_fSpiralAngle += 0.15f;
}

void CBoss::LateUpdate() { UpdateRect(); }

void CBoss::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
    if (m_ePhase == BP_ONE) {
        Rectangle(hDC, m_tRect.left - 20, m_tRect.top + 10, m_tRect.left, m_tRect.top + 40);
        Rectangle(hDC, m_tRect.right, m_tRect.top + 10, m_tRect.right + 20, m_tRect.top + 40);
    }

    TCHAR szHP[32];
    wsprintf(szHP, TEXT("체력: %d / %d"), m_iHP, m_iMaxHP);
    TextOut(hDC, m_tRect.left, m_tRect.top - 18, szHP, lstrlen(szHP));

    TCHAR szPhase[16];
    wsprintf(szPhase, TEXT("페이즈 %d"), (int)m_ePhase + 1);
    TextOut(hDC, m_tRect.left, m_tRect.top - 32, szPhase, lstrlen(szPhase));
}

void CBoss::Release() {}