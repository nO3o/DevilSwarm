#pragma once
class CMgrBase
{
public:
	CMgrBase() {}
	virtual ~CMgrBase() {}

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

private:
	HDC m_hDC;
};

