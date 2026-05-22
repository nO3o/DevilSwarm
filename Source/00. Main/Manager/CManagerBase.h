#pragma once
class CManagerBase
{
public:
	CManagerBase() {}
	virtual ~CManagerBase() {}

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

private:
	HDC m_hDC;
};

