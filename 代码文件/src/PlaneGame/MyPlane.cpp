#include "StdAfx.h"
#include "MyPlane.h"
#include "resource.h"

CImageList CMyPlane::m_Images;
//CImageList CMyPlane::m_HealthBarImg;

CMyPlane::CMyPlane(void) :m_nHorMotion(0), m_nVerMotion(0)
{
	m_nWait = 0;
	m_MissleWait = 0;
	m_ptPos.x = GAME_WIDTH / 2;
	m_ptPos.y = GAME_HEIGHT / 2;
	m_plevel.SetLevel(0);
	m_canlevelUp = 0;
	control_flag = 0;
	m_score = 0;
	m_myMissleNum = 1000;
	m_zzl_flag = FALSE;
	m_threshod = 10;
	//m_health = 100;
	//m_index = 10;
	m_cHealth.SetHealth(1000000);
	m_cHealth.setHealthPos(GAME_WIDTH - 250, GAME_HEIGHT - 100);

}
CMyPlane::~CMyPlane(void)
{
	//int t = MessageBox(TEXT(" ��������ͼ��ʶ��ģʽ��\n  YES����ͼ��ʶ��ģʽ, NO�������ģʽ"), TEXT("O(��_��)O~"), MB_YESNO);
}


//ͼƬ�������
BOOL CMyPlane::LoadImage()
{
	BOOL success =// CGameObject::LoadImage(m_HealthBarImg, IDB_BITMAP4, RGB(255, 255, 255), 200, 14, 10) &&
		CGameObject::LoadImage(m_Images, IDB_BITMAP2, RGB(255, 255, 255), 69, 44, 1);

	return success;
}

BOOL CMyPlane::Draw(CDC* pDC, int bPause)
{

	m_nWait++;//�����ӳ� ÿ��3֡ ����һ��
	m_threshod = 10 - m_plevel.GetLevel() / 2;
	if (m_threshod <= 1) m_threshod = 1;
	if (m_nWait > m_threshod)
		m_nWait = 0;
	
	m_MissleWait++;
	if (m_MissleWait < 0)
		m_MissleWait = 0;
	if (m_MissleWait > 3)
		m_MissleWait = 0;

	//0 �Ǽ���
	if (control_flag == 7)
	{
		m_ptPos.x = m_ptPos.x + m_nHorMotion * 10;
		m_ptPos.y = m_ptPos.y - m_nVerMotion * 10;
	}
	//1���Ӿ�ʶ��ģʽ
	if (control_flag == 6)
	{
		;
	}

	if (m_ptPos.x >= GAME_WIDTH - PLANE_WIDTH)
		m_ptPos.x = GAME_WIDTH - PLANE_WIDTH;

	if (m_ptPos.x <= 0)
		m_ptPos.x = 0;

	if (m_ptPos.y <= 0)
		m_ptPos.y = 0;

	if (m_ptPos.y >= GAME_HEIGHT - PLANE_HEIGHT)
		m_ptPos.y = GAME_HEIGHT - PLANE_HEIGHT;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	m_plevel.Draw(pDC, 0);
	
	m_cHealth.Draw(pDC, 0);

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
	pDC->SetTextColor(RGB(5, 250, 127));

	CString cstrScore;
	cstrScore.Format(_T("�÷֣� %d"),m_score);
		CString cstrMissleNum;
		cstrMissleNum.Format(_T("�������� %d"), m_myMissleNum);
	CPoint Score_Point(GAME_WIDTH - 230, GAME_HEIGHT - 100);
		CPoint Missle_Point(GAME_WIDTH - 120, GAME_HEIGHT - 100);
	pDC->TextOutW(Score_Point.x,Score_Point.y - 40, cstrScore);
		pDC->TextOutW(Missle_Point.x, Missle_Point.y - 40, cstrMissleNum);
	DeleteObject(font);

	
	return TRUE;
}
CRect CMyPlane::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + PLANE_WIDTH, m_ptPos.y + PLANE_HEIGHT));
}
//�˶�

void CMyPlane::SetHorMotion(int nMotion)
{
	m_nHorMotion = nMotion;
}
int CMyPlane::GetHorMotion() const
{
	return m_nHorMotion;
}

void CMyPlane::SetVerMotion(int nMotion)
{
	m_nVerMotion = nMotion;
}
int CMyPlane::GetVerMotion() const
{
	return m_nVerMotion;
}

void CMyPlane::Move()
{
	for (int i = 0; i < 4; i++)
	{
		int nMeMotion = 0;
		SetVerMotion(0);
		SetHorMotion(0);

		nMeMotion = GetKey('W');
		if (nMeMotion == 1)
			SetVerMotion(1);

		nMeMotion = GetKey('S');
		if (nMeMotion == 1)
			SetVerMotion(-1);

		nMeMotion = GetKey('D');
		if (nMeMotion == 1)
			SetHorMotion(1);

		nMeMotion = GetKey('A');
		if (nMeMotion == 1)
			SetHorMotion(-1);
	}
}
void CMyPlane::Move(CPoint pos, int MoveType)//OPENCV
{
	m_ptPos = pos;
}

int CMyPlane::getControlMode()
{
	return control_flag; 
}
BOOL CMyPlane::setControlMode(int Mode)
{
	control_flag = Mode;
	return TRUE;
}


int CMyPlane::GetKey(int nVirtKey)
{
	return (GetKeyState(nVirtKey) & 0x8000) ? 1 : 0;
}


//����
BOOL CMyPlane::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;

}

//Ѫ��

int CMyPlane::takeDamage(int dmgType)
{
	if (dmgType == 0)//��ͨ�л��ӵ�
	{
		m_cHealth.decrease(10);
	}
	else if (dmgType == 1)//BossOneBall
	{
		m_cHealth.decrease(50);
	}
	switch (dmgType)
	{
	case 0://��ͨ�л��ӵ�
		m_cHealth.decrease(10);
		break;

	case 1://BossOneBall
		m_cHealth.decrease(50);
		break;
	case 2:
		m_cHealth.decrease(100);
		break;
	default:
		break;
	}
	return 1;
}
BOOL CMyPlane::PisAlive() { return m_cHealth.isAlive(); }




BOOL CMyPlane::FiredMissle()
{
	//���û�е��������ܷ���
	if (m_myMissleNum <= 0)
	{
		m_myMissleNum = 0;
		return FALSE;
	}
	else //������ӵ�
	{	//��������ӳ�Ϊ0
		if (m_MissleWait == 0)
		{
			m_myMissleNum--;
			return TRUE;
		}
		//���û�ˣ����ܷ���
		return FALSE;
	}
}

int CMyPlane::Heal(int healTyle)
{
	if (healTyle == 0)
	{
		m_cHealth.increase(10);
	}
	return 1;
}

int CMyPlane::getPlaneLevel()
{
	return m_plevel.GetLevel();
}
void CMyPlane::ScoreUp()
{
	m_score++;
}


BOOL CMyPlane::upgrade()
{
	int level_Threshold = 2;//��СΪ2
	if (m_zzl_flag == TRUE)
	{
		if (m_score % level_Threshold == 0)//�����3�ı���
		{
			m_plevel.upgrade();//�ȼ�+1
			m_zzl_flag = FALSE;
		}
	}
	else
	{
		if (m_score % level_Threshold != 0)//����3�ı���
		{
			m_zzl_flag = TRUE;
		}
	}
	return TRUE;
}
void CMyPlane::AddScore()
{
	m_score++;
}
