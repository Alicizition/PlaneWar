#pragma once
#include "GameObject.h"
#include "resource.h"
#include "Health.h"
#include "Level.h"

class CBossOne :
    public CGameObject
{
public:

	
	CBossOne(int HP,int FireWait);
	~CBossOne(void);

	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect();

	int GetMontion() const;

	void takeDamage(int dmgType);

	int getHealth();
	BOOL enIsAlive();
	//是否可以开火发射子弹
	BOOL Fired();
public:
	static int nBossOneMaxNum;
	static int nBossOneCurNum;
private:
	static const int BOSSONE_HEIGHT = 100;
	static const int BOSSONE_WIDTH = 144;
	static CImageList m_Images;
	int    m_nXMotion;//方向 1->向下 0->停止 -1->向上
	int    m_nYMotion;
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	//开火
	int    m_nWait;
	int m_waitCtl;
	//血量
	CHealth m_chealth;

	//敌机等级
	CLevel m_enlevel;
};

