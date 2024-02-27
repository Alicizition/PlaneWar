#pragma once
#include"GameObject.h"
class CLevel :public CGameObject
{
public:
    CLevel();
    CLevel(const CPoint& p);
    CLevel(int x , int y);
    ~CLevel();
    BOOL  LoadImage();
    BOOL Draw(CDC* pDC, int bPause);

    BOOL setLevelPos(int x, int y);
    BOOL setLevelPos(CPoint p);

    BOOL upgrade();
    CRect GetRect();

    int GetLevel();
    int SetLevel(const int x);

 

protected:
    int m_level;
    static CImageList m_LevelImg;

   
};

