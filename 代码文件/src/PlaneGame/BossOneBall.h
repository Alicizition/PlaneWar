#pragma once
#include "GameObject.h"
#include "resource.h"
class CBossOneBall :
    public CGameObject
{
public:

    CBossOneBall(int x, int y, CPoint tgtp);
	~CBossOneBall(void);

	BOOL Draw(CDC* pDC, int bPause);
	static BOOL LoadImage();

	void UpdatePosition(CPoint targetPoint);
	CRect GetRect();
private:
	static const int BALL_HEIGHT = 40;
    static const int BALL_WIDTH = 15;
	static CImageList m_Images;
    //运动
	int    m_nMotion;
    CPoint targetPoint;
    double m_speed;
    int  m_positionX;
    int   m_positionY;
    double m_ddirectionX;
    double m_ddirectionY;
    //持续时间
    int m_lifeRound;
};

