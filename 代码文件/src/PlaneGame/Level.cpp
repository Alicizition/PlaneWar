#include "stdafx.h"
#include "Level.h"

static CImageList m_LevelImg;

CLevel::CLevel()
{
	m_level = 0;
	m_ptPos.x = GAME_WIDTH - 100;
	m_ptPos.y = GAME_HEIGHT - 100;
}
CLevel::CLevel(const CPoint& p)
{
	m_level = 0;
    m_ptPos = p;
	
}
CLevel::CLevel(int x = GAME_WIDTH - 200, int y = GAME_HEIGHT - 200)
{
	m_level = 0;
	m_ptPos.x = x;
	m_ptPos.y = y;
}

CLevel::~CLevel()
{

}
BOOL  CLevel::Draw(CDC* pDC, int bPause)
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
    CString cstr;
    cstr.Format(_T("�ȼ��� %d"), m_level);
    //std:: string x = "Ѫ����" + std::to_string(m_health);
	CPoint Level_Point(GAME_WIDTH - 120, GAME_HEIGHT - 120);
    pDC->TextOutW(Level_Point.x,Level_Point.y, cstr);
    DeleteObject(font);
    return TRUE;
}

BOOL  CLevel::LoadImage()
{
    return TRUE;
}

CRect CLevel::GetRect()
{
     return CRect(CPoint(0,0),CPoint(200,200));
}

BOOL CLevel::setLevelPos(CPoint p)
{
    m_ptPos = p;
    return TRUE;
}
BOOL CLevel::setLevelPos(int x = GAME_WIDTH - 200, int y = GAME_HEIGHT - 200)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
	return TRUE;
}

int CLevel::GetLevel()
{
	return m_level;
}
int CLevel::SetLevel(const int x)
{
	return m_level = x;
}
BOOL CLevel::upgrade()
{
	m_level++;
	return TRUE;
}