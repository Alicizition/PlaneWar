#pragma once
#include "GameObject.h"
#include "resource.h"
class CBossTwoBall :
    public CGameObject
{
public:

    CBossTwoBall(int x, int y, CPoint tgtp);
    CBossTwoBall(int x, int y, int direction);
    ~CBossTwoBall(void);

    BOOL Draw(CDC* pDC, int bPause);
    static BOOL LoadImage();
    void Move();
    //void UpdatePosition(CPoint targetPoint);
    CRect GetRect();
private:
    static const int BALL_HEIGHT = 8;
    static const int BALL_WIDTH = 8;
    static CImageList m_Images;
    int img_index;


    int    m_nMotion;
    double m_speed;
    int m_direction;

    double m_ddirectionX;
    double m_ddirectionY;
};

