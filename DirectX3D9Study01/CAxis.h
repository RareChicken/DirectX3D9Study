#pragma once
#include <d3d9.h>

class CAxis
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

public:
	VOID OnInit(LPDIRECT3DDEVICE9 pd3dDevice);
	VOID OnRender();
	VOID OnRelease();
	
public:
	CAxis(VOID);
	~CAxis(VOID);
};