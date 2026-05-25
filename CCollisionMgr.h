#pragma once
#include "CObj.h"

class CCollisionMgr
{

public:
	static void	CollisionRect(std::list<CObj*> DstList, std::list<CObj*> SrcList);

	static void	CollisionRectEx(std::list<CObj*> DstList, std::list<CObj*> SrcList);
	static bool	CheckRect(CObj* pDst, CObj* pSrc, float* pWidth, float* pHeight);

	static void	CollisionCircle(std::list<CObj*> DstList, std::list<CObj*> SrcList);
	static bool	CheckCircle(CObj* pDst, CObj* pSrc);

};

