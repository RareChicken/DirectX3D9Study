#include "stdafx.h"
#include "d3dx9math.h"
#include "CCube.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;
	DWORD color;
};

CCube::CCube(VOID)
{
}

CCube::~CCube(VOID)
{
}

VOID CCube::OnInit(LPDIRECT3DDEVICE9 pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;

	CUSTOMVERTEX vertices[] =
	{
		{ D3DXVECTOR3(-1.f, 1.f, 1.f), D3DCOLOR_RGBA(255, 0, 255, 255) },
		{ D3DXVECTOR3(1.f, 1.f, 1.f), D3DCOLOR_RGBA(0, 255, 0, 255) },
		{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DCOLOR_RGBA(0, 0, 255, 255) },
		{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 0, 255) },

		{ D3DXVECTOR3(-1.0f, -1.0f,  1.0f) , D3DCOLOR_RGBA(255, 0, 0, 255) },
		{ D3DXVECTOR3(1.0f, -1.0f,  1.0f), D3DCOLOR_RGBA(0, 255, 10, 255) },
		{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DCOLOR_RGBA(0, 0, 255, 255) },
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DCOLOR_RGBA(255, 0, 0, 255) }
	};

	WORD indices[] = 
	{
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		4, 7, 6,
		0, 3, 7,
		0, 7, 4,
		1, 5, 6,
		1, 6, 2,
		3, 2, 6,
		3, 6, 7,
		0, 4, 5,
		0, 5, 1
	};

	// 정점 버퍼 생성
	m_pd3dDevice->CreateVertexBuffer(sizeof(vertices), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);

	VOID* pVertices;
	m_pVB->Lock(0, sizeof(vertices), &pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();

	// 인덱스 버퍼 생성
	m_pd3dDevice->CreateIndexBuffer(sizeof(indices), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);

	VOID* pIndices;
	m_pIB->Lock(0, sizeof(indices), &pIndices, 0);
	memcpy(pIndices, indices, sizeof(indices));
	m_pIB->Unlock();
}

VOID CCube::OnRender()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	// m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	// m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX)); // 출력할 정점들을 디바이스에 바인드
	m_pd3dDevice->SetIndices(m_pIB);
	m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 6 * 2);

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

VOID CCube::OnRelease()
{
	if (m_pVB != NULL)
	{
		m_pVB->Release();
	}

	if (m_pIB != NULL)
	{
		m_pIB->Release();
	}
}