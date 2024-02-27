#include "stdafx.h"
#include "BossTwo.h"


CImageList CBossTwo::m_Images;
int CBossTwo::nBossTwoMaxNum = 100;
int CBossTwo::nBossTwoCurNum = 0;





CBossTwo::CBossTwo(int HP, int Firewait)
{
	//����
	damageCtl = 50;
	nBossTwoCurNum++;
	//λ��
	m_ptPos.x = rand() % GAME_WIDTH - BOSSTWO_WIDTH / 2;
	m_ptPos.y = -20;
	m_nYMotion = 1;
	m_nXMotion = rand() % 10 - 5;
	if (m_nImgIndex % 2 != 0)//�����ͼ��������ż��
	{
		m_nYMotion = -1;
		m_ptPos.y = GAME_HEIGHT + BOSSTWO_HEIGHT;
	}
	m_V = rand() % 6 + 2;
	//����
	m_nWait = 0;
	m_waitCtl = Firewait;
	//����
	m_chealth.SetHealth(HP);
	m_chealth.setHealthPos(m_ptPos);
	//ͼ��
	m_nImgIndex = 2;
}
CBossTwo::~CBossTwo(void)
{
	nBossTwoCurNum--;
}
BOOL CBossTwo::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSSES, RGB(0, 0, 0), 144, 100, 4);
}
BOOL CBossTwo::Draw(CDC* pDC, int bPause)
{
	//�����ӳ�
	m_nWait++;
	if (m_nWait > m_waitCtl)
		m_nWait = 0;
	//�Ƿ񿪻�
	//m_ptPos.y += 1;
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nYMotion * m_V;
		//m_ptPos.y = 200;
		m_ptPos.x = m_ptPos.x + m_nXMotion * 2;

	}

	if (m_ptPos.x < -BOSSTWO_WIDTH / 2 || m_ptPos.x > GAME_WIDTH - BOSSTWO_WIDTH/ 2)
	{
		m_nXMotion = -m_nXMotion;
	}
	if (m_ptPos.y < -50 || m_ptPos.y > 500)
	{
		m_nYMotion = -m_nYMotion;
	}

	if (m_ptPos.y > GAME_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSSTWO_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	CPoint HealthPoint(m_ptPos.x - 30, m_ptPos.y);
	m_chealth.setHealthPos(HealthPoint);
	m_chealth.Draw(pDC, 0);
	return TRUE;
}
BOOL CBossTwo::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}


CRect CBossTwo::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + BOSSTWO_WIDTH, m_ptPos.y + BOSSTWO_HEIGHT));
}

int CBossTwo::GetMontion() const
{
	//return m_nYMotion;
	//��Զ���·���
	return 1;

}

void CBossTwo::takeDamage(int dmgType)
{
	//if (dmgType == 0)//�л����ҷ��ӵ�����
	//	m_chealth.decrease(50);
	//else if (dmgType == 1) // �л����һ���ײ
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

int CBossTwo::getHealth()
{
	return m_chealth.GetHealth();
}

BOOL CBossTwo::enIsAlive()
{
	return m_chealth.isAlive();
}