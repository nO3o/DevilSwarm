#pragma once
#include "CObj.h"

template<typename T>
class CAFObj
{
public:
	CAFObj() {}
	~CAFObj() {}

public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}
};