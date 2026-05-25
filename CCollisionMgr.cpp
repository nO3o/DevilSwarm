#include "pch.h"
#include "CCollisionMgr.h"

void CCollisionMgr::CollisionRect(std::list<CObj*> DstList, std::list<CObj*> SrcList)
{
	RECT	rc{};

	for (auto& Dst : DstList) {
		for (auto& Src : SrcList) {
			if (IntersectRect(&rc, Dst->GetRect(), Src->GetRect())) {
				Dst->SetDead();
				Src->SetDead();
			}
		}
	}
}

void CCollisionMgr::CollisionRectEx(std::list<CObj*> DstList, std::list<CObj*> SrcList)
{
	float fWidth(0.f), fHeight(0.f);

	for (auto& Dst : DstList) {
		for (auto& Src : SrcList) {
			if (CheckRect(Dst, Src, &fWidth, &fHeight)) {
			
				if (fWidth > fHeight) {
					
					if (Dst->GetInfo()->fY < Src->GetInfo()->fY)
						Dst->SetPosY(-fHeight);
					else
						Dst->SetPosY(fHeight);
				}
				else {
					if (Dst->GetInfo()->fX < Src->GetInfo()->fX)
						Dst->SetPosX(-fWidth);
					else
						Dst->SetPosX(fWidth);
				}
			}
		}
	}
}

bool CCollisionMgr::CheckRect(CObj* pDst, CObj* pSrc, float* pWidth, float* pHeight)
{
	float		fDistanceX = fabsf(pDst->GetInfo()->fX - pSrc->GetInfo()->fX);
	float		fDistanceY = fabsf(pDst->GetInfo()->fY - pSrc->GetInfo()->fY);

	float		fRadiusX = (pDst->GetInfo()->fCX + pSrc->GetInfo()->fCX) * 0.5f;
	float		fRadiusY = (pDst->GetInfo()->fCY + pSrc->GetInfo()->fCY) * 0.5f;

	if ((fRadiusX > fDistanceX) &&
		(fRadiusY > fDistanceY)) {

		*pWidth = fRadiusX - fDistanceX;
		*pHeight = fRadiusY - fDistanceY;

		return true;
	}
	return false;
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
	float	fRadius = (pDst->GetInfo()->fCX + pSrc->GetInfo()->fCX) * 0.5f;

	float	fWidth = fabsf(pDst->GetInfo()->fX - pSrc->GetInfo()->fX);
	float	fHeight = fabsf(pDst->GetInfo()->fY - pSrc->GetInfo()->fY);

	float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fRadius >= fDistance;
}
