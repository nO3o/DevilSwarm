#include "pch.h"
#include "CMonster.h"
#include "CAFObj.h"
#include "CObjMgr.h"
#include "CPlayer.h"

void CMonster::Initialize()
{
    switch (m_eID) {
    case MONSTER_A:
        m_iHP = 40;

        break;
    case MONSTER_B:
        m_iHP = 60;

        break;
    case MONSTER_SHILD:
        m_iHP = 150;

        break;
    case MONSTER_BOOM:
        m_iHP = 30;

        break;
    case MONSTER_ELITE:
        m_iHP = 400;

        break;
    case BOOS_BUTCHER:
        m_iHP = 4000;

        break;
    case BOOS_DIABLO:
        m_iHP = 25000;

        break;
    }
}

int CMonster::Update()
{
    if (m_iHP <= 0) {
        return DEAD;
    }


    return NOEVENT;
}

void CMonster::LateUpdate()
{
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release()
{
}

template<typename T>
CObj* CMonster::CreateMonster(MOB_ID ID) {

    CObj* pMonster = CAFObj<T>::Create();

    static_cast<CMonster*>(pMonster)->m_eID = ID;

    pMonster->SetPos(m_tInfo.fX, m_tInfo.fY);
    pMonster->SetAngle(m_fAngle);

    return pMonster;
}
