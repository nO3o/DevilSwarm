#include "pch.h"
#include "CSceneMgr.h"
#include "CGameMgr.h"
#include "CSceneBase.h"
#include "CTitle.h"
#include "CInGame.h"


IMPLEMENT_SINGLETON(CSceneMgr)

void CSceneMgr::Initialize(HDC hDC) {
	m_hDC = hDC;

	if (m_pScene == nullptr) {
		m_pScene = new CTitle;
		m_pScene->Initialize();
	}

	GAME_STATE m_ThisState = CGameMgr::GetInstance()->GetState();
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

		}
		if (m_pInstance != nullptr) 
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

void CSceneMgr::Release() {

	m_pScene->Release();
}

void CSceneMgr::CheckState()
{
	m_eNextState =  CGameMgr::GetInstance()->GetState();

	if (m_ThisState != m_eNextState) {
		m_ThisState = m_eNextState;
	}
	else
		m_eNextState = GS_END;
}
