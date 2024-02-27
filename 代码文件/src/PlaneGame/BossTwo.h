#pragma once
#include "GameObject.h"
#include "resource.h"
#include "Health.h"
#include "Level.h"
class CBossTwo :
    public CGameObject
{

public:
	CBossTwo(int HP, int FireWait);
	~CBossTwo(void);

	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect();

	int GetMontion() const;

	void takeDamage(int dmgType);

	int getHealth();
	BOOL enIsAlive();
	//是否可以开火发射子弹
	BOOL Fired();
private:
	static const int BOSSTWO_HEIGHT = 100;
	static const int BOSSTWO_WIDTH = 144;
	static CImageList m_Images;
	int    m_nXMotion;//方向 1->向下 0->停止 -1->向上
	int    m_nYMotion;
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;

	int    m_nWait;
	int m_waitCtl;
	//血量
	CHealth m_chealth;

	//敌机等级
public:
	static int nBossTwoMaxNum;
	static int nBossTwoCurNum;
private:
	CLevel m_enlevel;

private:
	int damageCtl;
};

