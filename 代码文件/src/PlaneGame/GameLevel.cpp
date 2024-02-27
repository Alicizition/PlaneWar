#include "stdafx.h"
#include "GameLevel.h"
CGameLevel::CGameLevel()
{
	/////////////////////////////////////////////////////////////////////////////Enemy

	m_gameLevel = 0;
	//ÿ����֡�����л�
	m_gEnemyNumControl = 40;
	//�л������ӳ�
	m_gEnemyWaitControl = 30;
	//�л�Ѫ��
	m_gEnemyHealthCtrol = 200;
	///////////////////////////////////////////////////////////////////////////////Boss1
	//����Boss1
	m_gBoss1NumControl = 200;
	//Boss1�����ӳ�
	m_gBoss1WaitControl = 60;
	//Boss1Ѫ����ʼ��
	m_gBoss1HealthControl = 1000;
	//////////////////////////////////////////////////////////////////////////Boss2
	//����Boss2
	m_gBoss2NumControl = 400;
	//Boss2�����ӳ�
	m_gBoss2WaitControl = 50;
	//Boss2Ѫ����ʼ��
	m_gBoss2HealthControl = 5000;

	/////////////////////////////////////////////////////////////////////////////Blood
	m_gBloodWait = 100;
	///////////////////////////////////////////
	m_dmgCtl = 1;
	///////////////////////////////////////////


}
CGameLevel::~CGameLevel()
{

}

void CGameLevel::allControl()
{
	//��ͨ����
	if (m_gEnemyNumControl < 10)	m_gEnemyNumControl = 10;
	if (m_gEnemyWaitControl < 10) m_gEnemyWaitControl = 10;
	if (m_gEnemyHealthCtrol > 10000) m_gEnemyHealthCtrol = 50000;
	//Boss1
	if (m_gBoss1NumControl < 20)m_gBoss1NumControl = 20;
	if (m_gBoss1WaitControl < 10) m_gBoss1WaitControl = 10;
	if (m_gBoss1HealthControl > 20000) m_gBoss1HealthControl = 20000;
	//Boss2
	if (m_gBoss2NumControl < 20) m_gBoss2NumControl = 20;
	if (m_gBoss2WaitControl < 10)m_gBoss2WaitControl = 10;
	if (m_gBoss2HealthControl > 40000)m_gBoss2HealthControl;
	if (m_gBloodWait > 500) m_gBloodWait = 500;
	if (m_gameLevel > 50) m_gameLevel = 50;
}

void CGameLevel::GameLevelUp()
{
	m_gameLevel++;

	//ÿ����֡�����л� 
	m_gEnemyNumControl -= 2;
	//�л������ӳ�
	m_gEnemyWaitControl--;
	//�л�Ѫ��
	m_gEnemyHealthCtrol += 50;
	////////////////////////////////////////////////////////////Boss1
	//����Boss1
	m_gBoss1NumControl -= 10;
	//Boss1�����ӳ�
	m_gBoss1WaitControl -= 1;
	//Boss1Ѫ��
	m_gBoss1HealthControl += 100;
	//////////////////////////////////////////////////////////Boss2
	//����Boss2
	m_gBoss2NumControl -= 8;
	//Boss2�����ӳ�
	m_gBoss2WaitControl -= 1;
	//BossѪ��
	m_gBoss2HealthControl += 100;
	//////////////////////////////////////////////////////////Blood
	m_gBloodWait += 10;
	//////////////////////////////////////////////////////////Damage
	m_dmgCtl += 1;
	allControl();

}



/////////////////////////////////////////////////Boss1
int CGameLevel::getBoss1NumCtl()
{
	return m_gBoss1NumControl;
}
int CGameLevel::getBoss1HPCtl()
{
	return m_gBoss1HealthControl;
}
int CGameLevel::getBoss1FireWt()
{
	return m_gBoss1WaitControl;
}
///////////////////////////////////////////////////Boss2
int CGameLevel::getBoss2NumCtl()
{
	return m_gBoss2NumControl;
}
int CGameLevel::getBoss2HPCtl()
{
	return m_gBoss2HealthControl;
}
int CGameLevel::getBoss2FireWt()
{
	return m_gBoss2WaitControl;
}

/////////////////////////////////////////////////////////////blood
int CGameLevel::getBloodNumCtl()
{
	return m_gBloodWait;
}
////////////////////////////////////////////////////////////Enemy
int CGameLevel::getEnemyHPCtl()
{
	return m_gEnemyHealthCtrol;
}
int CGameLevel::getEnemyNumCtl()
{
	return m_gEnemyNumControl;
}

int CGameLevel::getEnemyFireWt()
{
	return m_gEnemyWaitControl;
}
int CGameLevel::getDamageCtl()
{
	return m_dmgCtl;
}
//////////////////////////////////////////////////////////////////
void CGameLevel::Draw(CDC* pDC)
{
	HFONT font;
	font = CreateFont(20, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
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
	pDC->SetTextColor(RGB(255, 0, 255));
	CString cstr;
	m_trueLevel = m_gameLevel / 5;
	cstr.Format(_T("�ؿ��� %d"), m_trueLevel);
	//cstr.Format(_T("�ؿ��� "));
	//std:: string x = "Ѫ����" + std::to_string(m_health);
	CPoint pGameLevel(GAME_WIDTH - 200, GAME_HEIGHT - 170);
	pDC->TextOutW(pGameLevel.x, pGameLevel.y, cstr);

	DeleteObject(font);
}

int CGameLevel::getGameLevel()
{
	return m_trueLevel;
}
