#include "stdafx.h"
#include "CD3DApp.h"

CD3DApp::CD3DApp(VOID)
{
}

CD3DApp::~CD3DApp(VOID)
{
}

HRESULT CD3DApp::InitD3D(HWND hWnd)
{
	m_hWnd = hWnd;

	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//----------Z버퍼 설정 부분----------//
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									m_hWnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&d3dpp,
									&m_pd3dDevice)))
	{
		return E_FAIL;
	}

	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	OnInit();

	return S_OK;
}

VOID CD3DApp::Render()
{
	if (NULL == m_pd3dDevice)
	{
		return;
	}

	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.f, 0);

	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		OnRender();

		m_pd3dDevice->EndScene();
	}

	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

VOID CD3DApp::Update()
{
	OnUpdate();
}

VOID CD3DApp::Cleanup()
{
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
	}

	if (m_pd3dDevice != NULL)
	{
		m_pd3dDevice->Release();
	}
}