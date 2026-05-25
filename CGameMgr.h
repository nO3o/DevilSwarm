#pragma once
#include "Singleton.h"

class CGameMgr {
DECLARE_SINGLETON(CGameMgr)

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
	GAME_STATE m_eState;

public:
	GAME_STATE GetState() const { return m_eState; }
	void SetState(GAME_STATE eState) { m_eState = eState; }
};

