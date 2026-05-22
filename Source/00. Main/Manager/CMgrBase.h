#pragma once
class CMgrBase
{
public:
	CMgrBase() {}
	virtual ~CMgrBase() {}

public:
	virtual void Initialize(HWND hWnd) PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

private:
	HWND m_hWnd;
	HDC	 m_hDC;
};

