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
    CString cstr;
    cstr.Format(_T("等级： %d"), m_level);
    //std:: string x = "血量：" + std::to_string(m_health);
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