#include "stdafx.h"
#include "CGameEdu01.h"

CGameEdu01::CGameEdu01(VOID)
{
}

CGameEdu01::~CGameEdu01(VOID)
{
}

VOID CGameEdu01::OnInit()
{
	RECT rect;
	D3DVIEWPORT9 vp;
	GetClientRect(m_hWnd, &rect);

	vp.X      = 0;
	vp.Y      = 0;
	vp.Width  = rect.right - rect.left;
	vp.Height = rect.bottom - rect.top;
	vp.MinZ   = 0.f;
	vp.MaxZ   = 1.f;

	m_Eye.x = 15.f;
	m_Eye.y = 10.f;
	m_Eye.z = -10.f;

	m_At.x = 0.f;
	m_At.y = 0.f;
	m_At.z = 0.f;

	m_Up.x = 0.f;
	m_Up.y = 1.f;
	m_Up.z = 0.f;

	D3DXMatrixLookAtLH(&m_matView, &m_Eye, &m_At, &m_Up);
	m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, 1.f, 1.f, 100.f);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
	m_pd3dDevice->SetViewport(&vp);

	m_Axis.OnInit(m_pd3dDevice);

	D3DXCreateTeapot(m_pd3dDevice, &m_pTeapotMesh, NULL);
}

VOID CGameEdu01::OnRender()
{
	D3DXMATRIX matRotationY, matWorld, matTrans, matScaling;
	FLOAT fScaling[] = { 0.3f, 0.6f, 1.f };
	D3DXVECTOR3 vTrans[] =
	{
		D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(2.f, 0.f, 0.f),
		D3DXVECTOR3(5.f, 0.f, 0.f)
	};

	D3DXMatrixRotationY(&matRotationY, GetTickCount() * 0.004f);

	m_Axis.OnRender();
	
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// 첫 번재 Teapot
	D3DXMatrixScaling(&matScaling, fScaling[0], fScaling[0], fScaling[0]);
	D3DXMatrixTranslation(&matTrans, vTrans[0].x, vTrans[0].y, vTrans[0].z);
	matWorld = matScaling * matRotationY * matTrans; // SRT
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pTeapotMesh->DrawSubset(0);

	// 두 번째 Teapot
	D3DXMatrixScaling(&matScaling, fScaling[1], fScaling[1], fScaling[1]);
	D3DXMatrixTranslation(&matTrans, vTrans[1].x, vTrans[1].y, vTrans[1].z);
	matWorld = matScaling * matRotationY * matTrans; // SRT
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pTeapotMesh->DrawSubset(0);

	// 세 번재 Teapot
	D3DXMatrixScaling(&matScaling, fScaling[2], fScaling[2], fScaling[2]);
	D3DXMatrixTranslation(&matTrans, vTrans[2].x, vTrans[2].y, vTrans[2].z);
	matWorld = matScaling * matTrans * matRotationY; // STR (원점을 기준으로 회전하게 됨)
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pTeapotMesh->DrawSubset(0);
}

VOID CGameEdu01::OnUpdate()
{

}

VOID CGameEdu01::OnRelease()
{
	m_pTeapotMesh->Release();
	m_Axis.OnRelease();
}