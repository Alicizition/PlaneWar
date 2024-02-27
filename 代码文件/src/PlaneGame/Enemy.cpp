#include "StdAfx.h"
#include "Enemy.h"


CImageList CEnemy::m_Images;

CEnemy::CEnemy(void)
{
	//随机确定X位置
	m_ptPos.x = rand() % GAME_WIDTH;
	//m_ptPos.x = 100;
	//随机确定图像索引
	m_nImgIndex = 0;
	//方向始终向下
	//m_nMotion = 1;
	//m_ptPos.y = -ENEMY_HEIGHT;
	//根据图像索引确定方向
	
	m_nYMotion=1;
	m_nXMotion = rand() % 10 -5
		
		;
	m_ptPos.y=-ENEMY_HEIGHT;
	if (m_nImgIndex%2!=0)//如果是图像索引是偶数
	{
		m_nYMotion=-1;
		m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	}
	
	//随机确定速度
	m_V = rand()%6+2;
	

	m_nWait=0;

	m_chealth.SetHealth(100);
	m_chealth.setHealthPos(m_ptPos);
	
}

CEnemy::CEnemy(int HP, int FireWait)
{
	//随机确定X位置
	m_ptPos.x = rand() % GAME_WIDTH;
	//m_ptPos.x = 100;
	//随机确定图像索引
	m_nImgIndex = 0;
	//方向始终向下
	//m_nMotion = 1;
	//m_ptPos.y = -ENEMY_HEIGHT;
	//根据图像索引确定方向

	m_nYMotion = 1;
	m_nXMotion = rand() % 10 - 5;


	m_ptPos.y = -ENEMY_HEIGHT;
	if (m_nImgIndex % 2 != 0)//如果是图像索引是偶数
	{
		m_nYMotion = -1;
		m_ptPos.y = GAME_HEIGHT + ENEMY_HEIGHT;
	}

	//随机确定速度
	m_V = rand() % 6 + 2;
	m_nWait = 0;
	m_waitCtl = FireWait;
	m_chealth.SetHealth(HP);
	m_chealth.setHealthPos(m_ptPos);
}
CEnemy::CEnemy(int amount)
{
	//随机确定X位置
	m_ptPos.x = rand() % GAME_WIDTH;
	//m_ptPos.x = 100;
	//随机确定图像索引
	m_nImgIndex = 0;
	//方向始终向下
	//m_nMotion = 1;
	//m_ptPos.y = -ENEMY_HEIGHT;
	//根据图像索引确定方向

	m_nYMotion = 1;
	m_nXMotion = rand() % 10 - 5;

	m_waitCtl = 10;
	m_ptPos.y = -ENEMY_HEIGHT;
	if (m_nImgIndex % 2 != 0)//如果是图像索引是偶数
	{
		m_nYMotion = -1;
		m_ptPos.y = GAME_HEIGHT + ENEMY_HEIGHT;
	}

	//随机确定速度
	m_V = rand() % 6 + 2;
	m_nWait = 0;

	m_chealth.SetHealth(amount);
	m_chealth.setHealthPos(m_ptPos);

}

CEnemy::~CEnemy(void)
{
}
BOOL CEnemy::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_ENEMY,RGB(0,0,0),35,35,2);
}
BOOL CEnemy::Draw(CDC* pDC, int bPause)
{
	//开火延迟
	m_nWait++;
	if(m_nWait>m_waitCtl)
		m_nWait=0;
	//是否开火？
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nYMotion * m_V;
		m_ptPos.x = m_ptPos.x + m_nXMotion * 2;
	}

	if (m_ptPos.x < 0 || m_ptPos.x > GAME_WIDTH - 30)
	{
		m_nXMotion = -m_nXMotion;
	}

	if(m_ptPos.y > GAME_HEIGHT)
		return FALSE;
	if(m_ptPos.y < -ENEMY_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,m_nImgIndex,m_ptPos,ILD_TRANSPARENT);

	m_chealth.setHealthPos(m_ptPos);
	m_chealth.Draw(pDC,1);
	return TRUE;
}
BOOL CEnemy::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}

CRect CEnemy::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMY_HEIGHT, m_ptPos.y + ENEMY_HEIGHT));
}
int CEnemy::GetMontion() const
{
	return m_nYMotion;
}
void CEnemy::takeDamage(int dmgType)
{
	//if (dmgType == 0)//敌机被我方子弹击中
	//	m_chealth.decrease(50);
	//else if (dmgType == 1) // 敌机与我机碰撞
	//{
	//	m_chealth.decrease(1000);
	//}
	if (dmgType < 0)//Missle
	{
		dmgType = -dmgType;
		for (int i = 0; i < dmgType + 1; i++)
		{
			if (i == dmgType)
			{
				int hurt = 500 + 10 * dmgType;
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
int CEnemy::getHealth()
{
	return m_chealth.GetHealth();
}

BOOL CEnemy::enIsAlive()
{
	return m_chealth.isAlive();
}

void CEnemy::setHealth(int amount)
{
	m_chealth.SetHealth(amount);
}
