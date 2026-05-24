#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer():m_fShild(0.f),m_fRageCurrent(0.f), m_fRageMax(100.f), m_fRageRate(0.f)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_fMaxHP = 300;
	SetHP(m_fMaxHP);
}

int CPlayer::Update()
{
	__super::UpdateRect();
	return NOEVENT;

}

void CPlayer::LateUpdate()
{
}

void CPlayer::Render(HDC hDC)
{
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState(VK_SPACE)) {

	}
	else if (GetAsyncKeyState(VK_SHIFT)) {

	}
	else if (GetAsyncKeyState('C')) {

	}
	else if (GetAsyncKeyState(VK_ESCAPE)) {

	}

	if (GetAsyncKeyState(VK_RIGHT)) {

		if (GetAsyncKeyState(VK_UP)) {

			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_LEFT)) {

		if (GetAsyncKeyState(VK_UP)) {
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;
}
