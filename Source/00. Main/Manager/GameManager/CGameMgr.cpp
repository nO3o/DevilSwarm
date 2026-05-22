#include "pch.h"
#include "CGameMgr.h"

void CGameMgr::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDC = GetDC(m_hWnd);

	for (int i = 0; i < MGR_END; ++i) {
		if (m_arrMgr[i])
			m_arrMgr[i]->Initialize(m_hWnd);
	}
}

void CGameMgr::Update()
{
}

void CGameMgr::LateUpdate()
{
}

void CGameMgr::Render()
{
}

void CGameMgr::Release()
{
}
