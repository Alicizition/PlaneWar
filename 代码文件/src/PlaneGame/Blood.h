#pragma once
#include "gameobject.h"
#include "resource.h"
class CBlood:public CGameObject
{
public:
	
	CBlood();
	~CBlood();
	BOOL Draw(CDC* pDC, int bPause);
	static BOOL LoadImage();


	CRect GetRect();
private:
	static const int BLD__HEIGHT = 30;//暂定，还需要改
	static const int BLD__WIDTH = 30;//暂定，还需要改

	static CImageList m_BloodImg;
};


