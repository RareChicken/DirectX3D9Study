#include "stdafx.h"
#include "CGameEdu01.h"
#include <stdio.h>

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

	m_Eye.x = 0.f;
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

	D3DXCreateFont(m_pd3dDevice, 20, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("System"), &m_pFont);
}

VOID CGameEdu01::OnRender()
{
	char string[100];
	RECT rt = { 10, 10, 10, 10 };

	sprintf(string, "FPS: %d", m_nFPS);
	wchar_t wstring[100];
	mbstowcs(wstring, string, strlen(string) + 1);
	m_pFont->DrawText(NULL, wstring, -1, &rt, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 0.f, 1.f));
	m_nFPSCount++;
}

VOID CGameEdu01::OnUpdate()
{
	DWORD dwCurTime = GetTickCount();
	static DWORD dwOldTime = GetTickCount();
	static DWORD dwAccumulateTime = 0; // 누적 경과 시간

	m_dwElapsedTime = dwCurTime - dwOldTime; // 프레임 경과 시간
	dwOldTime = dwCurTime;

	dwAccumulateTime += m_dwElapsedTime; // 누적
	if (dwAccumulateTime >= 1000)
	{
		dwAccumulateTime = 0;
		m_nFPS = m_nFPSCount;
		m_nFPSCount = 0;
	}
}

VOID CGameEdu01::OnRelease()
{
	m_pFont->Release();
}