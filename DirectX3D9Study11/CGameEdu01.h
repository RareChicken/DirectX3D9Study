#pragma once
#include "CD3DApp.h"
#include "d3dx9math.h"
#include "CGround.h"

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
	CGround m_Ground;

public:
	CGameEdu01(VOID);
	~CGameEdu01(VOID);
};