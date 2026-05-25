#include "pch.h"
#include "CSceneMgr.h"
#include "CGameMgr.h"
#include "CSceneBase.h"
#include "CTitle.h"
#include "CInGame.h"
#include "CWin.h"
#include "CLose.h"

IMPLEMENT_SINGLETON(CSceneMgr)

void CSceneMgr::Initialize(HDC hDC) {
	m_hDC = hDC;

	if (m_pScene == nullptr) {
		m_pScene = new CTitle;
		m_pScene->Initialize();
	}

	m_ThisState = CGameMgr::GetInstance()->GetState();
}

void CSceneMgr::Update() {

	CheckState();

	if (m_eNextState != GS_END) {

		if (m_pScene != nullptr) {
			m_pScene->Release();
			Safe_Delete(m_pScene);
		}

		switch (m_eNextState) {
			case GS_TITLE:
				m_pScene = new CTitle;
				break;

			case GS_INGAME:
				m_pScene = new CInGame;
				break;

			case GS_CLEAR:
				m_pScene = new CWin;
				break;

			case GS_GAMEOVER:
				m_pScene = new CLose;
				break;
		}
		if (m_pScene != nullptr)
			m_pScene->Initialize();
		
		m_eNextState = GS_END;
	}

	if (m_pScene != nullptr)
		m_pScene->Update();
	
}

void CSceneMgr::LateUpdate() {

	if (m_pScene != nullptr)
		m_pScene->LateUpdate();
}

void CSceneMgr::Render() {
	if (m_pScene != nullptr)
		m_pScene->Render(m_hDC);
}

void CSceneMgr::Release()
{
	if (m_pScene != nullptr)
	{
		m_pScene->Release();
		Safe_Delete(m_pScene);
	}
}

void CSceneMgr::CheckState()
{
	GAME_STATE eCurrentState =  CGameMgr::GetInstance()->GetState();

	if (m_ThisState != eCurrentState) {
		m_ThisState = eCurrentState;
		m_eNextState = eCurrentState;
	}
	else
		m_eNextState = GS_END;
}
