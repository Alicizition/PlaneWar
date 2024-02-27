#pragma once
#include "GameObject.h"
#include "resource.h"
class CBall  :public CGameObject
{
public:
	CBall(int x,int y,int nMontion);
	~CBall(void);

	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+BALL_HEIGHT,m_ptPos.y+BALL_HEIGHT));
	}
private:
	static const int BALL_HEIGHT=8;
	static CImageList m_Images;
	int    m_nMotion;
};
