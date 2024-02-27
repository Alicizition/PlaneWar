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
	static const int BLD__HEIGHT = 30;//�ݶ�������Ҫ��
	static const int BLD__WIDTH = 30;//�ݶ�������Ҫ��

	static CImageList m_BloodImg;
};


