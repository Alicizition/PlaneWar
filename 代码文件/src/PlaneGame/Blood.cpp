#include "stdafx.h"
#include "Blood.h"
CImageList CBlood::m_BloodImg;


CBlood::CBlood()
{
	m_ptPos.x = rand() % (GAME_WIDTH - BLD__HEIGHT) + 1;
}
CBlood::~CBlood()
{

}


CRect CBlood::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + BLD__WIDTH, m_ptPos.y + BLD__HEIGHT));
}


BOOL  CBlood::LoadImage()
{
	return CGameObject::LoadImage(m_BloodImg, IDB_HP, RGB(255, 255, 255), 30, 30, 1);
}

BOOL  CBlood::Draw(CDC* pDC, int bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y +  8;
	}

	if (m_ptPos.y < -BLD__HEIGHT)
		return FALSE;
	if (m_ptPos.y > GAME_HEIGHT)
		return FALSE;

	m_BloodImg.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}