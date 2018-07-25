#pragma once
#include <d3d9.h>

class CCube
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;

public:
	VOID OnInit(LPDIRECT3DDEVICE9 pd3dDevice);
	VOID OnRender();
	VOID OnRelease();

public:
	CCube(VOID);
	~CCube(VOID);
};