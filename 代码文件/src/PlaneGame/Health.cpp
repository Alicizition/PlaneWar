#include "stdafx.h"
#include "Health.h"
#include "resource.h"
CImageList CHealth:: m_healthImg_me;
CImageList CHealth:: m_healthImg_enemy;
//绘制对象

CHealth::CHealth(int health) :m_curhealth(health), m_maxHealth(health) {
	m_index = 0;
}

BOOL CHealth::LoadImage()
{
	//0 我机
	//1 敌机1
	 CGameObject::LoadImage(m_healthImg_me, IDB_BITMAP4, RGB(255, 255, 255), 200, 14, 10);
	 CGameObject::LoadImage(m_healthImg_enemy, IDB_BITMAP3, RGB(255, 255, 255), 35, 2, 10);
	return TRUE;
}

BOOL CHealth:: Draw(CDC* pDC, int bPause)
{
	//0 我机
	//1 敌机1
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
		//	int     height,            // 字体高度（以像素为单位）
		//	int     width,             // 字体宽度
		//	int     escapement,        // 字符串倾斜角度
		//	int     orientation,       // 字符串方向角度
		//	int     weight,            // 字体粗细程度（取值范围为0-1000）
		//	DWORD   italic,            // 斜体标志（0表示不使用斜体，非零值表示使用斜体）
		//	DWORD   underline,         // 下划线标志（0表示没有下划线，非零值表示有下划线）
		//	DWORD   strikeOut,         // 删除线标志（0表示没有删除线，非零值表示有删除线）
		//	DWORD   charset,           // 字符集标识符
		//	DWORD   outputPrecision,   // 输出精度标志
		//	DWORD   clipPrecision,     // 剪辑精度标志
		//	DWORD   quality,           // 字体质量标志
		//	DWORD   pitchAndFamily,    // 音调和字体族标志
		//	LPCTSTR faceName           // 字体名称
		//);
		pDC->SelectObject(font);
		pDC->SetTextColor(RGB(255, 0, 0));
		CString cstr;
		cstr.Format(_T("血量： %d"), m_curhealth);
		//std:: string x = "血量：" + std::to_string(m_health);

		pDC->TextOutW(m_ptPos.x+40, m_ptPos.y - 20, cstr);
		DeleteObject(font);
	}
	return TRUE;
}

//获得血条矩形区域 意义不大
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
