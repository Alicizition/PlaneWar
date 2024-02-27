#include "stdafx.h"
#include "Health.h"
#include "resource.h"
CImageList CHealth:: m_healthImg_me;
CImageList CHealth:: m_healthImg_enemy;
//���ƶ���

CHealth::CHealth(int health) :m_curhealth(health), m_maxHealth(health) {
	m_index = 0;
}

BOOL CHealth::LoadImage()
{
	//0 �һ�
	//1 �л�1
	 CGameObject::LoadImage(m_healthImg_me, IDB_BITMAP4, RGB(255, 255, 255), 200, 14, 10);
	 CGameObject::LoadImage(m_healthImg_enemy, IDB_BITMAP3, RGB(255, 255, 255), 35, 2, 10);
	return TRUE;
}

BOOL CHealth:: Draw(CDC* pDC, int bPause)
{
	//0 �һ�
	//1 �л�1
	m_index = m_curhealth * 10 / m_maxHealth;
	if (m_index == 0) m_index = 1;
	CPoint HealthBar_Point(GAME_WIDTH - 250, GAME_HEIGHT - 100);
	if(bPause == 0)
		m_healthImg_me.Draw(pDC, m_index - 1, m_ptPos, ILD_TRANSPARENT);
	else if(bPause == 1)
		m_healthImg_enemy.Draw(pDC, m_index - 1, m_ptPos, ILD_TRANSPARENT);


	if (bPause == 0)
	{
		HFONT font;
		font = CreateFont(15, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		//HFONT CreateFont(
		//	int     height,            // ����߶ȣ�������Ϊ��λ��
		//	int     width,             // ������
		//	int     escapement,        // �ַ�����б�Ƕ�
		//	int     orientation,       // �ַ�������Ƕ�
		//	int     weight,            // �����ϸ�̶ȣ�ȡֵ��ΧΪ0-1000��
		//	DWORD   italic,            // б���־��0��ʾ��ʹ��б�壬����ֵ��ʾʹ��б�壩
		//	DWORD   underline,         // �»��߱�־��0��ʾû���»��ߣ�����ֵ��ʾ���»��ߣ�
		//	DWORD   strikeOut,         // ɾ���߱�־��0��ʾû��ɾ���ߣ�����ֵ��ʾ��ɾ���ߣ�
		//	DWORD   charset,           // �ַ�����ʶ��
		//	DWORD   outputPrecision,   // ������ȱ�־
		//	DWORD   clipPrecision,     // �������ȱ�־
		//	DWORD   quality,           // ����������־
		//	DWORD   pitchAndFamily,    // �������������־
		//	LPCTSTR faceName           // ��������
		//);
		pDC->SelectObject(font);
		pDC->SetTextColor(RGB(255, 0, 0));
		CString cstr;
		cstr.Format(_T("Ѫ���� %d"), m_curhealth);
		//std:: string x = "Ѫ����" + std::to_string(m_health);

		pDC->TextOutW(m_ptPos.x+40, m_ptPos.y - 20, cstr);
		DeleteObject(font);
	}
	return TRUE;
}

//���Ѫ���������� ���岻��
CRect CHealth::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x+1, m_ptPos.y+1));
}
void CHealth::decrease(int amount)
{
	m_curhealth -= amount;

	if (m_curhealth < 0)
		m_curhealth = 0;
	
}

void CHealth:: increase(int amount)
{
	m_curhealth += amount;
	if (m_curhealth > m_maxHealth)
	{
		m_curhealth = m_maxHealth;
	}
}

BOOL CHealth::isAlive()
{
	return m_curhealth > 0;
}
void CHealth::SetHealth(int amount)
{
	m_curhealth = amount;
	m_maxHealth = amount;
}
BOOL CHealth::setHealthPos(int x, int y)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
	return TRUE;
}
BOOL CHealth::setHealthPos(const CPoint p)
{
	m_ptPos = p;
	return TRUE;
}
void CHealth::setMaxHealth(int maxhp)
{
	m_maxHealth = maxhp;
}
int CHealth::GetHealth() 
{
	return m_curhealth; 
}
int CHealth::GetMaxHealth() 
{ 
	return m_maxHealth; 
}
