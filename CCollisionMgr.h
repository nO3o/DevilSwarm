#pragma once
#include "CObj.h"

#pragma once
#include "CObj.h"

class CCollisionMgr
{
public:
    static void CollisionRect(std::list<CObj*> DstList, std::list<CObj*> SrcList);
    static void CollisionCircle(std::list<CObj*> DstList, std::list<CObj*> SrcList);
    static void CollisionCircleDamage(std::list<CObj*>& DstList, std::list<CObj*>& SrcList, bool bIsBoss);
    static void CollisionPlayerAndReward(std::list<CObj*>& PlayerList, std::list<CObj*>& RewardList);

    static bool CheckCircle(CObj* pDst, CObj* pSrc);
    static bool CheckRect(CObj* pDst, CObj* pSrc, float* pWidth, float* pHeight);
};