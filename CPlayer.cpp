#include "pch.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CBullet.h"

CPlayer::CPlayer()
	: m_iLevel(1), m_iWave(1), m_iKillCount(0), m_fEXP(0.f),
	m_fMaxEXP(100.f), m_iShild(0), m_fAttackDelay(0.f), 
	m_fAttackTimer(0.f)
{
	m_iMaxHP = 300;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	SetHP(m_iMaxHP);
	m_tInfo = { 400.f, 540.f, 40.f, 40.f };
	m_fSpeed = 4.f;
	m_fAngle = 0.f;
	m_fAttackDelay = 0.2f;
}

int CPlayer::Update()
{
	if (m_bDead) return 1;

	if (m_iHP <= 0) {
		m_iHP = 0;
		m_bDead = true;
	}
	if (m_iShild < 0) {
		m_iShild = 0;
	}

	const float fDelta = 0.01f;

	if (m_fAttackTimer > 0.f) {
		m_fAttackTimer -= fDelta;
		if (m_fAttackTimer < 0.f)
			m_fAttackTimer = 0.f;
	}

	__super::UpdateRect();
	return 0;
}

void CPlayer::LateUpdate()
{
	if (m_bDead) return;

	KeyInput();

	if (m_tRect.left < 0.f)
	{
		float fOverlapWidth = 0.f - m_tRect.left;
		m_tInfo.fX += fOverlapWidth;
	}

	if (m_tRect.right > 800.f)
	{
		float fOverlapWidth = 800.f - m_tRect.right;
		m_tInfo.fX += fOverlapWidth;
	}

	if (m_tRect.top < 0.f)
	{
		float fOverlapHeight = m_tRect.top - 0.f;
		m_tInfo.fY -= fOverlapHeight;
	}

	if (m_tRect.bottom > 540.f)
	{
		float fOverlapHeight = m_tRect.bottom - 540.f;
		m_tInfo.fY -= fOverlapHeight;
	}
}

void CPlayer::Render(HDC hDC)
{
	if (m_bDead) return;

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState(VK_SPACE)) {
		if (m_fAttackTimer <= 0.f) {

			for (int i = 0; i < m_iLevel; ++i)
			{
				CObj* pBullet = CreateBullet<CBullet>(OBJ_PLAYER_BULLET);
				if (pBullet != nullptr)
				{
					CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, pBullet);
				}
			}
			m_fAttackTimer = m_fAttackDelay;
		}
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

bool CPlayer::IncreaseEXP(float EXP) {
	m_fEXP += EXP;

	if (m_fEXP >= m_fMaxEXP) {
		m_iLevel += 1;
		m_fEXP = 0.f;
		m_fMaxEXP *= 1.2f;
		RestoreHP();
		return true;
	}
	return false;
}