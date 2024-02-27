#include "stdafx.h"
#include "BossOneBall.h"
CImageList CBossOneBall::m_Images;

CBossOneBall::CBossOneBall(int x, int y, CPoint tgtp) : CGameObject(x, y), targetPoint(tgtp)
{
	m_speed = 8;
    m_ddirectionX = 0;
    m_ddirectionY = 0;
    m_nMotion = 0;
    //持续时间
    m_lifeRound = 50;
}

CBossOneBall::~CBossOneBall(void)
{
}

void CBossOneBall::UpdatePosition(CPoint targetPoint)
{
    m_ddirectionX = targetPoint.x - m_ptPos.x;
    m_ddirectionY = targetPoint.y - m_ptPos.y;
    double length = sqrt(m_ddirectionX * m_ddirectionX + m_ddirectionY * m_ddirectionY);
    m_ddirectionX /= length;
    m_ddirectionY /= length;
    m_positionX = m_ptPos.x;
    m_positionY = m_ptPos.y;
    m_positionX += m_speed * m_ddirectionX;
    m_positionY += m_speed * m_ddirectionY;
    m_ptPos.x = (int)m_positionX;
    m_ptPos.y = (int)m_positionY + 2;

}
CRect CBossOneBall::GetRect()
{
    return CRect(m_ptPos, CPoint(m_ptPos.x + BALL_WIDTH, m_ptPos.y + BALL_HEIGHT));
}


BOOL CBossOneBall::Draw(CDC* pDC, int bPause)
{
	/*if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 8;
	}*/
    m_lifeRound--;
    if (m_lifeRound == 0) return FALSE;
	if (m_ptPos.y > GAME_HEIGHT + BALL_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BALL_HEIGHT)
		return FALSE;

	//m_Images.Draw(pDC, 2, m_ptPos, ILD_TRANSPARENT);
    m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBossOneBall::LoadImage()
{
    return CGameObject::LoadImage(m_Images, IDB_TKBALL, RGB(0, 0, 0), 39, 42, 1);
}