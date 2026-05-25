#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

protected:
	INFO m_tInfo;
	RECT m_tRect;
	CObj* m_pObj;
	
	int m_iHP;
	int m_iMaxHP;
	bool m_bDead;
	float m_fSpeed;
	float m_fAngle;

public:
	const INFO* GetInfo() const { return &m_tInfo; }
	const RECT* GetRect() const { return &m_tRect; }
	const bool& GetDead() const { return m_bDead; }
	int GetHP() const { return m_iHP; }
	int GetMaxHP() const { return m_iMaxHP; }

public:
	void SetPos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void SetPosX(float fX) { m_tInfo.fX += fX; }
	void SetPosY(float fY) { m_tInfo.fY += fY; }
	void SetObj(CObj* pObj) { m_pObj = pObj; }
	void SetHP(int HP) { m_iHP = HP; }
	void SetAngle(float fAngle) { m_fAngle = fAngle; }
	void SetDead() { m_bDead = true; }

public:
	void UpdateRect();
};

	
