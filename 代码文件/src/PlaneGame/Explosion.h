#pragma once
#include "gameobject.h"

class CExplosion :public CGameObject
{
public:
	CExplosion(int x,int y);
	~CExplosion(void);

	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect();
private:
	//炸弹的图片列表
	static CImageList m_Images;
	//图像索引的步进计数
	int   m_nProcess;
public:
	static const int  EXPLOSION_WIDTH = 66;

};
