#pragma once
#include "Singleton.h"
#include "CObj.h"

class CObjMgr {
DECLARE_SINGLETON(CObjMgr);

private:
	CObjMgr();
	~CObjMgr();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

private:
	std::list<CObj*> m_ObjList[OBJ_END];

public:
	void AddObject(OBJID eID, CObj* pObj);
};

