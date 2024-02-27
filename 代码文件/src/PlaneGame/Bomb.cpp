#include "StdAfx.h"
#include "Bomb.h"

CImageList CBomb::m_Images;


CBomb::CBomb(int x,int y):CGameObject(x,y),m_direction(0)
{
	
}

CBomb::CBomb(int x, int y, int direction) :CGameObject(x, y), m_direction(direction)
{
	
}


CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP1,RGB(0,0,0),20,20,1);
}
BOOL CBomb::Draw(CDC* pDC, int bPause)
{
	if(!bPause)
	{
		if (m_direction == 0)
		{
			m_ptPos.x = m_ptPos.x - 2;
			m_ptPos.y = m_ptPos.y - 25;
		}
		else if (m_direction == 1)
		{
			m_ptPos.y = m_ptPos.y - 25;
		}
		else
		{
			m_ptPos.y = m_ptPos.y - 25;
			m_ptPos.x = m_ptPos.x + 2;
		}
	}

	if(m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}

CRect CBomb::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + BOMB_HEIGHT, m_ptPos.y + BOMB_HEIGHT));
}