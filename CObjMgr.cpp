#include "pch.h"
#include "CObjMgr.h"
#include "CEnemy.h"
#include "CBoss.h"
#include "CReward.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
    :  m_iGold(0)
    , m_dwSpawnTick(0)
{
}

CObjMgr::~CObjMgr()
{
    Release();
}

void CObjMgr::Initialize()
{
    m_dwSpawnTick = GetTickCount();
}

void CObjMgr::AddObject(OBJID eID, CObj* pObj)
{
    if (eID >= OBJ_END || nullptr == pObj)
        return;
    m_ObjList[eID].push_back(pObj);
}

void CObjMgr::SpawnEnemy()
{
    int iRand = rand() % 4;
    CObj* pPlayer = GetPlayer();
    if (pPlayer && !pPlayer->GetDead())
    {
        int iPlayerWave = static_cast<CPlayer*>(pPlayer)->GetWave();
        if (iRand == 2 && iPlayerWave < 2)
            iRand = 0;
    }

    float fSpawnX = (float)(50 + rand() % (800 - 100));

    CEnemy* pEnemy = new CEnemy;
    pEnemy->Initialize();
    pEnemy->SetEnemyType((ENEMY_TYPE)iRand);
    pEnemy->SetPos(fSpawnX, -30.f);

    AddObject(OBJ_ENEMY, pEnemy);
}

void CObjMgr::SpawnBoss()
{
    CBoss* pBoss = new CBoss;
    pBoss->Initialize();
    pBoss->SetPos(400.f, 100.f);

    AddObject(OBJ_BOSS, pBoss);
}

void CObjMgr::SpawnReward(float fX, float fY, int iHpMax, bool bBoss)
{
    if (bBoss)
    {
        CReward* pBossSoul = new CReward;
        pBossSoul->Initialize();

        float fBaseValue = 100.f + (rand() % 50);
        pBossSoul->SetRewardInfo(RT_SOUL03, fBaseValue);
        pBossSoul->SetPos(fX, fY);

        AddObject(OBJ_REWARD, pBossSoul);
    }
    else
    {
        int iRand = rand() % 10;

        if (iRand < 2)
        {
            CReward* pNormalSoul = new CReward;
            pNormalSoul->Initialize();

            float fBaseValue = 30.f + (rand() % 10);
            pNormalSoul->SetRewardInfo(RT_SOUL02, fBaseValue);
            pNormalSoul->SetPos(fX, fY);

            AddObject(OBJ_REWARD, pNormalSoul);
        }
        else
        {
            CReward* pSmallSoul = new CReward;
            pSmallSoul->Initialize();

            float fBaseValue = 10.f + (rand() % 5);
            pSmallSoul->SetRewardInfo(RT_SOUL, fBaseValue);
            pSmallSoul->SetPos(fX, fY);

            AddObject(OBJ_REWARD, pSmallSoul);
        }
    }
}

void CObjMgr::Update()
{

    for (size_t i = 0; i < OBJ_END; ++i)
    {
        for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
        {
            int iResult = (*iter)->Update();

            if (iResult == 1 || (*iter)->GetDead())
            {
                delete (*iter);
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

    CCollisionMgr::CollisionCircleDamage(m_ObjList[OBJ_ENEMY], m_ObjList[OBJ_PLAYER_BULLET], false);
    CCollisionMgr::CollisionCircleDamage(m_ObjList[OBJ_BOSS], m_ObjList[OBJ_PLAYER_BULLET], true);
    CCollisionMgr::CollisionCircleDamage(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ENEMY_BULLET], false);
    CCollisionMgr::CollisionPlayerAndReward(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_REWARD]);
}

void CObjMgr::Render(HDC hDC)
{
    for (size_t i = 0; i < OBJ_END; ++i)
    {
        for (auto& pObj : m_ObjList[i])
            pObj->Render(hDC);
    }
}

void CObjMgr::Release()
{
    for (size_t i = 0; i < OBJ_END; ++i)
    {
        for (auto& pObj : m_ObjList[i])
        {
            pObj->Release();
            delete pObj;
        }
        m_ObjList[i].clear();
    }
}