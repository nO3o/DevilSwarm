#pragma once
#include "Singleton.h"
#include "CObj.h"

class CObjMgr {
    DECLARE_SINGLETON(CObjMgr)

private:
    CObjMgr();
    ~CObjMgr();

public:
    void Initialize();
    void Update();
    void LateUpdate();
    void Render(HDC hDC);
    void Release();

public:
    void AddObject(OBJID eID, CObj* pObj);
    const std::list<CObj*>& GetObjList(OBJID eID) const { return m_ObjList[eID]; }
    CObj* GetPlayer() { return m_ObjList[OBJ_PLAYER].empty() ? nullptr : m_ObjList[OBJ_PLAYER].front(); }

    void AddGold(int iGoldVal) { m_iGold += iGoldVal; }
    void AddKillCount() { ++m_iKillCount; }

private:
    void SpawnEnemy();
    void SpawnBoss();

public:
    void SpawnReward(float fX, float fY, int iHpMax, bool bBoss);

private:
    std::list<CObj*> m_ObjList[OBJ_END];

    int    m_iWave;
    int    m_iKillCount;
    int    m_iGold;
    DWORD  m_dwSpawnTick;
    bool   m_bBossSpawned;
};