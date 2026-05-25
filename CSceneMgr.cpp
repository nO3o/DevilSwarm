#include "pch.h"
#include "CSceneMgr.h"
#include "CGameMgr.h"
#include "CSceneBase.h"
#include "CTitle.h"

IMPLEMENT_SINGLETON(CSceneMgr)

void CSceneMgr::Initialize(HDC hDC) {
	m_hDC = hDC;

	if (m_pScene == nullptr) {
		m_pScene = new CTitle;
		m_pScene->Initialize();
	}

}

void CSceneMgr::Update() {

	if (m_eNextState != GS_END) {

		if (m_pScene != nullptr) {
			m_pScene->Release();
			Safe_Delete(m_pScene);
		}

		switch (m_eNextState) {
			case GS_TITLE:
				m_pScene = new CTitle;
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