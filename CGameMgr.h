#pragma once
#include "Singleton.h"

class CGameMgr {
DECLARE_SINGLETON(CGameMgr);

private:
	CGameMgr();
	~CGameMgr();

public:
	void Run();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	HDC m_hDC;
};

