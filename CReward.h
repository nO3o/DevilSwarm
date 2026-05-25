#pragma once
class CReward {
public:
	CReward();
	~CReward();

public:
	void Initialize(REWARD_TYPE eType, float fX, float fY, int iValue);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	bool        IsAlive()  const { return m_bAlive; }
	REWARD_TYPE GetType()  const { return m_eType; }
	int         GetValue() const { return m_iValue; }
	INFO        GetInfo()  const { return m_tInfo; }

	void Collect() { m_bAlive = false; } 

private:
	INFO        m_tInfo;
	REWARD_TYPE m_eType;
	int         m_iValue; 
	bool        m_bAlive;
	DWORD       m_dwExpire;
	float       m_fBob;
};

