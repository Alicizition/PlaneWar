#include "stdafx.h"
#include "BossOne.h"

CImageList CBossOne::m_Images;
int CBossOne::nBossOneMaxNum = 100;
int CBossOne::nBossOneCurNum = 0;





CBossOne::CBossOne(int HP,int Firewait)
{
	//计数
	nBossOneCurNum++;
	//位置
	m_ptPos.x = rand() % GAME_WIDTH - BOSSONE_WIDTH/2;
	m_ptPos.y = -20;
	m_nYMotion = 1;
	m_nXMotion = rand() % 10 - 5;
	if (m_nImgIndex % 2 != 0)//如果是图像索引是偶数
	{
		m_nYMotion = -1;
		m_ptPos.y = GAME_HEIGHT + BOSSONE_HEIGHT;
	}
	m_V = rand() % 6 + 2;
	//开火
	m_nWait = 0;
	m_waitCtl = Firewait;
	//生命
	m_chealth.SetHealth(HP);
	m_chealth.setHealthPos(m_ptPos);
	//图像
	m_nImgIndex = 0;
	
}
CBossOne::~CBossOne(void)
{
	nBossOneCurNum--;
}
BOOL CBossOne::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSSES, RGB(0, 0, 0), 144, 100, 4);
}
BOOL CBossOne::Draw(CDC* pDC, int bPause)
{
	//开火延迟
	m_nWait++;
	if (m_nWait > m_waitCtl)
		m_nWait = 0;
	//是否开火？
	//m_ptPos.y += 1;
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nYMotion * m_V;
		//m_ptPos.y = 200;
		m_ptPos.x = m_ptPos.x + m_nXMotion * 2;
		
	}
	//转向
	if (m_ptPos.x < -BOSSONE_WIDTH / 2 || m_ptPos.x > GAME_WIDTH - BOSSONE_WIDTH / 2)
	{
		m_nXMotion = -m_nXMotion;
	}
	if (m_ptPos.y < -50 || m_ptPos.y > 500)
	{
		m_nYMotion = -m_nYMotion;
	}

	if (m_ptPos.y > GAME_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSSONE_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	CPoint HealthPoint(m_ptPos.x - 30,m_ptPos.y);
	m_chealth.setHealthPos(HealthPoint);
	m_chealth.Draw(pDC, 0);
	return TRUE;
}
BOOL CBossOne::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}


CRect CBossOne::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + BOSSONE_WIDTH, m_ptPos.y + BOSSONE_HEIGHT));
}

int CBossOne::GetMontion() const
{
	//return m_nYMotion;
	//永远向下发射
	return 1;

}

void CBossOne::takeDamage(int dmgType)
{
	if (dmgType < 0)//Missle
	{
		dmgType = -dmgType;
		for (int i = 0; i < dmgType + 1; i++)
		{
			if (i == dmgType)
			{
				int hurt = 500 + 20 * dmgType;
				m_chealth.decrease(hurt);
			}
		}
	}
	else//Bomb
	{
		for (int i = 0; i < dmgType + 1; i++)
		{
			if (i == dmgType)
			{
				int hurt = 40 + 5 * dmgType;
				m_chealth.decrease(hurt);
			}
		}
	}
}

int CBossOne::getHealth()
{
	return m_chealth.GetHealth();
}

BOOL CBossOne::enIsAlive()
{
	return m_chealth.isAlive();
}