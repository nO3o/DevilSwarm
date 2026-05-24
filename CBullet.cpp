#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
    Release();
}

void CBullet::Initialize()
{
    m_tInfo.fCX = 8.f;
    m_tInfo.fCY = 8.f;

    m_fSpeed = 4.f;
}

int CBullet::Update()
{
    if (m_bDead)
        return DEAD;

    m_tInfo.fY -= m_fSpeed;

    return NOEVENT;
}

void CBullet::LateUpdate()
{
    __super::UpdateRect();
}

void CBullet::Render(HDC hDC)
{
    Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}
