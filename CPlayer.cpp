#include "pch.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBullet.h"

CPlayer::CPlayer():m_fMaxHP(300), m_fShild(0.f),m_fRageCurrent(0.f), m_fRageMax(100.f), m_fRageRate(0.f), m_fAttackDelay(0.f), m_fAttackTimer(0.f)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	SetHP(m_fMaxHP);
	m_tInfo = { 100.f, float(WINCY >> 1), 100.f, 100.f };
	m_fSpeed = 4.f;
	m_fAngle = 0.f;
	m_fAttackDelay = 0.2f; // 5¹ß/ÃÊ
}

int CPlayer::Update()
{
	const float fDelta = 0.01f; // 10ms

	if (m_fAttackTimer > 0.f) {
		m_fAttackTimer -= fDelta;
		if (m_fAttackTimer < 0.f)
			m_fAttackTimer = 0.f;
	}

	__super::UpdateRect();
	return NOEVENT;

}

void CPlayer::LateUpdate()
{
	KeyInput();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState(VK_SPACE)) {
		if (m_fAttackTimer <= 0.f) {
			CObjMgr::GetInstance()->AddObject(OBJ_BULLET, CreateBullet<CBullet>());
			m_fAttackTimer = m_fAttackDelay;
		}
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

template<typename T>
CObj* CPlayer::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<T>::Create();

	pBullet->SetPos(m_tInfo.fX, m_tInfo.fY);
	pBullet->SetAngle(m_fAngle);

	return pBullet;
}

