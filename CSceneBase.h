#pragma once
#include "CSceneMgr.h"

class CSceneBase
{
public:
	CSceneBase() {}
	virtual ~CSceneBase() {}
public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;
};

