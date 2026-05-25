#pragma once
#include "CSceneBase.h"

class CTitle :
	public CSceneBase {

public:
	CTitle():m_iMenu(TITLE_MENU::TM_START) {}
	virtual ~CTitle() {}

public:
	void Initialize()override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	RECT m_rcLogo = { 240, 72, 560, 204 };
	RECT m_menuRects[2] = {
		{ 304, 324, 496, 360 },
		{ 304, 372, 496, 408 }
	};
	LPCWSTR m_menuTexts[2] = { L"게임 시작", L"종료" };

	enum TITLE_MENU {TM_START, TM_EXIT, TM_END};
	int m_iMenu;
};

