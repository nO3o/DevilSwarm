#pragma once

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int  Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

public:
	void UpdateRect();

public:
	const INFO* GetInfo() const { return &m_tInfo; }
	const RECT* GetRect() const { return &m_tRect; }

	void SetPos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void SetDead() { m_bDead = true; }
	bool GetDead() const { return m_bDead; }

	int  GetHP() const { return m_iHP; }
	int  GetMaxHP() const { return m_iMaxHP; }
	void SetHP(int iHP) { m_iHP = iHP; }

protected:
	INFO  m_tInfo;
	RECT  m_tRect;
	int   m_iHP;
	int   m_iMaxHP;
	float m_fSpeed;
	float m_fAngle;
	bool  m_bDead;
};