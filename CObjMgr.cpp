#include "pch.h"
#include "CObjMgr.h"
IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
}
void CObjMgr::Initialize() {

}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			int iResult = (*iter)->Update();

			if (iResult == DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}

			else
			{
				++iter;
			}
		}

	}
}

void CObjMgr::LateUpdate()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->LateUpdate();
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Render(hDC);
	}

}

void CObjMgr::Release() {
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), tagDelete());
		m_ObjList[i].clear();
	}
}

void CObjMgr::AddObject(OBJID eID, CObj* pObj)
{
	if (eID >= OBJ_END || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}