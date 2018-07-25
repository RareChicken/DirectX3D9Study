#pragma once
#include "CD3DApp.h"
#include "d3dx9math.h"
#include "CAxis.h"
#include "CCube.h"

class CGameEdu01 : public CD3DApp
{
protected:
	virtual void OnInit();
	virtual void OnRender();
	virtual void OnUpdate();
	virtual void OnRelease();

	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	D3DXVECTOR3 m_Eye, m_At, m_Up;
	CAxis m_Axis;
	CCube m_Cube;

public:
	CGameEdu01(VOID);
	~CGameEdu01(VOID);
};