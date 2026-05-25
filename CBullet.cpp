#include "pch.h"
#include "CBullet.h"

CBullet::CBullet() : m_fVX(0.f), m_fVY(0.f)
{
}

CBullet::~CBullet() { Release(); }

void CBullet::Initialize()
{
    if (m_eType != OBJ_ENEMY_BULLET) {
        m_tInfo.fCX = 12.f;
        m_tInfo.fCY = 12.f;
    }
    else {
        m_tInfo.fCX = 8.f;
        m_tInfo.fCY = 8.f;
    }
    m_fSpeed = 4.f;
    m_bDead = false;
}

int CBullet::Update()
{
    if (m_bDead) return 1;

    if (m_fVX == 0.f && m_fVY == 0.f) {
        m_tInfo.fY -= m_fSpeed;
    }
    else {
        m_tInfo.fX += m_fVX;
        m_tInfo.fY += m_fVY;
    }

    if (m_tInfo.fX < -30.f || m_tInfo.fX > 800.f + 30.f || m_tInfo.fY < -30.f || m_tInfo.fY > 600.f + 30.f)
        return 1;

    return 0;
}

void CBullet::LateUpdate()
{
    UpdateRect();
}

void CBullet::Render(HDC hDC)
{
    Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release() {}