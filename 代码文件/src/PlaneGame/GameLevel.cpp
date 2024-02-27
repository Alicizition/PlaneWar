#include "stdafx.h"
#include "GameLevel.h"
CGameLevel::CGameLevel()
{
	/////////////////////////////////////////////////////////////////////////////Enemy

	m_gameLevel = 0;
	//每多少帧产生敌机
	m_gEnemyNumControl = 40;
	//敌机开火延迟
	m_gEnemyWaitControl = 30;
	//敌机血量
	m_gEnemyHealthCtrol = 200;
	///////////////////////////////////////////////////////////////////////////////Boss1
	//产生Boss1
	m_gBoss1NumControl = 200;
	//Boss1开火延迟
	m_gBoss1WaitControl = 60;
	//Boss1血量初始化
	m_gBoss1HealthControl = 1000;
	//////////////////////////////////////////////////////////////////////////Boss2
	//产生Boss2
	m_gBoss2NumControl = 400;
	//Boss2开火延迟
	m_gBoss2WaitControl = 50;
	//Boss2血量初始化
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
	//普通敌人
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

	//每多少帧产生敌机 
	m_gEnemyNumControl -= 2;
	//敌机开火延迟
	m_gEnemyWaitControl--;
	//敌机血量
	m_gEnemyHealthCtrol += 50;
	////////////////////////////////////////////////////////////Boss1
	//产生Boss1
	m_gBoss1NumControl -= 10;
	//Boss1开火延迟
	m_gBoss1WaitControl -= 1;
	//Boss1血量
	m_gBoss1HealthControl += 100;
	//////////////////////////////////////////////////////////Boss2
	//产生Boss2
	m_gBoss2NumControl -= 8;
	//Boss2开火延迟
	m_gBoss2WaitControl -= 1;
	//Boss血量
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
	pDC->SetTextColor(RGB(255, 0, 255));
	CString cstr;
	m_trueLevel = m_gameLevel / 5;
	cstr.Format(_T("关卡： %d"), m_trueLevel);
	//cstr.Format(_T("关卡： "));
	//std:: string x = "血量：" + std::to_string(m_health);
	CPoint pGameLevel(GAME_WIDTH - 200, GAME_HEIGHT - 170);
	pDC->TextOutW(pGameLevel.x, pGameLevel.y, cstr);

	DeleteObject(font);
}

int CGameLevel::getGameLevel()
{
	return m_trueLevel;
}
