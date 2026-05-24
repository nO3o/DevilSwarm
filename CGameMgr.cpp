#include "pch.h"
#include "CGameMgr.h"

IMPLEMENT_SINGLETON(CGameMgr);

CGameMgr::CGameMgr()
{
}

CGameMgr::~CGameMgr()
{
}

inline void CGameMgr::Run() {
	Update();
	LateUpdate();
	Render();
}

void CGameMgr::Initialize()
{
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
