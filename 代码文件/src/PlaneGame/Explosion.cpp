#include "StdAfx.h"
#include "Explosion.h"
#include "resource.h"

CImageList CExplosion::m_Images;

CExplosion::CExplosion(int x,int y):CGameObject(x,y),m_nProcess(0)
{
}

CExplosion::~CExplosion(void)
{
}
BOOL CExplosion::Draw(CDC* pDC, int bPause)
{
	//只有8张图片
	if(m_nProcess==8)//18
	{
		m_nProcess=0;
		return FALSE;
	}

	//用新位置绘制图像
	m_Images.Draw(pDC,m_nProcess,m_ptPos,ILD_TRANSPARENT);
	m_nProcess++;
	return TRUE;
}

BOOL CExplosion::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_EXPLOSION, RGB(0, 0, 0), 66, 66, 8);
}

CRect CExplosion::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + EXPLOSION_WIDTH, m_ptPos.y + EXPLOSION_WIDTH));
}