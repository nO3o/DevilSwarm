#include "pch.h"
#include "CGameMgr.h"
#include "CObj.h"

IMPLEMENT_SINGLETON(CGameMgr);

CGameMgr::CGameMgr() :m_hDC(nullptr), m_eState(STATE_TITLE)
{
}

CGameMgr::~CGameMgr()
{
}

void CGameMgr::Run() {
	Update();
	LateUpdate();
	Render();
}

void CGameMgr::Initialize()
{
	m_hDC = GetDC(g_hWnd);
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
	ReleaseDC(g_hWnd, m_hDC);
}
