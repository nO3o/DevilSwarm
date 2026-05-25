#pragma once
#include "Singleton.h"

class CSceneBase;
class CSceneMgr {
DECLARE_SINGLETON(CSceneMgr)

private:
	CSceneMgr():m_hDC(nullptr), m_pScene(nullptr), m_eNextState(GS_END){}
	~CSceneMgr() {}

public:
	void Initialize(HDC hDC);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	HDC m_hDC;
	CSceneBase* m_pScene;
	GAME_STATE m_ThisState;
	GAME_STATE m_eNextState;

public:
	void CheckState();
};

