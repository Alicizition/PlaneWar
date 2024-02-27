#pragma once
#include "gameobject.h"
#include "resource.h"
class CBomb :
	public CGameObject
{
public:
	CBomb(int x,int y);
	CBomb(int x, int y, int direction);
	~CBomb(void);

	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect();
private:
	static const int BOMB_HEIGHT = 20;
	static CImageList m_Images;
	int m_direction;
};