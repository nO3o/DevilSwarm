#include "pch.h"
#include "CGameMgr.h"
#include "CObj.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"

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
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
}

void CGameMgr::Update()
{
	CObjMgr::GetInstance()->Update();
}

void CGameMgr::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CGameMgr::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	CObjMgr::GetInstance()->Render(m_hDC);
}

void CGameMgr::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::DestroyInstance();
}
