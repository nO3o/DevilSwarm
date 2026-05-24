#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

protected:
	INFO m_tInfo;
	RECT m_tRect;
	CObj* m_pObj;
	
	float m_fSpeed;
	float m_fAngle;
	bool m_bDead;

public:
	const INFO* GetInfo() const { return &m_tInfo; }
	const RECT* GetRect() const { return &m_tRect; }
	const bool& GetDead() const { return m_bDead; }

public:
	void SetPos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void SetObj(CObj* pObj) { m_pObj = pObj; }
	void SetAngle(float fAngle) { m_fAngle = fAngle; }
	void SetDead() { m_bDead = true; }

public:
	void UpdateRect();
};

	
