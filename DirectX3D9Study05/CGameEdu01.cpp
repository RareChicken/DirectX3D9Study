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

	m_Eye.x = 5.f;
	m_Eye.y = 8.f;
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
	D3DXMATRIX matRotation;

	m_Axis.OnRender();
	
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// x축 회전
	D3DXMatrixRotationX(&matRotation, GetTickCount() * 0.004f);

	// y축 회전
	// D3DXMatrixRotationY(&matRotation, GetTickCount() * 0.004f);

	// z축 회전
	// D3DXMatrixRotationZ(&matRotation, GetTickCount() * 0.004f);
	
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matRotation);
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