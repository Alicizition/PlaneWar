#pragma once
#include "GameObject.h"
#include "resource.h"
#include "Enemy.h"
class CMyMissle :
    public CGameObject
{
public:
	CMyMissle(int x, int y);
	
	CMyMissle(int x, int y, CPoint p);
	~CMyMissle(void);
	void calculateTrack();
	
	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect();
private:
	
	CPoint m_targetPoint;
	CEnemy* m_pEnemy;
	
	double m_speed;
	CPoint m_direction;
	static const int Missle_HEIGHT = 20;
	static const int Missle_WIDTH = 10;
	static CImageList m_MissleImg;

};
