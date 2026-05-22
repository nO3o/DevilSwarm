#pragma once
class CMgrBase
{
public:
	CMgrBase(): m_hWnd(nullptr), m_hDC(nullptr) {}
	virtual ~CMgrBase() {}

public:
	virtual void Initialize(HWND hWnd) PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	HWND m_hWnd;
	HDC	 m_hDC;
};

