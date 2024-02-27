#include "stdafx.h"
#include "MyMissle.h"

CImageList CMyMissle::m_MissleImg;
BOOL CMyMissle::Draw(CDC* pDC, int bPause)
{
	if (!bPause)
	{
		//追踪（还没写）
		m_ptPos.y = m_ptPos.y - 16;
		
	}
	

	if (m_ptPos.y < -Missle_HEIGHT)
		return FALSE;
	if (m_ptPos.y > GAME_HEIGHT)
		return FALSE;

	m_MissleImg.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CMyMissle::LoadImage()
{
	return CGameObject::LoadImage(m_MissleImg, IDB_MISSLE, RGB(255, 255, 255), 30, 60, 1);

}


CMyMissle::CMyMissle(int x, int y)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
	m_speed = 16;
}

CMyMissle::CMyMissle(int x, int y, CPoint p)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
	m_targetPoint = p;
	m_speed = 16;
}
CMyMissle::~CMyMissle(void)
{

}

void  CMyMissle::calculateTrack()
{

	if (m_ptPos.x <= m_targetPoint.x) m_ptPos.x += 10;
	if (m_ptPos.x >= m_targetPoint.x) m_ptPos.x -= 10;
	if (m_ptPos.y <= m_targetPoint.y) m_ptPos.y += 10;
	if (m_ptPos.y >= m_targetPoint.y) m_ptPos.y -= 10;

	//m_targetPoint = m_pEnemy->GetPoint();
	//方向向量
	/*m_direction.x = m_targetPoint.x - m_ptPos.x;
	m_direction.y = m_targetPoint.y - m_ptPos.y;
	// 将方向向量归一化
	//double length = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
	//m_direction.x = m_direction.x *10 / length;
	//m_direction.y = m_direction.y *10 / length;
	//计算角度
	//m_ptPos.x += static_cast<int>(m_speed * m_direction.x) + 1;
	//m_ptPos.y += static_cast<int>(m_speed * m_direction.y) + 3;
	m_ptPos.x =  m_ptPos.x + static_cast<int>(m_speed * m_direction.x) + 1;
	m_ptPos.y =  m_ptPos.y + static_cast<int>(m_speed * m_direction.y) + 3;*/
}


CRect  CMyMissle::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + Missle_WIDTH, m_ptPos.y + Missle_HEIGHT));
}