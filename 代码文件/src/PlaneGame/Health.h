#pragma once
#include"GameObject.h"
class CHealth:public CGameObject
{

public:

	//��ʼ��
	CHealth(int health = 100);

	//���ƶ���
	BOOL Draw(CDC* pDC, int bPause);
	static BOOL LoadImage();

	
	//λ��
	BOOL setHealthPos(int x, int y);
	BOOL setHealthPos(const CPoint p);
	//��þ�������
	CRect GetRect();


	//Ѫ������
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

