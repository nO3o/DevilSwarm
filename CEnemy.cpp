#include "pch.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "CObjMgr.h"

CEnemy::CEnemy()
    : m_eType(ET_STRAIGHT), m_dwFireTick(0), m_iSpreadIdx(0)
{
    m_tInfo = { 0.f, 0.f, 36.f, 36.f };
}

CEnemy::~CEnemy() { Release(); }

void CEnemy::Initialize()
{
    m_bDead = false;
    m_dwFireTick = GetTickCount();
}

void CEnemy::Initialize(ENEMY_TYPE eType)
{
    m_bDead = false;
    m_dwFireTick = GetTickCount();
    SetEnemyType(eType);
}

void CEnemy::SetEnemyType(ENEMY_TYPE eType)
{
    m_eType = eType;
    switch (eType) {
    case ET_STRAIGHT: m_iMaxHP = 40;  m_fSpeed = 0.8f;  break;
    case ET_ZIGZAG:   m_iMaxHP = 60;  m_fSpeed = 1.0f;  break;
    case ET_DRONE:    m_iMaxHP = 30;  m_fSpeed = 1.2f;  break;
    case ET_ELITE:    m_iMaxHP = 200; m_fSpeed = 0.5f;  break;
    default: break;
    }
    m_iHP = m_iMaxHP;
}

int CEnemy::Update()
{
    if (m_bDead) return 1;

    CObj* pPlayer = CObjMgr::GetInstance()->GetPlayer();
    float fPlX = 400.f, fPlY = 500.f;
    if (pPlayer) {
        fPlX = pPlayer->GetInfo()->fX;
        fPlY = pPlayer->GetInfo()->fY;
    }

    switch (m_eType) {
    case ET_STRAIGHT:
        m_tInfo.fY += m_fSpeed;
        break;
    case ET_ZIGZAG:
        m_fAngle += 0.04f;
        m_tInfo.fY += m_fSpeed;
        m_tInfo.fX += sinf(m_fAngle) * 2.0f;
        break;
    case ET_DRONE: {
        float fDX = fPlX - m_tInfo.fX;
        float fDY = fPlY - m_tInfo.fY;
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
    }

    if (m_tInfo.fY > 600.f + 60.f || m_tInfo.fX < -60.f || m_tInfo.fX > 800.f + 60.f)
        return 1;

    DWORD dwNow = GetTickCount();
    if (dwNow - m_dwFireTick > 2500) {
        m_dwFireTick = dwNow;
        switch (m_eType) {
        case ET_STRAIGHT:
        case ET_ZIGZAG:
            FireStraight(fPlX, fPlY);
            break;
        case ET_ELITE:
            FireSpread8();
            break;
        default: break;
        }
    }

    return 0;
}

void CEnemy::FireStraight(float fPlayerX, float fPlayerY)
{
    float fDX = fPlayerX - m_tInfo.fX;
    float fDY = fPlayerY - m_tInfo.fY;
    float fDst = sqrtf(fDX * fDX + fDY * fDY);
    if (fDst < 1.f) return;

    CBullet* pBullet = new CBullet;
    static_cast<CBullet*>(pBullet)->SetType(OBJ_ENEMY_BULLET);
    pBullet->Initialize();
    pBullet->SetPos(m_tInfo.fX, m_tInfo.fY);
    pBullet->SetVelocity((fDX / fDst) * 2.2f, (fDY / fDst) * 2.2f);

    CObjMgr::GetInstance()->AddObject(OBJ_ENEMY_BULLET, pBullet);
}

void CEnemy::FireSpread8()
{
    float fAng = (3.141592f * 2.f / 8.f) * m_iSpreadIdx;
    m_iSpreadIdx = (m_iSpreadIdx + 1) % 8;

    CBullet* pBullet = new CBullet;
    static_cast<CBullet*>(pBullet)->SetType(OBJ_ENEMY_BULLET);
    pBullet->Initialize();
    pBullet->SetPos(m_tInfo.fX, m_tInfo.fY);
    pBullet->SetVelocity(cosf(fAng) * 1.8f, sinf(fAng) * 1.8f);

    CObjMgr::GetInstance()->AddObject(OBJ_ENEMY_BULLET, pBullet);
}

void CEnemy::LateUpdate()
{
    UpdateRect();
}

void CEnemy::Render(HDC hDC)
{
    Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    TCHAR szHp[32];
    wsprintf(szHp, TEXT("%d/%d"), m_iHP, m_iMaxHP);
    TextOut(hDC, (int)m_tInfo.fX - 16, m_tRect.top - 15, szHp, lstrlen(szHp));

    const TCHAR* pLabel = TEXT("N");
    switch (m_eType) {
    case ET_STRAIGHT: pLabel = TEXT("A형"); break;
    case ET_ZIGZAG:   pLabel = TEXT("B형"); break;
    case ET_DRONE:    pLabel = TEXT("자폭"); break;
    case ET_ELITE:    pLabel = TEXT("정예"); break;
    }
    TextOut(hDC, (int)m_tInfo.fX - 14, (int)m_tInfo.fY - 6, pLabel, lstrlen(pLabel));
}

void CEnemy::Release() {}