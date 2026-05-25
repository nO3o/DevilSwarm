#include "pch.h"
#include "CGameMgr.h"
#include "CObj.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CSceneMgr.h"
#include "CPlayer.h"

IMPLEMENT_SINGLETON(CGameMgr)

CGameMgr::CGameMgr() :m_hDC(nullptr), m_eState(GS_TITLE)
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
	CSceneMgr::GetInstance()->Initialize(m_hDC);
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
}

void CGameMgr::Update()
{
	CSceneMgr::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
}

void CGameMgr::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
	CObjMgr::GetInstance()->LateUpdate();
}

void CGameMgr::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	CSceneMgr::GetInstance()->Render();
}

void CGameMgr::Release()
{
	CObjMgr::DestroyInstance();
	CSceneMgr::DestroyInstance();
	ReleaseDC(g_hWnd, m_hDC);
}
