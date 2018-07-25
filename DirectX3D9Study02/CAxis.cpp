#include "stdafx.h"
#include <d3dx9math.h>
#include "CAxis.h"

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

CAxis::CAxis(VOID)
{
}

CAxis::~CAxis(VOID)
{
}

VOID CAxis::OnInit(LPDIRECT3DDEVICE9 pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;

	CUSTOMVERTEX vertices[] =
	{
		{ -3.f, 0.f, 0.f, D3DCOLOR_RGBA(255, 0, 0, 255) }, // x축 (빨간색)
	{ 3.f, 0.f, 0.f, D3DCOLOR_RGBA(255, 0, 0, 255) },

	{ 0.f, -3.f, 0.f, D3DCOLOR_RGBA(0, 255, 0, 255) }, // y축 (파란색)
	{ 0.f, 3.f, 0.f, D3DCOLOR_RGBA(0, 255, 0, 255) },

	{ 0.f, 0.f, -3.f, D3DCOLOR_RGBA(0, 255, 255, 255) }, // z축 (마젠타색)
	{ 0.f, 0.f, 3.f, D3DCOLOR_RGBA(0, 255, 255, 255) }
	};

	m_pd3dDevice->CreateVertexBuffer(sizeof(vertices),
		0,
		D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT,
		&m_pVB,
		NULL);

	VOID* pVertices;
	m_pVB->Lock(0, sizeof(vertices), &pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();
}

VOID CAxis::OnRender()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
	m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pd3dDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

VOID CAxis::OnRelease()
{
	if (m_pVB != NULL)
	{
		m_pVB->Release();
	}
}