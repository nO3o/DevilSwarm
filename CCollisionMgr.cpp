#include "pch.h"
#include "CCollisionMgr.h"
#include "CObjMgr.h"
#include "CReward.h"
#include "CPlayer.h"

void CCollisionMgr::CollisionRect(std::list<CObj*> DstList, std::list<CObj*> SrcList)
{
    RECT rc{};
    for (auto& Dst : DstList) {
        for (auto& Src : SrcList) {
            if (IntersectRect(&rc, Dst->GetRect(), Src->GetRect())) {
                Dst->SetDead();
                Src->SetDead();
            }
        }
    }
}

void CCollisionMgr::CollisionCircle(std::list<CObj*> DstList, std::list<CObj*> SrcList)
{
    for (auto& Dst : DstList) {
        for (auto& Src : SrcList) {
            if (CheckCircle(Dst, Src)) {
                Dst->SetDead();
                Src->SetDead();
            }
        }
    }
}

bool CCollisionMgr::CheckCircle(CObj* pDst, CObj* pSrc)
{
    float fRadius = (pDst->GetInfo()->fCX + pSrc->GetInfo()->fCX) * 0.5f;
    float fWidth = fabsf(pDst->GetInfo()->fX - pSrc->GetInfo()->fX);
    float fHeight = fabsf(pDst->GetInfo()->fY - pSrc->GetInfo()->fY);
    float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

    return fRadius >= fDistance;
}

bool CCollisionMgr::CheckRect(CObj* pDst, CObj* pSrc, float* pWidth, float* pHeight)
{
    float fDistanceX = fabsf(pDst->GetInfo()->fX - pSrc->GetInfo()->fX);
    float fDistanceY = fabsf(pDst->GetInfo()->fY - pSrc->GetInfo()->fY);
    float fRadiusX = (pDst->GetInfo()->fCX + pSrc->GetInfo()->fCX) * 0.5f;
    float fRadiusY = (pDst->GetInfo()->fCY + pSrc->GetInfo()->fCY) * 0.5f;

    if ((fRadiusX > fDistanceX) && (fRadiusY > fDistanceY)) {
        *pWidth = fRadiusX - fDistanceX;
        *pHeight = fRadiusY - fDistanceY;
        return true;
    }
    return false;
}

void CCollisionMgr::CollisionCircleDamage(std::list<CObj*>& DstList, std::list<CObj*>& SrcList, bool bIsBoss)
{
    for (auto& Dst : DstList) {
        if (Dst->GetDead()) continue;

        for (auto& Src : SrcList) {
            if (Src->GetDead()) continue;

            if (CheckCircle(Dst, Src)) {
                Src->SetDead();

                int iNewHP = Dst->GetHP() - 20;
                if (iNewHP <= 0) {
                    iNewHP = 0;
                    Dst->SetDead();

                    if (!bIsBoss) {
                        CObjMgr::GetInstance()->AddKillCount();
                        CObjMgr::GetInstance()->SpawnReward(Dst->GetInfo()->fX, Dst->GetInfo()->fY, Dst->GetMaxHP(), false);
                    }
                    else if (bIsBoss) {
                        CObjMgr::GetInstance()->SpawnReward(Dst->GetInfo()->fX, Dst->GetInfo()->fY, Dst->GetMaxHP(), true);
                    }
                    break;
                }
                Dst->SetHP(iNewHP);
            }
        }
    }
}

void CCollisionMgr::CollisionPlayerAndReward(std::list<CObj*>& PlayerList, std::list<CObj*>& RewardList)
{
    if (PlayerList.empty()) return;
    CObj* pPlayerObj = PlayerList.front();
    if (pPlayerObj->GetDead()) return;

    for (auto& pRewardObj : RewardList)
    {
        if (pRewardObj->GetDead()) continue;

        if (CheckCircle(pPlayerObj, pRewardObj))
        {
            CReward* pReward = static_cast<CReward*>(pRewardObj);
            REWARD_TYPE eType = pReward->GetRewardType();

            if (eType == RT_SOUL || eType == RT_SOUL02 || eType == RT_SOUL03)
            {
                CPlayer* pPlayer = static_cast<CPlayer*>(pPlayerObj);
                pPlayer->IncreaseEXP(pReward->GetSoulValue());
            }

            pReward->SetDead();
        }
    }
}