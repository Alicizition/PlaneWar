#pragma once
#include"GameObject.h"
class CHealth:public CGameObject
{

public:

	//初始化
	CHealth(int health = 100);

	//绘制对象
	BOOL Draw(CDC* pDC, int bPause);
	static BOOL LoadImage();

	
	//位置
	BOOL setHealthPos(int x, int y);
	BOOL setHealthPos(const CPoint p);
	//获得矩形区域
	CRect GetRect();


	//血量管理
	int GetHealth();
	int GetMaxHealth();
	void SetHealth(int amount);
	void setMaxHealth(int maxhp);
	void decrease(int HurtType);
	void increase(int amount);
	BOOL isAlive();
private:
	int  m_curhealth;
	int  m_maxHealth;
	int m_index;
	
	
	static CImageList m_healthImg_me;
	static CImageList m_healthImg_enemy;
	


	
};

