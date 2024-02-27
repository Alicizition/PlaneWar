#pragma once
#include "gameobject.h"
#include "Level.h"
#include "resource.h"
#include "Health.h"

class CEnemy :public CGameObject
{
public:
	CEnemy(void);
	CEnemy(int HP);
	CEnemy(int HP,int FireWait);
	~CEnemy(void);

	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect();

	int GetMontion() const;
	void takeDamage(int dmgType);

	int getHealth();

	void setHealth(int amount);
	BOOL enIsAlive();
	//是否可以开火发射子弹
	BOOL Fired();
private:
	static const int ENEMY_HEIGHT = 35;
	static CImageList m_Images;
	int    m_nXMotion;//方向 1->向下 0->停止 -1->向上
	int    m_nYMotion;
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	//发射延时
	int    m_nWait;
	int	   m_waitCtl;
	//血量
	CHealth m_chealth;

//敌机等级

private:
	CLevel m_enlevel;

};
