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
	//ը����ͼƬ�б�
	static CImageList m_Images;
	//ͼ�������Ĳ�������
	int   m_nProcess;
public:
	static const int  EXPLOSION_WIDTH = 66;

};
